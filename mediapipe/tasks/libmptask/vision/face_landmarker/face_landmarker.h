//
// Created by leixing on 2024/11/5.
//

#ifndef LIB_MP_TASK_FACE_LANDMARK_H
#define LIB_MP_TASK_FACE_LANDMARK_H

#include <stddef.h>
#include <stdint.h>

// Windows DLL
#if _WIN32
#define MP_CPP_EXPORT __declspec(dllexport)  // DLL Export
#if defined(COMPILING_DLL)
#define MP_CPP_API __declspec(dllexport)  // DLL Export
#else
#define MP_CPP_API __declspec(dllimport)  // DLL Import
#endif
#else
// Linux SO
#define MP_CPP_EXPORT __attribute__((visibility("default")))  
#define MP_CPP_API
#endif

#include <string>
#include "mediapipe/tasks/libmptask/core/base_options.h"
#include "mediapipe/tasks/libmptask/vision/core/common.h"
#include "mediapipe/tasks/libmptask/vision/core/image_processing_options.h"
#include "mediapipe/tasks/libmptask/vision/face_landmarker/face_landmarker_result.h"

namespace libmptask {

    struct FaceLandmarkerOptions {
        // Base options for configuring MediaPipe Tasks, such as specifying the model
        // file with metadata, accelerator options, op resolver, etc.
        struct BaseOptions base_options;

        // The running mode of the task. Default to the image mode.
        // FaceLandmarker has three running modes:
        // 1) The image mode for recognizing face landmarks on single image inputs.
        // 2) The video mode for recognizing face landmarks on the decoded frames of a
        //    video.
        // 3) The live stream mode for recognizing face landmarks on the live stream
        //    of input data, such as from camera. In this mode, the "result_callback"
        //    below must be specified to receive the detection results asynchronously.
        RunningMode running_mode;

        // The maximum number of faces can be detected by the FaceLandmarker.
        int num_faces = 1;

        // The minimum confidence score for the face detection to be considered
        // successful.
        float min_face_detection_confidence = 0.5;

        // The minimum confidence score of face presence score in the face landmark
        // detection.
        float min_face_presence_confidence = 0.5;

        // The minimum confidence score for the face tracking to be considered
        // successful.
        float min_tracking_confidence = 0.5;

        // Whether FaceLandmarker outputs face blendshapes classification. Face
        // blendshapes are used for rendering the 3D face model.
        bool output_face_blendshapes = false;

        // Whether FaceLandmarker outputs facial transformation_matrix. Facial
        // transformation matrix is used to transform the face landmarks in canonical
        // face to the detected face, so that users can apply face effects on the
        // detected landmarks.
        bool output_facial_transformation_matrixes = false;

        // The user-defined result callback for processing live stream data.
        // The result callback should only be specified when the running mode is set
        // to RunningMode::LIVE_STREAM. Arguments of the callback function include:
        // the pointer to recognition result, the image that result was obtained
        // on, the timestamp relevant to recognition results and pointer to error
        // message in case of any failure. The validity of the passed arguments is
        // true for the lifetime of the callback function.
        //
        // The passed `image` is only valid for the lifetime of the call. A caller is
        // responsible for closing the face landmarker result.
        typedef void (*result_callback_fn)(FaceLandmarkerResult* result,const MpImage* image, int64_t timestamp_ms,char* error_msg);
        result_callback_fn result_callback;
    };


    class MP_CPP_API FaceLandmarker {
    public:
        static FaceLandmarker* create(FaceLandmarkerOptions& options, char** error_msg);


    private:
        void* faceLandmarker;
    

    public:
        FaceLandmarker();

        ~FaceLandmarker();

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

        void close();
    };
}


#endif //LIB_MP_TASK_FACE_LANDMARK_H
