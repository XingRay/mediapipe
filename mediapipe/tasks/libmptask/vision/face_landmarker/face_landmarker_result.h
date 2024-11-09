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

#ifndef MEDIAPIPE_TASKS_LIBMPTASK_VISION_FACE_LANDMARKER_FACE_LANDMARKER_RESULT_H_
#define MEDIAPIPE_TASKS_LIBMPTASK_VISION_FACE_LANDMARKER_FACE_LANDMARKER_RESULT_H_

#include <optional>
#include <vector>

#include "mediapipe/tasks/libmptask/components/containers/landmark.h"
#include "mediapipe/tasks/libmptask/components/containers/matrix.h"
#include "mediapipe/tasks/libmptask/components/containers/classification_result.h"


namespace libmptask {
// The face landmarks detection result from FaceLandmarker, where each vector
// element represents a single face detected in the image.
struct FaceLandmarkerResult {
  // Detected face landmarks in normalized image coordinates.
  std::vector<NormalizedLandmarks> face_landmarks;
  // Optional face blendshapes results.
  std::optional<std::vector<Classifications>>face_blendshapes;
  // Optional facial transformation matrix.
  std::optional<std::vector<Matrix>> facial_transformation_matrixes;
};

}  // namespace libmptask

#endif  // MEDIAPIPE_TASKS_LIBMPTASK_VISION_FACE_LANDMARKER_FACE_LANDMARKER_RESULT_H_
