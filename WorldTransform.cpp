#include "WorldTransform.h"
//#include "Player.h"


void WorldTransform::UpdateMatrix() {
	matWorld_ = MakeAffineMetrix(scale_, rotation_, translation_);

	if (parent_)
	{
		matWorld_ *= parent_->matWorld_;
	}

	TransferMatrix();
}
