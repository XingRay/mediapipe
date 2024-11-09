# libmptask



## 1 clone

git clone git@github.com:XingRay/mediapipe.git



## 2 build env

install bazel 6.5.0

https://github.com/bazelbuild/bazel/releases/download/6.5.0/bazel-6.5.0-windows-x86_64.exe

download add add path  to system env PATH



msys2

https://www.msys2.org/

https://github.com/msys2/msys2-installer/releases/download/2024-07-27/msys2-x86_64-20240727.exe



opencv 4.6.0

https://opencv.org/releases/

https://sourceforge.net/projects/opencvlibrary/files/4.6.0/opencv-4.6.0-vc14_vc15.exe/download



## 3 edit build configuration

set opencv path on mediapipe/WORKSPACE

```python
new_local_repository(
    name = "windows_opencv",
    build_file = "@//third_party:opencv_windows.BUILD",
    path = "D:\\develop\\opencv\\4.6.0\\windows\\opencv\\build",
)
```

set opencv version on mediapipe/third__party/opencv_windows.BUILD

```python
OPENCV_VERSION = "460"  # 4.6.0
```



## 3 build

net proxy(optional)

```
$env:ALL_PROXY = "socks5://127.0.0.1:10808"
$env:HTTPS_PROXY = "http://127.0.0.1:10809"
$env:HTTP_PROXY = "http://127.0.0.1:10809"
```

build:

```
bazel --output_user_root=bazel_out build -c opt --cxxopt="/utf-8" --define MEDIAPIPE_DISABLE_GPU=1 mediapipe/tasks/libmptask/vision/face_landmarker:face_landmarker.dll
```

Compiling mediapipe/tasks/cc/vision/custom_ops/fused_batch_norm.cc;
When compiling the following file, it may take a long time (15 minutes or more). Please be patient.

output files:

```
./bazel_out
```





## Todo

| task\platform           | windows | linux | android |
| ----------------------- | ------- | ----- | ------- |
| face_landmarker         | done    |       |         |
| face_detection          |         |       |         |
| pose_landmark_detection |         |       |         |
| hand_landmark_detection |         |       |         |
| gesture_recognition     |         |       |         |

