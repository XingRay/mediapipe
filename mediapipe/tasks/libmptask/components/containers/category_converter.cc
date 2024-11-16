#include "mediapipe/tasks/libmptask/components/containers/category_converter.h"

namespace libmptask{

Category ConvertToCategory(const ::mediapipe::Classification& proto) {
  Category category;
  category.index = proto.index();
  category.score = proto.score();
  if (proto.has_label()) {
    category.category_name = proto.label();
  }
  if (proto.has_display_name()) {
    category.display_name = proto.display_name();
  }
  return category;
}


}