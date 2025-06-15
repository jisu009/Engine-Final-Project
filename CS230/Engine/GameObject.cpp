
#include"GameObject.h"
#include "Collision.h"
#include "ShowCollision.h"


CS230::GameObject::GameObject(Math::vec2 position) :
    GameObject(position, 0, { 1, 1 })
{

}

CS230::GameObject::GameObject(Math::vec2 position, double rotation, Math::vec2 scale) :
    velocity({ 0,0 }),
    position(position),
    scale(scale),
    rotation(rotation),
    current_state(&state_none),
    destroy(false) {

}

bool CS230::GameObject::IsCollidingWith(GameObject* other_object) {
    Collision* collider = GetGOComponent<Collision>();
    return collider != nullptr && collider->IsCollidingWith(other_object);
}

bool CS230::GameObject::IsCollidingWith(Math::vec2 point) {
    Collision* collider = GetGOComponent<Collision>();
    return collider != nullptr && collider->IsCollidingWith(point);
}

bool CS230::GameObject::CanCollideWith([[maybe_unused]] GameObjectTypes other_object_type) {
    return false;
}

void CS230::GameObject::Update(double dt) {
    current_state->Update(this, dt);
    if (velocity.x != 0 || velocity.y != 0) {
        UpdatePosition(velocity * dt);
    }
    UpdateGOComponents(dt);
    current_state->CheckExit(this);

    //sprite.Update(dt);
}

void CS230::GameObject::change_state(State* new_state) {
    current_state = new_state;
    current_state->Enter(this);
}

void CS230::GameObject::Draw(Math::TransformationMatrix camera_matrix) {
    Sprite* sprite = GetGOComponent<Sprite>();
    if (sprite != nullptr) {
        sprite->Draw(camera_matrix * GetMatrix());
    }
#ifdef _DEBUG
    CS230::ShowCollision* show = Engine::GetGameStateManager().GetGSComponent<ShowCollision>();
    if (show != nullptr && show->Enabled()) {
        Collision* collision = GetGOComponent<Collision>();
        if (collision != nullptr) {
            collision->Draw(camera_matrix);
        }
    }
#endif

    //RectCollision* collision = GetGOComponent<RectCollision>();
    //if (collision != nullptr) {
    //    collision->Draw(camera_matrix);
    //}
}

const Math::TransformationMatrix& CS230::GameObject::GetMatrix() {
    if (matrix_outdated == true) {
        object_matrix = Math::TranslationMatrix(position) * Math::RotationMatrix(rotation) * Math::ScaleMatrix(scale);
        matrix_outdated = false;
    }
    return object_matrix;
}

const Math::vec2& CS230::GameObject::GetPosition() const {
    return { position };
}

void CS230::GameObject::SetPosition(Math::vec2 new_position) {
    position = new_position;
    matrix_outdated = true;
}

void CS230::GameObject::UpdatePosition(Math::vec2 delta) {
    position += delta;
    matrix_outdated = true;
}

const Math::vec2& CS230::GameObject::GetVelocity() const {
    return { velocity };
}

void CS230::GameObject::SetVelocity(Math::vec2 new_position) {
    velocity = new_position;
    matrix_outdated = true;
}

void CS230::GameObject::UpdateVelocity(Math::vec2 delta) {
    velocity += delta;
    matrix_outdated = true;
}

const Math::vec2& CS230::GameObject::GetScale() const {
    return { scale };
}

void CS230::GameObject::SetScale(Math::vec2 new_scale) {
    scale = new_scale;
    matrix_outdated = true;
}

void CS230::GameObject::UpdateScale(Math::vec2 delta) {
    scale += delta;
    matrix_outdated = true;
}

double CS230::GameObject::GetRotation() const {
    return rotation;
}

void CS230::GameObject::SetRotation(double new_rotation) {
    rotation = new_rotation;
    matrix_outdated = true;
}

void CS230::GameObject::UpdateRotation(double delta) {
    rotation += delta;
    matrix_outdated = true;
}

void CS230::GameObject::Destroy() {
    destroy = true;
}

bool CS230::GameObject::Destroyed() const {
    return destroy;
}

