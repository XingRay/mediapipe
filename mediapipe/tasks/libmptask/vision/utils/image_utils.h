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

#ifndef MEDIAPIPE_TASKS_LIBMPTASK_VISION_UTILS_IMAGE_UTILS_H_
#define MEDIAPIPE_TASKS_LIBMPTASK_VISION_UTILS_IMAGE_UTILS_H_

#include <cstdint>
#include <memory>
#include <string>

#include "absl/status/statusor.h"
#include "mediapipe/framework/formats/image.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/tensor.h"

namespace libmptask {

// Decodes an image file and returns it as a mediapipe::Image object.
//
// Support a wide range of image formats (see stb_image.h for the full list), as
// long as the image data is grayscale (1 channel), RGB (3 channels) or RGBA (4
// channels).
//
// Note: this function is not optimized for speed, and thus shouldn't be used
// outside of tests or simple CLI demo tools.
absl::StatusOr<::mediapipe::Image> DecodeImageFromFile(const char* path);


absl::StatusOr<::mediapipe::Image> DecodeImageFromFile(const std::string& path);

// Creates an image and returns it as a mediapipe::Image object.
//
// Support a wide range of image formats, namely grayscale (1 channel), RGB (3
// channels) or RGBA (4 channels) and BGRA (4 channels).
absl::StatusOr<mediapipe::Image> CreateImageFromBuffer(const uint8_t* image_data, int width, int height, int channels);

// Creates an image and returns it as a mediapipe::Image object.
//
// Support a wide range of image formats, namely grayscale (1 channel), RGB (3
// channels) or RGBA (4 channels) and BGRA (4 channels).
absl::StatusOr<mediapipe::Image> CreateImageFromBuffer(const uint8_t* pixel_data, int width, int height, mediapipe::ImageFormat::Format format);

}  // namespace libmptask

#endif  // MEDIAPIPE_TASKS_LIBMPTASK_VISION_UTILS_IMAGE_UTILS_H_
