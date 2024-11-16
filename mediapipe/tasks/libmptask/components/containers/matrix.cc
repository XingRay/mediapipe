
#include "mediapipe/tasks/libmptask/components/containers/matrix.h"

#include <algorithm>

namespace libmptask {

Matrix::Matrix() : mRows(0), mCols(0), mData(nullptr) {}

Matrix::Matrix(uint32_t rows, uint32_t cols) : mRows(rows), mCols(cols) {
    mData = new float[mRows * mCols]();
}

Matrix::Matrix(const Matrix& other) : mRows(other.mRows), mCols(other.mCols) {
    mData = new float[mRows * mCols];
    std::copy(other.mData, other.mData + mRows * mCols, mData);
}

Matrix::Matrix(Matrix&& other) noexcept : mRows(other.mRows), mCols(other.mCols), mData(other.mData) {
    other.mData = nullptr;
    other.mRows = other.mCols = 0;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        delete[] mData;
        mRows = other.mRows;
        mCols = other.mCols;
        mData = new float[mRows * mCols];
        std::copy(other.mData, other.mData + mRows * mCols, mData);
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        delete[] mData;
        mRows = other.mRows;
        mCols = other.mCols;
        mData = other.mData;
        other.mData = nullptr;
        other.mRows = other.mCols = 0;
    }
    return *this;
}

Matrix::~Matrix() {
    delete[] mData;
}

void Matrix::resize(int32_t rows, int32_t cols) {
    delete[] mData;
    mRows = rows;
    mCols = cols;
    mData = new float[mRows * mCols]();
}

float& Matrix::operator()(uint32_t row, uint32_t col) {
    if (row >= mRows || col >= mCols) {
        throw std::out_of_range("Matrix index out of range");
    }
    return mData[col * mRows + row];
}

const float& Matrix::operator()(uint32_t row, uint32_t col) const {
    if (row >= mRows || col >= mCols) {
        throw std::out_of_range("Matrix index out of range");
    }
    return mData[col * mRows + row];
}

uint32_t Matrix::rows() const {
    return mRows;
}

uint32_t Matrix::cols() const {
    return mCols;
}

// 提供 mData() 方法
float* Matrix::data() const {
    return mData;
}

}  // namespace libmptask