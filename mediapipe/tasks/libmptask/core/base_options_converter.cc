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

#include "mediapipe/tasks/libmptask/core/base_options_converter.h"

#include <memory>
#include <string>
#include <variant>

#include "absl/log/absl_log.h"
#include "mediapipe/calculators/tensor/inference_calculator.pb.h"
#include "mediapipe/tasks/cc/core/proto/acceleration.pb.h"
#include "mediapipe/tasks/cc/core/proto/base_options.pb.h"
#include "mediapipe/tasks/cc/core/proto/external_file.pb.h"

namespace libmptask {

// c -> cpp
void CppConvertToBaseOptions(const BaseOptions& in,
                             mediapipe::tasks::core::BaseOptions* out) {
  out->model_asset_buffer =
      in.model_asset_buffer
          ? std::make_unique<std::string>(
                in.model_asset_buffer,
                in.model_asset_buffer + in.model_asset_buffer_count)
          : nullptr;
  out->model_asset_path =
      in.model_asset_path ? std::string(in.model_asset_path) : "";
}

// c-> cpp -> proto
mediapipe::tasks::core::proto::BaseOptions baseOptionsConvertToProto(BaseOptions* base_options){
    mediapipe::tasks::core::BaseOptions cppBaseOptions;
    CppConvertToBaseOptions(*base_options, &cppBaseOptions);
    return ConvertBaseOptionsToProto(&cppBaseOptions);
}

}  // namespace mediapipe::tasks::c::core
