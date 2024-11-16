//
// Created by leixing on 2024/11/5.
//

#ifndef LIB_MP_TASK_FACE_LANDMARK_H
#define LIB_MP_TASK_FACE_LANDMARK_H

#include <stddef.h>
#include <stdint.h>

#include <string>
#include "mediapipe/tasks/libmptask/core/base_options.h"
#include "mediapipe/tasks/libmptask/vision/core/common.h"
#include "mediapipe/tasks/libmptask/vision/core/image_processing_options.h"
#include "mediapipe/tasks/libmptask/vision/face_landmarker/face_landmarker_result.h"
#include "mediapipe/tasks/libmptask/vision/face_landmarker/face_landmarker_options.h"
#include "mediapipe/tasks/libmptask/utils/cpp_export.h"

namespace libmptask {

    class MP_CPP_API FaceLandmarkerApi {
    public:
        static FaceLandmarkerApi* create(FaceLandmarkerOptions& options, char** error_msg);


    private:
        void* faceLandmarker;
    

    public:
        FaceLandmarkerApi();

        ~FaceLandmarkerApi();

        inline void* getFaceLandmarker() const{
            return faceLandmarker;
        }

        FaceLandmarkerResult detect(const std::string& path, std::optional<ImageProcessingOptions> image_processing_options = std::nullopt) {
            return detect(path.c_str());
        }

        FaceLandmarkerResult detect(const char* path, std::optional<ImageProcessingOptions> image_processing_options = std::nullopt);

        FaceLandmarkerResult detect(const uint8_t* pixel_data, int width, int height, int channels, std::optional<ImageProcessingOptions> image_processing_options = std::nullopt);

        FaceLandmarkerResult detect(const uint8_t* pixel_data, int width, int height, ImageFormat format, std::optional<ImageProcessingOptions> image_processing_options = std::nullopt);

        FaceLandmarkerResult detectForVideo(const uint8_t* pixel_data, int width, int height, int channels, int64_t timestamp_ms, std::optional<ImageProcessingOptions> image_processing_options = std::nullopt);

        FaceLandmarkerResult detectForVideo(const uint8_t* pixel_data, int width, int height, ImageFormat format, int64_t timestamp_ms, std::optional<ImageProcessingOptions> image_processing_options = std::nullopt);

        int detectAsync(const uint8_t* pixel_data, int width, int height, int channels, int64_t timestamp_ms, std::optional<ImageProcessingOptions> image_processing_options = std::nullopt);

        int detectAsync(const uint8_t* pixel_data, int width, int height, ImageFormat format, int64_t timestamp_ms, std::optional<ImageProcessingOptions> image_processing_options = std::nullopt);

        int close();
    };
}


#endif //LIB_MP_TASK_FACE_LANDMARK_H
