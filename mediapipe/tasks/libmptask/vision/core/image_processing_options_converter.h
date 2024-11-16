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

#ifndef MEDIAPIPE_TASKS_LIBMPTASK_VISION_CORE_IMAGE_PROCESSING_OPTIONS_CONVERTER_H_
#define MEDIAPIPE_TASKS_LIBMPTASK_VISION_CORE_IMAGE_PROCESSING_OPTIONS_CONVERTER_H_

#include "mediapipe/tasks/libmptask/vision/core/image_processing_options.h"
#include "mediapipe/tasks/cc/vision/core/image_processing_options.h"

namespace libmptask{

void cppConvertImageProcessingOptions(ImageProcessingOptions& options, ::mediapipe::tasks::vision::core::ImageProcessingOptions* cppOptions);

}

#endif // MEDIAPIPE_TASKS_LIBMPTASK_VISION_CORE_IMAGE_PROCESSING_OPTIONS_CONVERTER_H_