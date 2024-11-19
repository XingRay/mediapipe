/* Copyright 2023 The MediaPipe Authors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "mediapipe/tasks/libmptask/components/containers/matrix_converter.h"

namespace libmptask {

void MatrixFromMatrixDataProto(const ::mediapipe::MatrixData& matrix_data, Matrix* matrix){
    const int rows = matrix_data.rows();
    const int cols = matrix_data.cols();

    if (matrix_data.packed_data_size() != rows * cols) {
        throw std::runtime_error("MatrixData packed_data size does not match rows * cols.");
    }

    matrix->resize(rows, cols);
    std::copy(matrix_data.packed_data().begin(), matrix_data.packed_data().end(), matrix->data());
}

}  // namespace mediapipe::tasks::c::components::containers
