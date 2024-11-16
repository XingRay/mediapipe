/* Copyright 2023 The MediaPipe Authors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef MEDIAPIPE_TASKS_LIBMPTASK_VISION_FACE_LANDMARKER_FACE_LANDMARKER_H_
#define MEDIAPIPE_TASKS_LIBMPTASK_VISION_FACE_LANDMARKER_FACE_LANDMARKER_H_

#include <memory>
#include <optional>
#include <vector>

#include "absl/status/statusor.h"
#include "mediapipe/framework/formats/image.h"
#include "mediapipe/tasks/cc/vision/core/base_vision_task_api.h"

#include "mediapipe/tasks/libmptask/vision/face_landmarker/face_landmarker_result.h"
#include "mediapipe/tasks/libmptask/vision/face_landmarker/face_landmarker_options.h"
#include "mediapipe/tasks/libmptask/vision/core/image_processing_options.h"
#include "mediapipe/tasks/libmptask/vision/core/common.h"

namespace libmptask {

// Performs face landmarks detection on the given image.
//
// TODO  add the link to DevSite.
// This API expects a pre-trained face landmarker model asset bundle.
//
// Inputs:
//   Image
//     - The image that face landmarks detection runs on.
//   std::optional<NormalizedRect>
//     - If provided, can be used to specify the rotation to apply to the image
//       before performing face landmarks detection, by setting its 'rotation'
//       field in radians (e.g. 'M_PI / 2' for a 90° anti-clockwise rotation).
//       Note that specifying a region-of-interest using the 'x_center',
//       'y_center', 'width' and 'height' fields is NOT supported and will
//       result in an invalid argument error being returned.
// Outputs:
//   FaceLandmarkerResult
//     - The face landmarks detection results.

class FaceLandmarker : ::mediapipe::tasks::vision::core::BaseVisionTaskApi {
 public:
  using BaseVisionTaskApi::BaseVisionTaskApi;

  // Creates a FaceLandmarker from a FaceLandmarkerOptions to process image data
  // or streaming data. Face landmarker can be created with one of the following
  // three running modes:
  // 1) Image mode for detecting face landmarks on single image inputs. Users
  //    provide mediapipe::Image to the `Detect` method, and will receive the
  //    detected face landmarks results as the return value.
  // 2) Video mode for detecting face landmarks on the decoded frames of a
  //    video. Users call `DetectForVideo` method, and will receive the detected
  //    face landmarks results as the return value.
  // 3) Live stream mode for detecting face landmarks on the live stream of the
  //    input data, such as from camera. Users call `DetectAsync` to push the
  //    image data into the FaceLandmarker, the detected results along with the
  //    input timestamp and the image that face landmarker runs on will be
  //    available in the result callback when the face landmarker finishes the
  //    work.
  static absl::StatusOr<std::unique_ptr<FaceLandmarker>> Create(std::unique_ptr<FaceLandmarkerOptions> options);

  // Performs face landmarks detection on the given image.
  // Only use this method when the FaceLandmarker is created with the image
  // running mode.
  //
  // The optional 'image_processing_options' parameter can be used to specify
  // the rotation to apply to the image before performing detection, by setting
  // its 'rotation_degrees' field. Note that specifying a region-of-interest
  // using the 'region_of_interest' field is NOT supported and will result in an
  // invalid argument error being returned.
  //
  // The image can be of any size with format RGB or RGBA.
  // TODO: Describes how the input image will be preprocessed
  // after the yuv support is implemented.
  absl::StatusOr<FaceLandmarkerResult> Detect(::mediapipe::Image image, std::optional<ImageProcessingOptions> image_processing_options = std::nullopt);

  // Performs face landmarks detection on the provided video frame.
  // Only use this method when the FaceLandmarker is created with the video
  // running mode.
  //
  // The optional 'image_processing_options' parameter can be used to specify
  // the rotation to apply to the image before performing detection, by setting
  // its 'rotation_degrees' field. Note that specifying a region-of-interest
  // using the 'region_of_interest' field is NOT supported and will result in an
  // invalid argument error being returned.
  //
  // The image can be of any size with format RGB or RGBA. It's required to
  // provide the video frame's timestamp (in milliseconds). The input timestamps
  // must be monotonically increasing.
  absl::StatusOr<FaceLandmarkerResult> DetectForVideo(::mediapipe::Image image, int64_t timestamp_ms, std::optional<ImageProcessingOptions> image_processing_options = std::nullopt);

  // Sends live image data to perform face landmarks detection, and the results
  // will be available via the "result_callback" provided in the
  // FaceLandmarkerOptions. Only use this method when the FaceLandmarker
  // is created with the live stream running mode.
  //
  // The image can be of any size with format RGB or RGBA. It's required to
  // provide a timestamp (in milliseconds) to indicate when the input image is
  // sent to the face landmarker. The input timestamps must be monotonically
  // increasing.
  //
  // The optional 'image_processing_options' parameter can be used to specify
  // the rotation to apply to the image before performing detection, by setting
  // its 'rotation_degrees' field. Note that specifying a region-of-interest
  // using the 'region_of_interest' field is NOT supported and will result in an
  // invalid argument error being returned.
  //
  // The "result_callback" provides
  //   - A vector of FaceLandmarkerResult, each is the detected results
  //     for a input frame.
  //   - The const reference to the corresponding input image that the face
  //     landmarker runs on. Note that the const reference to the image will no
  //     longer be valid when the callback returns. To access the image data
  //     outside of the callback, callers need to make a copy of the image.
  //   - The input timestamp in milliseconds.
  absl::Status DetectAsync(::mediapipe::Image image, int64_t timestamp_ms, std::optional<ImageProcessingOptions>image_processing_options = std::nullopt);

  // Shuts down the FaceLandmarker when all works are done.
  absl::Status Close() { return runner_->Close(); }
};

}  // namespace libmptask

#endif  // MEDIAPIPE_TASKS_LIBMPTASK_VISION_FACE_LANDMARKER_FACE_LANDMARKER_H_
