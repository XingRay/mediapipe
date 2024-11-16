#include "mediapipe/tasks/libmptask/components/containers/rect_converter.h"

namespace libmptask{

void cppConvertRect(Rect& rect, ::mediapipe::tasks::components::containers::Rect* cppRect){
    cppRect->left=rect.left;
    cppRect->top=rect.top;
    cppRect->right=rect.right;
    cppRect->bottom=rect.bottom;
}

void cppConvertRectF(RectF& rectf, ::mediapipe::tasks::components::containers::RectF* cppRectf){
    cppRectf->left=rectf.left;
    cppRectf->top=rectf.top;
    cppRectf->right=rectf.right;
    cppRectf->bottom=rectf.bottom;
}

}