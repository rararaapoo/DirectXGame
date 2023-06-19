#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include <iostream>
#include "PlayerBullet.h"
#include <list>
#include "Matrix4x4.h"
#include "Material.h"

class Player {

	public:

		~Player();

		void Initialize(Model* model, uint32_t textureHandle);

		void Update();

		void Draw(ViewProjection viewProjection_);
	    
		Matrix4x4 MakeRotateXMatrix(float radian) {
		    Matrix4x4 result;

		    result = {
		        1, 0, 0, 0, 0, cosf(radian), sinf(radian), 0, 0, -sinf(radian), cosf(radian),
		        0, 0, 0, 0, 1,
		    };

		    return result;
	    }

	    Matrix4x4 MakeRotateYMatrix(float radian) {
		    Matrix4x4 result;

		    result = {
		        cosf(radian), 0, -sinf(radian), 0, 0, 1, 0, 0,
		        sinf(radian), 0, cosf(radian),  0, 0, 0, 0, 1,
		    };

		    return result;
	    }

	    Matrix4x4 MakeRotateZMatrix(float radian) {
		    Matrix4x4 result;

		    result = {
		        cosf(radian),
		        sinf(radian),
		        0,
		        0,
		        -sinf(radian),
		        cosf(radian),
		        0,
		        0,
		        0,
		        0,
		        1,
		        0,
		        0,
		        0,
		        0,
		        1,
		    };

		    return result;
	    }

	    Matrix4x4 Multiply(Matrix4x4 scalar, Matrix4x4 v) {
		    Matrix4x4 result;

		    result.m[0][0] = scalar.m[0][0] * v.m[0][0] + scalar.m[0][1] * v.m[1][0] +
		                     scalar.m[0][2] * v.m[2][0] + scalar.m[0][3] * v.m[3][0];
		    result.m[0][1] = scalar.m[0][0] * v.m[0][1] + scalar.m[0][1] * v.m[1][1] +
		                     scalar.m[0][2] * v.m[2][1] + scalar.m[0][3] * v.m[3][1];
		    result.m[0][2] = scalar.m[0][0] * v.m[0][2] + scalar.m[0][1] * v.m[1][2] +
		                     scalar.m[0][2] * v.m[2][2] + scalar.m[0][3] * v.m[3][2];
		    result.m[0][3] = scalar.m[0][0] * v.m[0][3] + scalar.m[0][1] * v.m[1][3] +
		                     scalar.m[0][2] * v.m[2][3] + scalar.m[0][3] * v.m[3][3];

		    result.m[1][0] = scalar.m[1][0] * v.m[0][0] + scalar.m[1][1] * v.m[1][0] +
		                     scalar.m[1][2] * v.m[2][0] + scalar.m[1][3] * v.m[3][0];
		    result.m[1][1] = scalar.m[1][0] * v.m[0][1] + scalar.m[1][1] * v.m[1][1] +
		                     scalar.m[1][2] * v.m[2][1] + scalar.m[1][3] * v.m[3][1];
		    result.m[1][2] = scalar.m[1][0] * v.m[0][2] + scalar.m[1][1] * v.m[1][2] +
		                     scalar.m[1][2] * v.m[2][2] + scalar.m[1][3] * v.m[3][2];
		    result.m[1][3] = scalar.m[1][0] * v.m[0][3] + scalar.m[1][1] * v.m[1][3] +
		                     scalar.m[1][2] * v.m[2][3] + scalar.m[1][3] * v.m[3][3];

		    result.m[2][0] = scalar.m[2][0] * v.m[0][0] + scalar.m[2][1] * v.m[1][0] +
		                     scalar.m[2][2] * v.m[2][0] + scalar.m[2][3] * v.m[3][0];
		    result.m[2][1] = scalar.m[2][0] * v.m[0][1] + scalar.m[2][1] * v.m[1][1] +
		                     scalar.m[2][2] * v.m[2][1] + scalar.m[2][3] * v.m[3][1];
		    result.m[2][2] = scalar.m[2][0] * v.m[0][2] + scalar.m[2][1] * v.m[1][2] +
		                     scalar.m[2][2] * v.m[2][2] + scalar.m[2][3] * v.m[3][2];
		    result.m[2][3] = scalar.m[2][0] * v.m[0][3] + scalar.m[2][1] * v.m[1][3] +
		                     scalar.m[2][2] * v.m[2][3] + scalar.m[2][3] * v.m[3][3];

		    result.m[3][0] = scalar.m[3][0] * v.m[0][0] + scalar.m[3][1] * v.m[1][0] +
		                     scalar.m[3][2] * v.m[2][0] + scalar.m[3][3] * v.m[3][0];
		    result.m[3][1] = scalar.m[3][0] * v.m[0][1] + scalar.m[3][1] * v.m[1][1] +
		                     scalar.m[3][2] * v.m[2][1] + scalar.m[3][3] * v.m[3][1];
		    result.m[3][2] = scalar.m[3][0] * v.m[0][2] + scalar.m[3][1] * v.m[1][2] +
		                     scalar.m[3][2] * v.m[2][2] + scalar.m[3][3] * v.m[3][2];
		    result.m[3][3] = scalar.m[3][0] * v.m[0][3] + scalar.m[3][1] * v.m[1][3] +
		                     scalar.m[3][2] * v.m[2][3] + scalar.m[3][3] * v.m[3][3];
		    return result;
	    }

	    Matrix4x4 MakeAffineMetrix(
	        const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

		    Matrix4x4 result;

		    Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
		    Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
		    Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
		    Matrix4x4 rotateXYZMatrix =
		        Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

		    result = {
		        scale.x * rotateXYZMatrix.m[0][0],
		        scale.x * rotateXYZMatrix.m[0][1],
		        scale.x * rotateXYZMatrix.m[0][2],
		        0,
		        scale.y * rotateXYZMatrix.m[1][0],
		        scale.y * rotateXYZMatrix.m[1][1],
		        scale.y * rotateXYZMatrix.m[1][2],
		        0,
		        scale.z * rotateXYZMatrix.m[2][0],
		        scale.z * rotateXYZMatrix.m[2][1],
		        scale.z * rotateXYZMatrix.m[2][2],
		        0,
		        translate.x,
		        translate.y,
		        translate.z,
		        1,
		    };

		    return result;
	    }

		void Attack();


	private:
	    WorldTransform worldTransform_;

		Model* model_ = nullptr;

		uint32_t textureHandle_ = 0u;

		Input* input_ = nullptr;

	    std::list<PlayerBullet*> bullets_;

};
