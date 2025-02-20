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

#ifndef MEDIAPIPE_TASKS_C_CORE_BASE_OPTIONS_CONVERTER_H_
#define MEDIAPIPE_TASKS_C_CORE_BASE_OPTIONS_CONVERTER_H_

#include "mediapipe/tasks/libmptask/core/base_options.h"
#include "mediapipe/tasks/cc/core/base_options.h"
#include "mediapipe/tasks/cc/core/proto/base_options.pb.h"

namespace libmptask {

void CppConvertToBaseOptions(const BaseOptions& in,
                             mediapipe::tasks::core::BaseOptions* out);

mediapipe::tasks::core::proto::BaseOptions baseOptionsConvertToProto(BaseOptions* base_options);

}  // namespace libmptask

#endif  // MEDIAPIPE_TASKS_C_CORE_BASE_OPTIONS_H_
