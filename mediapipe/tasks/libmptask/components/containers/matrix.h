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

#ifndef MEDIAPIPE_TASKS_LIBMPTASK_COMPONENTS_CONTAINERS_MATRIX_H_
#define MEDIAPIPE_TASKS_LIBMPTASK_COMPONENTS_CONTAINERS_MATRIX_H_

#include <stdint.h>
#include <stdexcept>

#include "mediapipe/tasks/libmptask/utils/cpp_export.h"

namespace libmptask {

class MP_CPP_API Matrix {

private:
    uint32_t mRows;
    uint32_t mCols;
    float* mData;

public:
    Matrix();
    Matrix(uint32_t rows, uint32_t cols);

    Matrix(const Matrix& other);
    
    Matrix(Matrix&& other) noexcept;

    Matrix& operator=(const Matrix& other);
    
    Matrix& operator=(Matrix&& other) noexcept;

    ~Matrix();

    void resize(int32_t rows, int32_t cols);

    float& operator()(uint32_t row, uint32_t col);
    const float& operator()(uint32_t row, uint32_t col) const;

    uint32_t rows() const;
    uint32_t cols() const;

    float* data() const;
};


}  // namespace libmptask


#endif  // MEDIAPIPE_TASKS_LIBMPTASK_COMPONENTS_CONTAINERS_MATRIX_H_
