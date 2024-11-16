#include "mediapipe/tasks/libmptask/components/containers/classification_result_converter.h"
#include "mediapipe/tasks/libmptask/components/containers/category_converter.h"

namespace libmptask{

Classifications ConvertToClassifications(const ::mediapipe::tasks::components::containers::proto::Classifications& proto) {
  Classifications classifications;
  classifications.categories.reserve(
      proto.classification_list().classification_size());
  for (const auto& classification :
       proto.classification_list().classification()) {
    classifications.categories.push_back(ConvertToCategory(classification));
  }
  classifications.head_index = proto.head_index();
  if (proto.has_head_name()) {
    classifications.head_name = proto.head_name();
  }
  return classifications;
}

Classifications ConvertToClassifications(
    const mediapipe::ClassificationList& proto, int head_index,
    std::optional<std::string> head_name) {
  Classifications classifications;
  classifications.categories.reserve(proto.classification_size());
  for (const auto& classification : proto.classification()) {
    classifications.categories.push_back(ConvertToCategory(classification));
  }
  classifications.head_index = head_index;
  classifications.head_name = head_name;
  return classifications;
}

ClassificationResult ConvertToClassificationResult(
    const ::mediapipe::tasks::components::containers::proto::ClassificationResult& proto) {
  ClassificationResult classification_result;
  classification_result.classifications.reserve(proto.classifications_size());
  for (const auto& classifications : proto.classifications()) {
    classification_result.classifications.push_back(
        ConvertToClassifications(classifications));
  }
  if (proto.has_timestamp_ms()) {
    classification_result.timestamp_ms = proto.timestamp_ms();
  }
  return classification_result;
}

}
