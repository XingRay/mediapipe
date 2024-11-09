# Copyright 2023 The MediaPipe Authors.
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
licenses(["notice"])

package(default_visibility = ["//mediapipe/tasks:__subpackages__"])

BIN_DATA = [
    
]

LIB_DEPS = [
    # Deps for libmp_impl.cpp
    "//mediapipe/framework/port:parse_text_proto",
    "@com_google_absl//absl/flags:parse",

    # Remove any of these if you need to build only one example
    # Selfie segmentation
    "//mediapipe/graphs/selfie_segmentation:selfie_segmentation_cpu_deps",

    # Hand tracking
    "//mediapipe/modules/hand_landmark:hand_landmark_tracking_cpu",
    "//mediapipe/calculators/util:annotation_overlay_calculator",
    "//mediapipe/calculators/util:detections_to_render_data_calculator",

    # Face detection
    "//mediapipe/graphs/face_detection:face_detection_full_range_desktop_live_deps",

    # Face mesh
    "//mediapipe/graphs/face_mesh:desktop_live_calculators",

    # Face geometry (thanks, @oUp2Uo!)
    # - Fixes from https://github.com/google/mediapipe/issues/2867 have been applied,
    #   allowing for use of face mesh with attention (discards the 10 iris landmarks)
    # - See https://github.com/google/mediapipe/issues/1162#issuecomment-1434268379 for details
    "//mediapipe/modules/face_geometry:face_geometry_from_detection",
    "//mediapipe/modules/face_geometry:env_generator_calculator",
    "//mediapipe/modules/face_geometry:geometry_pipeline_calculator",

    # Hair segmentation
    "//mediapipe/graphs/hair_segmentation:desktop_calculators",

    # Holistic tracking
    "//mediapipe/graphs/holistic_tracking:holistic_tracking_cpu_graph_deps",

    # Iris tracking
    "//mediapipe/graphs/iris_tracking:iris_tracking_cpu_deps",

    # Object detection
    "//mediapipe/calculators/core:concatenate_vector_calculator",
    "//mediapipe/calculators/core:flow_limiter_calculator",
    "//mediapipe/calculators/core:previous_loopback_calculator",
    "//mediapipe/calculators/core:split_vector_calculator",
    "//mediapipe/calculators/image:image_transformation_calculator",
    "//mediapipe/calculators/tflite:ssd_anchors_calculator",
    "//mediapipe/calculators/tflite:tflite_converter_calculator",
    "//mediapipe/calculators/tflite:tflite_inference_calculator",
    "//mediapipe/calculators/tflite:tflite_tensors_to_detections_calculator",
    "//mediapipe/calculators/util:detection_label_id_to_text_calculator",
    "//mediapipe/calculators/util:non_max_suppression_calculator",

    # Pose tracking
    "//mediapipe/graphs/pose_tracking:pose_tracking_cpu_deps",

    # framework
    "//mediapipe/framework/formats:image_frame",

    # tasks
    "//mediapipe/tasks/cc/vision/face_landmarker:face_landmarker",
    
    "//mediapipe/tasks/cc/vision/core:running_mode",
    "//mediapipe/tasks/cc/components/processors:classifier_options",
    "//mediapipe/tasks/cc/vision/utils:image_utils",

    # libmptask
    "//mediapipe/tasks/libmptask/components/containers:keypoint",
    "//mediapipe/tasks/libmptask/components/containers:rect",
    "//mediapipe/tasks/libmptask/components/containers:category",
    "//mediapipe/tasks/libmptask/components/containers:classification_result",
    "//mediapipe/tasks/libmptask/components/containers:detection_result",
    "//mediapipe/tasks/libmptask/components/containers:embedding_result",
    "//mediapipe/tasks/libmptask/components/containers:landmark",
    "//mediapipe/tasks/libmptask/components/containers:matrix",

    "//mediapipe/tasks/libmptask/core:base_options",
    "//mediapipe/tasks/libmptask/core:base_options_converter",

    "//mediapipe/tasks/libmptask/vision/core:common",
    "//mediapipe/tasks/libmptask/vision/core:image_processing_options",
    "//mediapipe/tasks/libmptask/vision/utils:image_utils",
]

SOURCES = [
    "face_landmarker.cc",
]

HEADERS = [
    "face_landmarker.h", "face_landmarker_result.h",
]

# windows
cc_binary(
    target_compatible_with = [
        "@platforms//os:windows",
    ],
    name = "face_landmarker.dll",
    deps = [":face_landmarker_win"],
    data = BIN_DATA,
    linkshared = 1, ## Very important
)

# linux
cc_binary(
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    name = "face_landmarker_linux.so",
    deps = [":face_landmarker_linux"],
    data = BIN_DATA,
    linkopts = ["-Wl,-soname,face_landmarker_linux.so"],
    linkshared = 1, ## Very important
)

# android
cc_binary(
    target_compatible_with = [
        "@platforms//os:android",
    ],
    name = "face_landmarker_android.so",
    deps = [":face_landmarker_android"],
    data = BIN_DATA,
    linkopts = ["-Wl,-soname,face_landmarker_android.so"],
    linkshared = 1, ## Very important
)


cc_library(
    target_compatible_with = [
        "@platforms//os:windows",
    ],
    name = "face_landmarker_win",
    srcs = SOURCES,
    hdrs = HEADERS,
    visibility = ["//visibility:public"],
    deps = LIB_DEPS,
    defines = ["COMPILING_DLL=1"],
    alwayslink = 1,
)

cc_library(
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    name = "face_landmarker_linux",
    srcs = SOURCES,
    hdrs = HEADERS,
    visibility = ["//visibility:public"],
    deps = LIB_DEPS,
    alwayslink = 1,
)

cc_library(
    target_compatible_with = [
        "@platforms//os:android",
    ],
    name = "face_landmarker_android",
    srcs = SOURCES,
    hdrs = HEADERS,
    visibility = ["//visibility:public"],
    deps = LIB_DEPS,
    alwayslink = 1,
)