
#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Vec2.h"
#include "../Game/GameObjectTypes.h"
#include "../Engine/GameObjectManager.h"

namespace CS230 {
    class Particle : public GameObject {
    public:
        Particle(const std::filesystem::path& sprite_file);
        void Start(Math::vec2 new_position, Math::vec2 new_velocity, double max_life);
        void Update(double dt) override;
        void Draw(Math::TransformationMatrix camera_matrix) override;
        bool Alive() { return  life > 0; }
        GameObjectTypes Type() { return GameObjectTypes::Particle; }

    private:
        double life;
    };

    template<typename T>
    class ParticleManager : public Component {
    public:
        ParticleManager();
        ~ParticleManager();
        void Emit(int count, Math::vec2 emitter_position, Math::vec2 emitter_velocity, Math::vec2 direction, double spread);
    private:
        std::vector<T*> particles;
        int index;
    };
}

template<typename T>
CS230::ParticleManager<T>::ParticleManager() : index(0) {
	for (int i = 0; i < T::MaxCount; ++i) {
		T* ptc = new T();
		Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(ptc);
		particles.push_back(ptc);
	}
}

template<typename T>
CS230::ParticleManager<T>::~ParticleManager() {
	particles.clear();
}

template<typename T>
void CS230::ParticleManager<T>::Emit(int count, Math::vec2 emitter_position, Math::vec2 emitter_velocity, Math::vec2 direction, double spread) {
	for (int i = 0; i < count; ++i) {
		if (particles[index]->Alive()) {
			Engine::GetLogger().LogError("Particle overwritten");
		}

		double angle_variation = 0.0;
		if (spread != 0.0) {
			angle_variation = ((rand() % static_cast<int>(spread * 1024)) / 1024.0f) - spread / 2;
		}

        Math::vec2 random_magnitude = direction * (((rand() % 1024) / 2048.0f) + 0.5f);
        Math::vec2 particle_velocity = Math::RotationMatrix(angle_variation) * random_magnitude + emitter_velocity;
        particles[index]->Start(emitter_position, particle_velocity, T::MaxLife);

		index++;
		if (index >= static_cast<int>(particles.size())) {
			index = 0;
		}
	}
}