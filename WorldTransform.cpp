#include "WorldTransform.h"
#include "Player.h"

void WorldTransform::UpdateMatrix() {
	matWorld_ = MakeAffineMetrix(scale_, rotation_, translation_);

	TransferMatrix();
}
