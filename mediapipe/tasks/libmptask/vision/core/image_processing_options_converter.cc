
#include "mediapipe/tasks/libmptask/vision/core/image_processing_options_converter.h"
#include "mediapipe/tasks/libmptask/components/containers/rect_converter.h"

namespace libmptask{

void cppConvertImageProcessingOptions(ImageProcessingOptions& options, ::mediapipe::tasks::vision::core::ImageProcessingOptions* cppOptions){
    if(options.region_of_interest.has_value()){
        cppConvertRectF(options.region_of_interest.value(), &(cppOptions->region_of_interest.value()));
    }
    
    cppOptions ->rotation_degrees = options.rotation_degrees;

}   

}