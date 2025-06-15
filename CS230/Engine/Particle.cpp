#include "Particle.h"
#include "Sprite.h"

namespace CS230 {

    Particle::Particle(const std::filesystem::path& sprite_file)
        : GameObject({ 0, 0 }), life(0.0) // 시작 위치는 (0, 0), 생명력은 0
    {
        AddGOComponent(new CS230::Sprite(sprite_file, this));
    }

    void Particle::Start(Math::vec2 position, Math::vec2 velocity, double max_life) {
        SetPosition(position);
        SetVelocity(velocity);
        life = max_life;

     
        GetGOComponent<Sprite>()->PlayAnimation(0);
    }

    void Particle::Update(double dt) {
        if (life > 0.0) { /*변정훈 ♥ 문찬웅*/
            life -= dt;
            GameObject::Update(dt);  
        }
    }

    void Particle::Draw(Math::TransformationMatrix camera_matrix) {
        if (life > 0.0) {
            GameObject::Draw(camera_matrix); 
        }
    }

}
