#pragma once
#include <Vector3.h>
#include <assert.h>
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
    Matrix4x4 MakeViewportMatrix(
        float left, float top, float width, float height, float minDepth, float maxDepth);
    Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
    Vector3 Normalize(const Vector3& v);
    Vector3& operator*=(Vector3& v, float s);
    //Vector3& operator-=(Vector3& v, float s);
    const Vector3 operator*(const Vector3& v, float s);



  /*  Vector3& operator*=(Vector3& v, float s);*/
    //Vector3& operator-=(Vector3& m1, const Vector3& m2);
    //Vector3 operator-(const Vector3& m1, const Vector3& m2);
    Matrix4x4& operator*=(Matrix4x4& m1, const Matrix4x4& m2);
    Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);
