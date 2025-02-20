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

#include "mediapipe/tasks/libmptask/vision/face_landmarker/face_landmarker_result_converter.h"
// #include "mediapipe/tasks/libmptask/vision/face_landmarker/face_landmarker_result.h"

#include <algorithm>

// #include "mediapipe/framework/formats/classification.pb.h"
// #include "mediapipe/framework/formats/landmark.pb.h"
// #include "mediapipe/framework/formats/matrix.h"
// #include "mediapipe/framework/formats/matrix_data.pb.h"

#include "mediapipe/tasks/libmptask/components/containers/classification_result.h"
#include "mediapipe/tasks/libmptask/components/containers/classification_result_converter.h"
#include "mediapipe/tasks/libmptask/components/containers/landmark.h"
#include "mediapipe/tasks/libmptask/components/containers/landmark_converter.h"
#include "mediapipe/tasks/libmptask/components/containers/matrix.h"
#include "mediapipe/tasks/libmptask/components/containers/matrix_converter.h"

namespace libmptask{

// result: proto -> cpp
FaceLandmarkerResult ConvertToFaceLandmarkerResult(
    std::vector<mediapipe::NormalizedLandmarkList> face_landmarks_proto,
    std::optional<std::vector<mediapipe::ClassificationList>> face_blendshapes_proto,
    std::optional<std::vector<mediapipe::MatrixData>> facial_transformation_matrixes_proto) {

  FaceLandmarkerResult result;
  result.face_landmarks.resize(face_landmarks_proto.size());
  std::transform(face_landmarks_proto.begin(), face_landmarks_proto.end(),result.face_landmarks.begin(),ConvertToNormalizedLandmarks);
  
  if (face_blendshapes_proto.has_value()) {
    result.face_blendshapes = std::vector<Classifications>(face_blendshapes_proto->size());
    std::transform(face_blendshapes_proto->begin(), face_blendshapes_proto->end(), result.face_blendshapes->begin(),
        [](const mediapipe::ClassificationList& classification_list) {
          return ConvertToClassifications(classification_list);
        });
  }

  if (facial_transformation_matrixes_proto.has_value()) {
    result.facial_transformation_matrixes = std::vector<Matrix>(facial_transformation_matrixes_proto->size());
    std::transform(facial_transformation_matrixes_proto->begin(),
                   facial_transformation_matrixes_proto->end(),
                   result.facial_transformation_matrixes->begin(),
                   [](const mediapipe::MatrixData& matrix_proto) {
                     Matrix matrix;
                     MatrixFromMatrixDataProto(matrix_proto, &matrix);
                     return matrix;
                   });
  }
  return result;
}

}
