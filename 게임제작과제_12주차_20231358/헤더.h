#pragma once
// MatrixUtils.h
#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <math.h>

// 2D ��ǥ ����ü
typedef struct {
    double x;
    double y;
} Point;

// 3x3 ��� ����ü
typedef struct {
    double m[3][3];
} Matrix;

// �Լ� ����
Matrix createRotationMatrix(double angle);      // ȸ�� ��� ����
Matrix createScalingMatrix(double scaleX, double scaleY); // ũ�� ���� ��� ����
Matrix createTranslationMatrix(double dx, double dy); // �̵� ��� ����
Point applyMatrixToPoint(const Matrix* matrix, const Point* point); // ��ǥ�� ��� ����

#endif
