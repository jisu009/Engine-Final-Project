#pragma once
#include "Laser.h"

Laser::Laser(Math::vec2 pos, double rot, Math::vec2 scale, Math::vec2 vel) :
	GameObject(pos, rot, scale)
{
	SetVelocity(vel);
	AddGOComponent(new CS230::Sprite("Assets/Laser.spt", this));
}

void Laser::Update(double dt) {
	GameObject::Update(dt);

	if (GetGOComponent<CS230::Sprite>() == nullptr) {
		return;
	}

	if (GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0 < 0 || GetPosition().x - GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0 > Engine::GetWindow().GetSize().x ||
		GetPosition().y + GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0 < 0 || GetPosition().y - GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0 > Engine::GetWindow().GetSize().y) {
		Destroy();
	}
}

bool Laser::CanCollideWith(GameObjectTypes other_object_type) {
	return other_object_type == GameObjectTypes::Meteor;
}

void Laser::ResolveCollision(GameObject* other_object) {
	Destroy();
	other_object->ResolveCollision(this);
}