
/* Copyright 2022 The MediaPipe Authors.

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

#ifndef MEDIAPIPE_TASKS_LIBMPTASK_COMPONENTS_CONTAINERS_CLASSIFICATION_RESULT_CONVERTER_H_
#define MEDIAPIPE_TASKS_LIBMPTASK_COMPONENTS_CONTAINERS_CLASSIFICATION_RESULT_CONVERTER_H_

#include <optional>
#include <string>
#include <vector>

#include "mediapipe/framework/formats/classification.pb.h"
#include "mediapipe/tasks/cc/components/containers/proto/classifications.pb.h"

#include "mediapipe/tasks/libmptask/components/containers/category.h"
#include "mediapipe/tasks/libmptask/components/containers/classification_result.h"

namespace libmptask{

    // Utility function to convert from Classifications proto to
// Classifications struct.
Classifications ConvertToClassifications(const ::mediapipe::tasks::components::containers::proto::Classifications& proto);

// Utility function to convert from ClassificationList proto to
// Classifications struct.
Classifications ConvertToClassifications(
    const mediapipe::ClassificationList& proto, int head_index = 0,
    std::optional<std::string> head_name = std::nullopt);

// Utility function to convert from ClassificationResult proto to
// ClassificationResult struct.
ClassificationResult ConvertToClassificationResult(
    const ::mediapipe::tasks::components::containers::proto::ClassificationResult& proto);

}


#endif  // MEDIAPIPE_TASKS_LIBMPTASK_COMPONENTS_CONTAINERS_CLASSIFICATION_RESULT_CONVERTER_H_