//
// Created by leixing on 2024/11/5.
//

#include <iostream>
#include <memory>

#include "mediapipe/framework/formats/image.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/port/status.h"

#include "mediapipe/tasks/cc/components/containers/landmark.h"
#include "mediapipe/tasks/cc/vision/core/image_processing_options.h"
#include "mediapipe/tasks/cc/vision/face_landmarker/face_landmarker.h"
#include "mediapipe/tasks/cc/vision/face_landmarker/face_landmarker_result.h"
#include "mediapipe/tasks/cc/vision/core/running_mode.h"

#include "mediapipe/tasks/libmptask/core/base_options_converter.h"
#include "mediapipe/tasks/libmptask/vision/face_landmarker/face_landmarker_api.h"
#include "mediapipe/tasks/libmptask/vision/face_landmarker/face_landmarker.h"
#include "mediapipe/tasks/libmptask/vision/face_landmarker/face_landmarker_result.h"
#include "mediapipe/tasks/libmptask/vision/utils/image_utils.h"

// using namespace ::mediapipe::tasks::components::containers;
// using namespace ::mediapipe::tasks::vision;

// typedef ::mediapipe::tasks::vision::face_landmarker::FaceLandmarkerResult CppFaceLandmarkerResult;
// typedef ::mediapipe::tasks::vision::core::ImageProcessingOptions CppImageProcessingOptions;

using ::mediapipe::Image;
typedef ::mediapipe::ImageFormat::Format CppImageFormat;

namespace libmptask {

    inline
    CppImageFormat imageFormatToCppImageFormat(ImageFormat imageFormat) {
        return static_cast<CppImageFormat>(static_cast<int>(imageFormat));
    }

    inline
    ImageFormat cppImageFormatToImageFormat(CppImageFormat imageFormat) {
        return static_cast<ImageFormat>(static_cast<int>(imageFormat));
    }

    inline
    int CppProcessError(absl::Status status, char** error_msg) {
        if (error_msg) {
            *error_msg = strdup(status.ToString().c_str());
        }
        return status.raw_code();
    }

    MP_CPP_EXPORT FaceLandmarkerApi* FaceLandmarkerApi::create(FaceLandmarkerOptions& options, char** error_msg) {
        std::cout<< "FaceLandmarker::Create" << std::endl;
        absl::StatusOr<std::unique_ptr<FaceLandmarker>> landmarkerStatusOr = FaceLandmarker::Create(std::make_unique<FaceLandmarkerOptions>(options));
        if(!landmarkerStatusOr.ok()){
            absl::Status status = landmarkerStatusOr.status();
            std::cerr << "Failed to create FaceLandmarker: " << status.message() << std::endl;
            return nullptr;
        }

        FaceLandmarkerApi* faceLandmarkerApi = new FaceLandmarkerApi();
        faceLandmarkerApi->faceLandmarker = landmarkerStatusOr->release();

        return faceLandmarkerApi;
    }

    FaceLandmarkerApi::FaceLandmarkerApi() {

    }

    FaceLandmarkerApi::~FaceLandmarkerApi() {
        auto cpp_landmarker = static_cast<FaceLandmarker*>(this->faceLandmarker);
        auto result = cpp_landmarker->Close();
        if (!result.ok()) {
            ABSL_LOG(ERROR) << "Failed to close FaceLandmarker: " << result;
            return;
        }
        delete cpp_landmarker;
    }

    FaceLandmarkerResult FaceLandmarkerApi::detect(const char* path, std::optional<ImageProcessingOptions> image_processing_options) {
        absl::StatusOr <::mediapipe::Image> image_status = DecodeImageFromFile(path);
        if (!image_status.ok()) {
            std::cerr << "Failed to load image: " << image_status.status().message() << std::endl;
            //return nullptr;
            return FaceLandmarkerResult();
        }
        FaceLandmarker* faceLandmarker = static_cast<FaceLandmarker*>(this->getFaceLandmarker());
        Image image = image_status.value();
        absl::StatusOr<FaceLandmarkerResult> result_status = faceLandmarker->Detect(image, image_processing_options);
        if (!result_status.ok()) {
            std::cerr << "Detection failed: " << result_status.status().message() << std::endl;
            // return nullptr;
            return FaceLandmarkerResult();
        }

        FaceLandmarkerResult& detectResult = result_status.value();
        FaceLandmarkerResult result;
        result.face_landmarks = detectResult.face_landmarks;
        if (detectResult.face_blendshapes.has_value()) {
            result.face_blendshapes = std::move(detectResult.face_blendshapes.value());
            detectResult.face_blendshapes.reset();
        }

        if (detectResult.facial_transformation_matrixes.has_value()) {
            std::vector<Matrix>& matrixes = detectResult.facial_transformation_matrixes.value();
            for (const Matrix& matrix : matrixes) {
                result.facial_transformation_matrixes->push_back(matrix);  // 将 matrix 逐个添加到 result
            }
            matrixes.clear();
            detectResult.facial_transformation_matrixes.reset();
        }

        return result;
    }

    FaceLandmarkerResult FaceLandmarkerApi::detect(const uint8_t* pixel_data, int width, int height, int channels, std::optional<ImageProcessingOptions> image_processing_options) {
        absl::StatusOr <::mediapipe::Image> image_status = CreateImageFromBuffer(pixel_data, width, height, channels);
        if (!image_status.ok()) {
            std::cerr << "Failed to load image: " << image_status.status().message() << std::endl;
            //return nullptr;
            return FaceLandmarkerResult();
        }
        FaceLandmarker* faceLandmarker = static_cast<FaceLandmarker*>(this->getFaceLandmarker());
        Image image = image_status.value();
        absl::StatusOr<FaceLandmarkerResult> result_status = faceLandmarker->Detect(image, image_processing_options);
        if (!result_status.ok()) {
            std::cerr << "Detection failed: " << result_status.status().message() << std::endl;
            // return nullptr;
            return FaceLandmarkerResult();
        }

        FaceLandmarkerResult& detectResult = result_status.value();
        FaceLandmarkerResult result;
        result.face_landmarks = detectResult.face_landmarks;
        if (detectResult.face_blendshapes.has_value()) {
            result.face_blendshapes = std::move(detectResult.face_blendshapes.value());
            detectResult.face_blendshapes.reset();
        }

        if (detectResult.facial_transformation_matrixes.has_value()) {
            std::vector<Matrix>& matrixes = detectResult.facial_transformation_matrixes.value();
            for (const Matrix& matrix : matrixes) {
                result.facial_transformation_matrixes->push_back(matrix);  // 将 matrix 逐个添加到 result
            }
            matrixes.clear();
            detectResult.facial_transformation_matrixes.reset();
        }

        return result;
    }

    FaceLandmarkerResult FaceLandmarkerApi::detect(const uint8_t* pixel_data, int width, int height, ImageFormat format, std::optional<ImageProcessingOptions> image_processing_options) {
        absl::StatusOr <::mediapipe::Image> image_status = CreateImageFromBuffer(pixel_data, width, height, imageFormatToCppImageFormat(format));
        if (!image_status.ok()) {
            std::cerr << "Failed to load image: " << image_status.status().message() << std::endl;
            //return nullptr;
            return FaceLandmarkerResult();
        }
        FaceLandmarker* faceLandmarker = static_cast<FaceLandmarker*>(this->getFaceLandmarker());
        Image image = image_status.value();
        absl::StatusOr<FaceLandmarkerResult> result_status = faceLandmarker->Detect(image, image_processing_options);
        if (!result_status.ok()) {
            std::cerr << "Detection failed: " << result_status.status().message() << std::endl;
            // return nullptr;
            return FaceLandmarkerResult();
        }

        FaceLandmarkerResult& detectResult = result_status.value();
        FaceLandmarkerResult result;
        result.face_landmarks = detectResult.face_landmarks;
        if (detectResult.face_blendshapes.has_value()) {
            result.face_blendshapes = std::move(detectResult.face_blendshapes.value());
            detectResult.face_blendshapes.reset();
        }

        if (detectResult.facial_transformation_matrixes.has_value()) {
            std::vector<Matrix>& matrixes = detectResult.facial_transformation_matrixes.value();
            for (const Matrix& matrix : matrixes) {
                result.facial_transformation_matrixes->push_back(matrix);  // 将 matrix 逐个添加到 result
            }
            matrixes.clear();
            detectResult.facial_transformation_matrixes.reset();
        }

        return result;
    }

    FaceLandmarkerResult FaceLandmarkerApi::detectForVideo(const uint8_t* pixel_data, int width, int height, int channels, int64_t timestamp_ms, std::optional<ImageProcessingOptions> image_processing_options) {
        absl::StatusOr <::mediapipe::Image> image_status = CreateImageFromBuffer(pixel_data, width, height, channels);
        if (!image_status.ok()) {
            std::cerr << "Failed to load image: " << image_status.status().message() << std::endl;
            //return nullptr;
            return FaceLandmarkerResult();
        }

        FaceLandmarker* faceLandmarker = static_cast<FaceLandmarker*>(this->getFaceLandmarker());
        Image image = image_status.value();
        absl::StatusOr<FaceLandmarkerResult> result_status = faceLandmarker->DetectForVideo(image, timestamp_ms, image_processing_options);
        if (!result_status.ok()) {
            std::cerr << "Detection failed: " << result_status.status().message() << std::endl;
            // return nullptr;
            return FaceLandmarkerResult();
        }

        FaceLandmarkerResult& detectResult = result_status.value();
        FaceLandmarkerResult result = detectResult;
        return result;
//        result.face_landmarks = detectResult.face_landmarks;
//        if (detectResult.face_blendshapes.has_value()) {
//            result.face_blendshapes = std::move(detectResult.face_blendshapes.value());
//            detectResult.face_blendshapes.reset();
//        } else{
//            result.face_blendshapes = std::nullopt;
//        }
//
//        // typedef Eigen::MatrixXf Matrix;
//        if (detectResult.facial_transformation_matrixes.has_value()) {
//            const std::vector<Matrix>& sourceMatrixes = detectResult.facial_transformation_matrixes.value();
//
//            // 构造目标可选项
//            std::optional<std::vector<Matrix>> resultMatrixes;
//            resultMatrixes.emplace(); // 原地构造空 vector
//
//            // 使用 std::transform
//            std::transform(sourceMatrixes.begin(), sourceMatrixes.end(),
//                           std::back_inserter(*resultMatrixes), [](const Matrix& srcMatrix) {
//                        Matrix dstMatrix;
//                        dstMatrix.resize(srcMatrix.rows(), srcMatrix.cols());
//                        return dstMatrix;
//                    });
//
//            result.facial_transformation_matrixes = std::move(resultMatrixes);
//        } else {
//            result.facial_transformation_matrixes = std::nullopt;
//        }
//
//
//
//        return result;
    }

    FaceLandmarkerResult FaceLandmarkerApi::detectForVideo(const uint8_t* pixel_data, int width, int height, ImageFormat format, int64_t timestamp_ms, std::optional<ImageProcessingOptions> image_processing_options) {
        absl::StatusOr <::mediapipe::Image> image_status = CreateImageFromBuffer(pixel_data, width, height, imageFormatToCppImageFormat(format));
        if (!image_status.ok()) {
            std::cerr << "Failed to load image: " << image_status.status().message() << std::endl;
            //return nullptr;
            return FaceLandmarkerResult();
        }
        FaceLandmarker* faceLandmarker = static_cast<FaceLandmarker*>(this->getFaceLandmarker());
        Image image = image_status.value();
        absl::StatusOr<FaceLandmarkerResult> result_status = faceLandmarker->DetectForVideo(image, timestamp_ms, image_processing_options);
        if (!result_status.ok()) {
            std::cerr << "Detection failed: " << result_status.status().message() << std::endl;
            // return nullptr;
            return FaceLandmarkerResult();
        }

        FaceLandmarkerResult& detectResult = result_status.value();
        FaceLandmarkerResult result;
        result.face_landmarks = detectResult.face_landmarks;
        if (detectResult.face_blendshapes.has_value()) {
            result.face_blendshapes = std::move(detectResult.face_blendshapes.value());
            detectResult.face_blendshapes.reset();
        }

        if (detectResult.facial_transformation_matrixes.has_value()) {
            std::vector<Matrix>& matrixes = detectResult.facial_transformation_matrixes.value();
            for (const Matrix& matrix : matrixes) {
                result.facial_transformation_matrixes->push_back(matrix);  // 将 matrix 逐个添加到 result
            }
            matrixes.clear();
            detectResult.facial_transformation_matrixes.reset();
        }

        return result;
    }

    int FaceLandmarkerApi::detectAsync(const uint8_t* pixel_data, int width, int height, int channels, int64_t timestamp_ms, std::optional<ImageProcessingOptions> image_processing_options) {
        absl::StatusOr <::mediapipe::Image> image_status = CreateImageFromBuffer(pixel_data, width, height, channels);
        if (!image_status.ok()) {
            std::cerr << "Failed to load image: " << image_status.status().message() << std::endl;
            //return nullptr;
            return -1;
        }
        FaceLandmarker* faceLandmarker = static_cast<FaceLandmarker*>(this->getFaceLandmarker());
        Image image = image_status.value();
        absl::Status result_status = faceLandmarker->DetectAsync(image, timestamp_ms, image_processing_options);
        if (!result_status.ok()) {
            std::cerr << "Detection failed: " << result_status.message() << std::endl;
            // return nullptr;
            return -1;
        }
        return 0;
    }

    int FaceLandmarkerApi::detectAsync(const uint8_t* pixel_data, int width, int height, ImageFormat format, int64_t timestamp_ms, std::optional<ImageProcessingOptions> image_processing_options) {
        absl::StatusOr <::mediapipe::Image> image_status = CreateImageFromBuffer(pixel_data, width, height, imageFormatToCppImageFormat(format));
        if (!image_status.ok()) {
            std::cerr << "Failed to load image: " << image_status.status().message() << std::endl;
            //return nullptr;
            return -1;
        }
        FaceLandmarker* faceLandmarker = static_cast<FaceLandmarker*>(this->getFaceLandmarker());
        Image image = image_status.value();
        absl::Status result_status = faceLandmarker->DetectAsync(image, timestamp_ms, image_processing_options);
        if (!result_status.ok()) {
            std::cerr << "Detection failed: " << result_status.message() << std::endl;
            // return nullptr;
            return -1;
        }
        return 0;
    }

    int FaceLandmarkerApi::close() {
        FaceLandmarker* faceLandmarker = static_cast<FaceLandmarker*>(this->getFaceLandmarker());
        absl::Status result_status = faceLandmarker->Close();
        if (!result_status.ok()) {
            std::cerr << "Detection failed: " << result_status.message() << std::endl;
            // return nullptr;
            return -1;
        }
        return 0;
    }
}