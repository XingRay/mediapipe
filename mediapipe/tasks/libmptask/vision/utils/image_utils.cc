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
#include "mediapipe/tasks/libmptask/vision/utils/image_utils.h"

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"
#include "mediapipe/framework/formats/image.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/tensor.h"
#include "stb_image.h"

namespace libmptask {


absl::StatusOr<mediapipe::Image> DecodeImageFromFile(const std::string& path) {
    return DecodeImageFromFile(path.c_str());
}

absl::StatusOr<mediapipe::Image> DecodeImageFromFile(const char* path) {
  int width;
  int height;
  int channels;
  auto* image_data = stbi_load(path, &width, &height, &channels, /*desired_channels=*/0);
  if (image_data == nullptr) {
    return absl::InternalError(absl::StrFormat("Image decoding failed (%s): %s", stbi_failure_reason(), path));
  }
  mediapipe::ImageFrameSharedPtr image_frame;
  switch (channels) {
    case 1:
      image_frame = std::make_shared<mediapipe::ImageFrame>(mediapipe::ImageFormat::GRAY8, width, height, width, image_data, stbi_image_free);
      break;
    case 3:
      image_frame = std::make_shared<mediapipe::ImageFrame>(mediapipe::ImageFormat::SRGB, width, height, 3 * width, image_data, stbi_image_free);
      break;
    case 4:
      image_frame = std::make_shared<mediapipe::ImageFrame>(mediapipe::ImageFormat::SRGBA, width, height, 4 * width, image_data, stbi_image_free);
      break;
    default:
      return absl::InvalidArgumentError(absl::StrFormat("Expected image with 1 (grayscale), 3 (RGB) or 4 (RGBA) channels, found %d channels.", channels));
  }
  return mediapipe::Image(std::move(image_frame));
}

absl::StatusOr<mediapipe::Image> CreateImageFromBuffer(const uint8_t* image_data, int width, int height, int channels) {
    if (image_data == nullptr) {
        return absl::InternalError(absl::StrFormat("Image decoding failed, image_data  is null"));
    }
    mediapipe::ImageFrameSharedPtr image_frame;
    switch (channels) {
    case 1:
        image_frame = std::make_shared<mediapipe::ImageFrame>(mediapipe::ImageFormat::GRAY8, width, height, width, const_cast<uint8_t*>(image_data), mediapipe::ImageFrame::PixelDataDeleter::kNone);
        break;
    case 3:
        image_frame = std::make_shared<mediapipe::ImageFrame>(mediapipe::ImageFormat::SRGB, width, height, 3 * width, const_cast<uint8_t*>(image_data), mediapipe::ImageFrame::PixelDataDeleter::kNone);
        break;
    case 4:
        image_frame = std::make_shared<mediapipe::ImageFrame>(mediapipe::ImageFormat::SRGBA, width, height,4 * width, const_cast<uint8_t*>(image_data), mediapipe::ImageFrame::PixelDataDeleter::kNone);
        break;
    default:
        return absl::InvalidArgumentError(absl::StrFormat("Expected image with 1 (grayscale), 3 (RGB) or 4 (RGBA) channels, found %d channels.", channels));
    }
    return mediapipe::Image(std::move(image_frame));
}

absl::StatusOr<mediapipe::Image> CreateImageFromBuffer(const uint8_t* pixel_data, int width, int height, mediapipe::ImageFormat::Format format) {
    if (pixel_data == nullptr) {
        return absl::InternalError(absl::StrFormat("Image decoding failed, pixel_data  is null"));
    }
    int width_step = 0;
    switch (format) {
    case mediapipe::ImageFormat::GRAY8:
        width_step = width;
        break;
    case mediapipe::ImageFormat::SRGB:
        width_step = 3 * width;
        break;
    case mediapipe::ImageFormat::SRGBA:
        width_step = 4 * width;
        break;
    case mediapipe::ImageFormat::SBGRA:
        width_step = 4 * width;
        break;
    default:
        return absl::InvalidArgumentError(absl::StrFormat("Expected image of SRGB, SRGBA or SBGRA format, but found %d.",format));
    }

    mediapipe::ImageFrameSharedPtr image_frame = std::make_shared<mediapipe::ImageFrame>(format, width, height, width_step, const_cast<uint8_t*>(pixel_data), mediapipe::ImageFrame::PixelDataDeleter::kNone);

    return mediapipe::Image(std::move(image_frame));
}

}  // namespace libmptask
