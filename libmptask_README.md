git clone git@github.com:XingRay/mediapipe.git


set opencv path on mediapipe/WORKSPACE

set opencv version on mediapipe/third__party/opencv_windows.BUILD


build:



bazel --output_user_root=bazel_out build -c opt --cxxopt="/utf-8" --define MEDIAPIPE_DISABLE_GPU=1 mediapipe/tasks/libmptask/vision/face_landmarker:face_landmarker.dll

Compiling mediapipe/tasks/cc/vision/custom_ops/fused_batch_norm.cc;
When compiling the following file, it may take a long time (15 minutes or more). Please be patient

