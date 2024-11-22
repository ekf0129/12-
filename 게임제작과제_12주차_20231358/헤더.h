#pragma once
// MatrixUtils.h
#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <math.h>

// 2D 좌표 구조체
typedef struct {
    double x;
    double y;
} Point;

// 3x3 행렬 구조체
typedef struct {
    double m[3][3];
} Matrix;

// 함수 선언
Matrix createRotationMatrix(double angle);      // 회전 행렬 생성
Matrix createScalingMatrix(double scaleX, double scaleY); // 크기 조정 행렬 생성
Matrix createTranslationMatrix(double dx, double dy); // 이동 행렬 생성
Point applyMatrixToPoint(const Matrix* matrix, const Point* point); // 좌표에 행렬 적용

#endif
