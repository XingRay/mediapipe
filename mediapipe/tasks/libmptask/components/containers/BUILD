# Copyright 2022 The MediaPipe Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

cc_library(
    name = "keypoint",
    srcs = [],
    hdrs = ["keypoint.h"],
    deps = [
        
    ],
)

cc_library(
    name = "rect",
    srcs = ["rect.cc"],
    hdrs = ["rect.h"],
    deps = [
        
    ],
)

cc_library(
    name = "rect_converter",
    srcs = ["rect_converter.cc"],
    hdrs = ["rect_converter.h"],
    deps = [
        "//mediapipe/tasks/libmptask/components/containers:rect",
        "//mediapipe/tasks/cc/components/containers:rect",
    ],
)

cc_library(
    name = "category",
    srcs = [],
    hdrs = ["category.h"],
    deps = [
        
    ],
)

cc_library(
    name = "category_converter",
    srcs = ["category_converter.cc"],
    hdrs = ["category_converter.h"],
    deps = [
        "//mediapipe/tasks/libmptask/components/containers:category",
        "//mediapipe/framework/formats:classification_cc_proto",
    ],
)

cc_library(
    name = "classification_result",
    srcs = [],
    hdrs = ["classification_result.h"],
    deps = [
        ":category",
    ],
)

cc_library(
    name = "classification_result_converter",
    srcs = ["classification_result_converter.cc"],
    hdrs = ["classification_result_converter.h"],
    deps = [
        "//mediapipe/tasks/libmptask/components/containers:classification_result",
        "//mediapipe/tasks/cc/components/containers:classification_result",
        "//mediapipe/tasks/libmptask/components/containers:category_converter",
    ],
)

cc_library(
    name = "detection_result",
    srcs = [],
    hdrs = ["detection_result.h"],
    deps = [
        ":category",
        ":keypoint",
        ":rect",
    ],
)

cc_library(
    name = "embedding_result",
    srcs = [],
    hdrs = ["embedding_result.h"],
    deps = [
        
    ],
)

cc_library(
    name = "landmark",
    srcs = [],
    hdrs = ["landmark.h"],
    deps = [
        
    ],
)

cc_library(
    name = "landmark_converter",
    srcs = ["landmark_converter.cc"],
    hdrs = ["landmark_converter.h"],
    deps = [
        ":landmark",
        "//mediapipe/tasks/libmptask/components/containers:classification_result_converter",
        "//mediapipe/framework/formats:landmark_cc_proto"
    ],
)

cc_library(
    name = "matrix",
    srcs = ["matrix.cc"],
    hdrs = ["matrix.h"],
    deps = [
        "//mediapipe/tasks/libmptask/utils:cpp_export",
    ],
)

cc_library(
    name = "matrix_converter",
    srcs = ["matrix_converter.cc"],
    hdrs = ["matrix_converter.h"],
    deps = [
        ":matrix",
        "//mediapipe/framework/formats:matrix_data_cc_proto"
    ],
)