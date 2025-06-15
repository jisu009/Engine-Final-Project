/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Seeker.h
Project:    CS230 Engine
Author:     Jeonghun Byeon, Jisu Son
Created:    June 15, 2025
*/
#include "../Engine/GameObject.h"
#include "GameObjectTypes.h"
#include "../Engine/Input.h"
#include "Mode3.h"

class Seeker : public CS230::GameObject {
public:
	Seeker(Math::vec2 start_position);
	GameObjectTypes Type() override { return GameObjectTypes::Seeker; }
	std::string TypeName() override { return "Seeker"; }
	void Update(double dt) override;
	const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }
	void Draw(Math::TransformationMatrix camera_matrix) override;
private:
	static constexpr double x_acceleration = 200;
	static constexpr double x_drag = 450;
	static constexpr double max_velocity = 300;
	static constexpr double jump_velocity = 650;

	static constexpr double hurt_time = 2.0;
	static constexpr double hurt_velocity = 350;
	static constexpr double hurt_acceleration = 300;
    double fall_start_y_position = 0;
	static constexpr double bounce_velocity = 700;
	static constexpr double pop_velocity = 400;

    void update_x_velocity(double dt);

    enum class Animations {
        Idle,
        Running,
        Jumping,
        Falling
    };

    class State_Jumping : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };

    class State_Idle : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    class State_Falling : public State {
    public:
        virtual void Enter(GameObject* objectt) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };

    class State_Running : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };

    State_Jumping state_jumping;
    State_Idle state_idle;
    State_Falling state_falling;
    State_Running state_running;
};