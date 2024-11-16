
#include "mediapipe/tasks/libmptask/vision/face_landmarker/face_landmarker_options_converter.h"


namespace libmptask{

void CppConvertToFaceLandmarkerOptions(const FaceLandmarkerOptions& in, mediapipe::tasks::vision::face_landmarker::FaceLandmarkerOptions* out) {
  out->num_faces = in.num_faces;
  out->min_face_detection_confidence = in.min_face_detection_confidence;
  out->min_face_presence_confidence = in.min_face_presence_confidence;
  out->min_tracking_confidence = in.min_tracking_confidence;
  out->output_face_blendshapes = in.output_face_blendshapes;
  out->output_facial_transformation_matrixes = in.output_facial_transformation_matrixes;
}

}
