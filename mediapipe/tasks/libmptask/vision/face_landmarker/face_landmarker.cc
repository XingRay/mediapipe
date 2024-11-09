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
#include "mediapipe/tasks/libmptask/vision/face_landmarker/face_landmarker.h"
#include "mediapipe/tasks/libmptask/vision/face_landmarker/face_landmarker_result.h"
#include "mediapipe/tasks/libmptask/vision/utils/image_utils.h"

using namespace ::mediapipe::tasks::components::containers;
using namespace ::mediapipe::tasks::vision;

typedef ::mediapipe::tasks::vision::face_landmarker::FaceLandmarkerResult CppFaceLandmarkerResult;
typedef ::mediapipe::tasks::vision::core::ImageProcessingOptions CppImageProcessingOptions;


namespace libmptask {

    void printCppResult(const ::mediapipe::tasks::vision::face_landmarker::FaceLandmarkerResult& result) {
        // Output face landmarks
        std::cout << "face_landmarks_count: " << result.face_landmarks.size() << std::endl;
        for (const auto& landmarks : result.face_landmarks) {
            std::cout << "Detected landmarks: " << std::endl;
            for (const auto& landmark : landmarks.landmarks) {
                std::cout << "( " << landmark.x << ", " << landmark.y << ", " << landmark.z << " )" << std::endl;
            }
        }

        // Output face blendshapes if available
        if (result.face_blendshapes.has_value()) {
            std::cout << "face_blendshapes_count: " << result.face_blendshapes->size() << std::endl;
            for (const auto& blendshape : *result.face_blendshapes) {
                std::cout << "Detected face blendshape: " << std::endl;
                std::cout << "head_index:" << blendshape.head_index << std::endl;
                if (blendshape.head_name.has_value()) {
                    std::cout << "head_name:" << *blendshape.head_name << std::endl;
                }
                else {
                    std::cout << "head_name has no value" << std::endl;
                }

                for (const auto& category : blendshape.categories) {
                    std::cout << "index: " << category.index << ", score: " << category.score;

                    std::cout << ", category_name: ";
                    if (category.category_name.has_value()) {
                        std::cout << *category.category_name;
                    }
                    else {
                        std::cout << "N/A";
                    }

                    std::cout << "display_name: ";
                    if (category.display_name.has_value()) {
                        std::cout << *category.display_name;
                    }
                    else {
                        std::cout << "N/A";
                    }

                    std::cout << std::endl;
                }
            }
        }
        else {
            std::cout << "No face blendshapes detected." << std::endl;
        }

        // Output facial transformation matrices if available
        if (result.facial_transformation_matrixes.has_value()) {
            std::cout << "facial_transformation_matrixes_count: " << result.facial_transformation_matrixes->size() << std::endl;
            for (const auto& matrix : *result.facial_transformation_matrixes) {
                std::cout << "Matrix (" << matrix.rows() << "x" << matrix.cols() << "):" << std::endl;
                for (int row = 0; row < matrix.rows(); ++row) {
                    for (int col = 0; col < matrix.cols(); ++col) {
                        std::cout << matrix(row, col) << " ";
                    }
                    std::cout << std::endl;
                }
            }
        }
        else {
            std::cout << "No facial transformation matrices detected." << std::endl;
        }
    }

    void printResult(const libmptask::FaceLandmarkerResult& result) {
        // Output face landmarks
        std::cout << "face_landmarks_count: " << result.face_landmarks.size() << std::endl;
        for (const auto& landmarks : result.face_landmarks) {
            std::cout << "Detected landmarks: " << std::endl;
            for (const auto& landmark : landmarks.landmarks) {
                std::cout << "( " << landmark.x << ", " << landmark.y << ", " << landmark.z << " )" << std::endl;
            }
        }

        // Output face blendshapes if available
        if (result.face_blendshapes.has_value()) {
            std::cout << "face_blendshapes_count: " << result.face_blendshapes->size() << std::endl;
            for (const auto& blendshape : *result.face_blendshapes) {
                std::cout << "Detected face blendshape: " << std::endl;
                std::cout << "head_index:" << blendshape.head_index << std::endl;
                if (blendshape.head_name.has_value()) {
                    std::cout << "head_name:" << *blendshape.head_name << std::endl;
                }
                else {
                    std::cout << "head_name has no value" << std::endl;
                }

                for (const auto& category : blendshape.categories) {
                    std::cout << "index: " << category.index << ", score: " << category.score;

                    std::cout << ", category_name: ";
                    if (category.category_name.has_value()) {
                        std::cout << *category.category_name;
                    }
                    else {
                        std::cout << "N/A";
                    }

                    std::cout << "display_name: ";
                    if (category.display_name.has_value()) {
                        std::cout << *category.display_name;
                    }
                    else {
                        std::cout << "N/A";
                    }

                    std::cout << std::endl;
                }
            }
        }
        else {
            std::cout << "No face blendshapes detected." << std::endl;
        }

        // Output facial transformation matrices if available
        if (result.facial_transformation_matrixes.has_value()) {
            std::cout << "facial_transformation_matrixes_count: " << result.facial_transformation_matrixes->size() << std::endl;
            for (const auto& matrix : *result.facial_transformation_matrixes) {
                std::cout << "Matrix (" << matrix.rows() << "x" << matrix.cols() << "):" << std::endl;
                for (int row = 0; row < matrix.rows(); ++row) {
                    for (int col = 0; col < matrix.cols(); ++col) {
                        std::cout << matrix(row, col) << " ";
                    }
                    std::cout << std::endl;
                }
            }
        }
        else {
            std::cout << "No facial transformation matrices detected." << std::endl;
        }
    }

    inline
    ::mediapipe::ImageFormat::Format imageFormatToCppImageFormat(ImageFormat imageFormat) {
        return static_cast<::mediapipe::ImageFormat::Format>(static_cast<int>(imageFormat));
    }

    inline
    ImageFormat cppImageFormatToImageFormat(::mediapipe::ImageFormat::Format imageFormat) {
        return static_cast<ImageFormat>(static_cast<int>(imageFormat));
    }

    /*absl::StatusOr<FaceLandmarkerResult> Detect(
        Image image,
        std::optional<core::ImageProcessingOptions> image_processing_options =
        std::nullopt);*/
    FaceLandmarkerResult cppDetect(const FaceLandmarker* faceLandmarker, const ::mediapipe::Image& image, std::optional<CppImageProcessingOptions> image_processing_options) {
        ::mediapipe::tasks::vision::face_landmarker::FaceLandmarker* cppFaceLandmarker = static_cast<::mediapipe::tasks::vision::face_landmarker::FaceLandmarker*>(faceLandmarker->getFaceLandmarker());
        absl::StatusOr<::mediapipe::tasks::vision::face_landmarker::FaceLandmarkerResult> result_status = cppFaceLandmarker->Detect(image, image_processing_options);
        if (!result_status.ok()) {
            std::cerr << "Detection failed: " << result_status.status().message() << std::endl;
            // return nullptr;
            return FaceLandmarkerResult();
        }
        ::mediapipe::tasks::vision::face_landmarker::FaceLandmarkerResult cppResult = result_status.value();
        return *reinterpret_cast<const libmptask::FaceLandmarkerResult*>(&cppResult);
    }

    /*absl::StatusOr<FaceLandmarkerResult> DetectForVideo(
        Image image, int64_t timestamp_ms,
        std::optional<core::ImageProcessingOptions> image_processing_options =
        std::nullopt);*/
    FaceLandmarkerResult cppDetectForVideo(const FaceLandmarker* faceLandmarker, const ::mediapipe::Image& image, int64_t timestamp_ms, std::optional<CppImageProcessingOptions> image_processing_options) {
        ::mediapipe::tasks::vision::face_landmarker::FaceLandmarker* cppFaceLandmarker = static_cast<::mediapipe::tasks::vision::face_landmarker::FaceLandmarker*>(faceLandmarker->getFaceLandmarker());
        absl::StatusOr<::mediapipe::tasks::vision::face_landmarker::FaceLandmarkerResult> result_status = cppFaceLandmarker->DetectForVideo(image, timestamp_ms, image_processing_options);
        if (!result_status.ok()) {
            std::cerr << "Detection failed: " << result_status.status().message() << std::endl;
            // return nullptr;
            return FaceLandmarkerResult();
        }
        ::mediapipe::tasks::vision::face_landmarker::FaceLandmarkerResult cppResult = result_status.value();
        return *reinterpret_cast<const libmptask::FaceLandmarkerResult*>(&cppResult);
    }

    /*absl::Status DetectAsync(Image image, int64_t timestamp_ms,
        std::optional<core::ImageProcessingOptions>
        image_processing_options = std::nullopt);*/
    int cppDetectAsync(const FaceLandmarker* faceLandmarker, const ::mediapipe::Image& image, int64_t timestamp_ms,  std::optional<CppImageProcessingOptions> image_processing_options) {
        ::mediapipe::tasks::vision::face_landmarker::FaceLandmarker* cppFaceLandmarker = static_cast<::mediapipe::tasks::vision::face_landmarker::FaceLandmarker*>(faceLandmarker->getFaceLandmarker());
        absl::Status result_status = cppFaceLandmarker->DetectAsync(image, timestamp_ms, image_processing_options);
        if (!result_status.ok()) {
            std::cerr << "Detection failed: " << result_status.message() << std::endl;
            // return nullptr;
            return -1;
        }
        return 0;
    }

    //// Shuts down the FaceLandmarker when all works are done.
    //absl::Status Close() { return runner_->Close(); }
    int cppClose(const FaceLandmarker* faceLandmarker) {
        ::mediapipe::tasks::vision::face_landmarker::FaceLandmarker* cppFaceLandmarker = static_cast<::mediapipe::tasks::vision::face_landmarker::FaceLandmarker*>(faceLandmarker->getFaceLandmarker());
        absl::Status result_status = cppFaceLandmarker->Close();
        if (!result_status.ok()) {
            std::cerr << "Detection failed: " << result_status.message() << std::endl;
            // return nullptr;
            return -1;
        }
        return 0;
    }

    int CppProcessError(absl::Status status, char** error_msg) {
        if (error_msg) {
            *error_msg = strdup(status.ToString().c_str());
        }
        return status.raw_code();
    }

    void CppConvertToFaceLandmarkerOptions(const FaceLandmarkerOptions& in, ::mediapipe::tasks::vision::face_landmarker::FaceLandmarkerOptions* out) {
        out->num_faces = in.num_faces;
        out->min_face_detection_confidence = in.min_face_detection_confidence;
        out->min_face_presence_confidence = in.min_face_presence_confidence;
        out->min_tracking_confidence = in.min_tracking_confidence;
        out->output_face_blendshapes = in.output_face_blendshapes;
        out->output_facial_transformation_matrixes =
            in.output_facial_transformation_matrixes;
    }

    MP_CPP_EXPORT FaceLandmarker* FaceLandmarker::create(FaceLandmarkerOptions& options, char** error_msg) {
        auto cpp_options = std::make_unique<::mediapipe::tasks::vision::face_landmarker::FaceLandmarkerOptions>();
        
        CppConvertToBaseOptions(options.base_options, &cpp_options->base_options);
        CppConvertToFaceLandmarkerOptions(options, cpp_options.get());
        cpp_options->running_mode = static_cast<::mediapipe::tasks::vision::core::RunningMode>(options.running_mode);


        // Enable callback for processing live stream data when the running mode is
        // set to RunningMode::LIVE_STREAM.
        if (cpp_options->running_mode == RunningMode::LIVE_STREAM) {
            if (options.result_callback == nullptr) {
                const absl::Status status = absl::InvalidArgumentError("Provided null pointer to callback function.");
                ABSL_LOG(ERROR) << "Failed to create FaceLandmarker: " << status;
                CppProcessError(status, error_msg);
                return nullptr;
            }

            FaceLandmarkerOptions::result_callback_fn result_callback = options.result_callback;

            cpp_options->result_callback = [result_callback](absl::StatusOr<CppFaceLandmarkerResult> cpp_result, const ::mediapipe::Image& image, int64_t timestamp) {
                char* error_msg = nullptr;

                if (!cpp_result.ok()) {
                    ABSL_LOG(ERROR) << "Detection failed: " << cpp_result.status();
                    CppProcessError(cpp_result.status(), &error_msg);
                    result_callback(nullptr, nullptr, timestamp, error_msg);
                    free(error_msg);
                    return;
                }

                CppFaceLandmarkerResult cppResult = cpp_result.value();
                FaceLandmarkerResult* result = reinterpret_cast<FaceLandmarkerResult*>(&cppResult);

                const auto& image_frame = image.GetImageFrameSharedPtr();
                MpImage mp_image;
                mp_image.type = MpImage::IMAGE_FRAME;
                mp_image.image_frame.format = cppImageFormatToImageFormat(image_frame->Format());
                mp_image.image_frame.image_buffer = image_frame->PixelData();
                mp_image.image_frame.width = image_frame->Width();
                mp_image.image_frame.height = image_frame->Height();

                result_callback(result, &mp_image, timestamp, /* error_msg= */ nullptr);
            };
        }

        auto landmarker = ::mediapipe::tasks::vision::face_landmarker::FaceLandmarker::Create(std::move(cpp_options));
        if (!landmarker.ok()) {
            ABSL_LOG(ERROR) << "Failed to create FaceLandmarker: "
                << landmarker.status();
            CppProcessError(landmarker.status(), error_msg);
            return nullptr;
        }

        FaceLandmarker* faceLandmarker = new FaceLandmarker();
        faceLandmarker->faceLandmarker = landmarker->release();

        return faceLandmarker;
    }

    FaceLandmarker::FaceLandmarker() {

    }

    FaceLandmarker::~FaceLandmarker() {
        // 使用别名以避免与成员变量 face_landmarker 混淆
        namespace mp_face = ::mediapipe::tasks::vision::face_landmarker;

        // 转换 this->face_landmarker，确保编译器将它识别为成员变量
        auto cpp_landmarker = static_cast<mp_face::FaceLandmarker*>(this->faceLandmarker);


        //auto cpp_landmarker = static_cast<mediapipe::tasks::vision::face_landmarker::FaceLandmarker*>(this->face_landmarker);
        auto result = cpp_landmarker->Close();
        if (!result.ok()) {
            ABSL_LOG(ERROR) << "Failed to close FaceLandmarker: " << result;
            return;
        }
        delete cpp_landmarker;
    }

    FaceLandmarkerResult FaceLandmarker::detect(const char* path, std::optional<ImageProcessingOptions> image_processing_options) {
        absl::StatusOr <::mediapipe::Image> image_status = DecodeImageFromFile(path);
        if (!image_status.ok()) {
            std::cerr << "Failed to load image: " << image_status.status().message() << std::endl;
            //return nullptr;
            return FaceLandmarkerResult();
        }
        return cppDetect(this, image_status.value(), *reinterpret_cast<std::optional<CppImageProcessingOptions>*>(&image_processing_options));
    }

    FaceLandmarkerResult FaceLandmarker::detect(const uint8_t* pixel_data, int width, int height, int channels, std::optional<ImageProcessingOptions> image_processing_options) {
        absl::StatusOr <::mediapipe::Image> image_status = CreateImageFromBuffer(pixel_data, width, height, channels);
        if (!image_status.ok()) {
            std::cerr << "Failed to load image: " << image_status.status().message() << std::endl;
            //return nullptr;
            return FaceLandmarkerResult();
        }
        return cppDetect(this, image_status.value(), *reinterpret_cast<std::optional<CppImageProcessingOptions>*>(&image_processing_options));
    }

    FaceLandmarkerResult FaceLandmarker::detect(const uint8_t* pixel_data, int width, int height, ImageFormat format, std::optional<ImageProcessingOptions> image_processing_options) {
        absl::StatusOr <::mediapipe::Image> image_status = CreateImageFromBuffer(pixel_data, width, height, imageFormatToCppImageFormat(format));
        if (!image_status.ok()) {
            std::cerr << "Failed to load image: " << image_status.status().message() << std::endl;
            //return nullptr;
            return FaceLandmarkerResult();
        }
        return cppDetect(this, image_status.value(), *reinterpret_cast<std::optional<CppImageProcessingOptions>*>(&image_processing_options));
    }

    FaceLandmarkerResult FaceLandmarker::detectForVideo(const uint8_t* pixel_data, int width, int height, int channels, int64_t timestamp_ms, std::optional<ImageProcessingOptions> image_processing_options) {
        absl::StatusOr <::mediapipe::Image> image_status = CreateImageFromBuffer(pixel_data, width, height, channels);
        if (!image_status.ok()) {
            std::cerr << "Failed to load image: " << image_status.status().message() << std::endl;
            //return nullptr;
            return FaceLandmarkerResult();
        }
        return cppDetectForVideo(this, image_status.value(), timestamp_ms, *reinterpret_cast<std::optional<CppImageProcessingOptions>*>(&image_processing_options));
    }

    FaceLandmarkerResult FaceLandmarker::detectForVideo(const uint8_t* pixel_data, int width, int height, ImageFormat format, int64_t timestamp_ms, std::optional<ImageProcessingOptions> image_processing_options) {
        absl::StatusOr <::mediapipe::Image> image_status = CreateImageFromBuffer(pixel_data, width, height, imageFormatToCppImageFormat(format));
        if (!image_status.ok()) {
            std::cerr << "Failed to load image: " << image_status.status().message() << std::endl;
            //return nullptr;
            return FaceLandmarkerResult();
        }
        return cppDetectForVideo(this, image_status.value(), timestamp_ms, *reinterpret_cast<std::optional<CppImageProcessingOptions>*>(&image_processing_options));
    }

    int FaceLandmarker::detectAsync(const uint8_t* pixel_data, int width, int height, int channels, int64_t timestamp_ms, std::optional<ImageProcessingOptions> image_processing_options) {
        absl::StatusOr <::mediapipe::Image> image_status = CreateImageFromBuffer(pixel_data, width, height, channels);
        if (!image_status.ok()) {
            std::cerr << "Failed to load image: " << image_status.status().message() << std::endl;
            //return nullptr;
            return -1;
        }
        return cppDetectAsync(this, image_status.value(), timestamp_ms, *reinterpret_cast<std::optional<CppImageProcessingOptions>*>(&image_processing_options));
    }

    int FaceLandmarker::detectAsync(const uint8_t* pixel_data, int width, int height, ImageFormat format, int64_t timestamp_ms, std::optional<ImageProcessingOptions> image_processing_options) {
        absl::StatusOr <::mediapipe::Image> image_status = CreateImageFromBuffer(pixel_data, width, height, imageFormatToCppImageFormat(format));
        if (!image_status.ok()) {
            std::cerr << "Failed to load image: " << image_status.status().message() << std::endl;
            //return nullptr;
            return -1;
        }
        return cppDetectAsync(this, image_status.value(), timestamp_ms, *reinterpret_cast<std::optional<CppImageProcessingOptions>*>(&image_processing_options));
    }

    void FaceLandmarker::close() {
        cppClose(this);
    }
}