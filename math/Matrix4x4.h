#pragma once
#include <Vector3.h>
/// <summary>
/// 4x4行列
/// </summary>
struct Matrix4x4 final {
	float m[4][4];

};
	Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
	Matrix4x4 MakeRotateXMatrix(float radian);
    Matrix4x4 MakeRotateYMatrix(float radian);
    Matrix4x4 MakeRotateZMatrix(float radian);
    Matrix4x4 Multiply(Matrix4x4 scalar, Matrix4x4 v);
    Matrix4x4 MakeAffineMetrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
    Matrix4x4 Inverse(const Matrix4x4& m);
    Matrix4x4& operator*=(const Matrix4x4& obj) {

	return *this;
    }
