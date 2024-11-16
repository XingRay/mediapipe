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

#ifndef MEDIAPIPE_TASKS_LIBMPTASK_COMPONENTS_CONTAINERS_LANDMARK_CONVERTER_H_
#define MEDIAPIPE_TASKS_LIBMPTASK_COMPONENTS_CONTAINERS_LANDMARK_CONVERTER_H_

#include "mediapipe/tasks/libmptask/components/containers/landmark.h"
#include "mediapipe/framework/formats/landmark.pb.h"

namespace libmptask{
// Utility function to convert from Landmark proto to Landmark struct.
Landmark ConvertToLandmark(const ::mediapipe::Landmark& proto);

// Utility function to convert from NormalizedLandmark proto to
// NormalizedLandmark struct.
NormalizedLandmark ConvertToNormalizedLandmark(const ::mediapipe::NormalizedLandmark& proto);

// Utility function to convert from LandmarkList proto to Landmarks struct.
Landmarks ConvertToLandmarks(const ::mediapipe::LandmarkList& proto);

// Utility function to convert from NormalizedLandmarkList proto to
// NormalizedLandmarks struct.
NormalizedLandmarks ConvertToNormalizedLandmarks(const ::mediapipe::NormalizedLandmarkList& proto);
}


#endif // MEDIAPIPE_TASKS_LIBMPTASK_COMPONENTS_CONTAINERS_LANDMARK_CONVERTER_H_