//
// Created by leixing on 2024/11/13.
//

#ifndef MEDIAPIPE_TASKS_LIBMPTASK_VISION_FACE_LANDMARKER_FACE_LANDMARKER_OPTIONS_CONVERTER_H_
#define MEDIAPIPE_TASKS_LIBMPTASK_VISION_FACE_LANDMARKER_FACE_LANDMARKER_OPTIONS_CONVERTER_H_

#include "mediapipe/tasks/libmptask/vision/face_landmarker/face_landmarker_options.h"
#include "mediapipe/tasks/cc/vision/face_landmarker/face_landmarker.h"

namespace libmptask{

void CppConvertToFaceLandmarkerOptions(const FaceLandmarkerOptions& in, mediapipe::tasks::vision::face_landmarker::FaceLandmarkerOptions* out);

}

#endif //MEDIAPIPE_TASKS_LIBMPTASK_VISION_FACE_LANDMARKER_FACE_LANDMARKER_OPTIONS_CONVERTER_H_