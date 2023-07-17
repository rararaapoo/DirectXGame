#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Matrix4x4.h"
#include <imgui.h>

class RailCamera 
{

	public:
	void Initialize(Vector3 move, Vector3 rot);

	void Update();

	const ViewProjection& GetViewProjection() { return viewProjection_; }

	private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
};
