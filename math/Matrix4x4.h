#pragma once
#include <Vector3.h>
/// <summary>
/// 4x4行列
/// </summary>
struct Matrix4x4 final {
	float m[4][4];

};
	Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
