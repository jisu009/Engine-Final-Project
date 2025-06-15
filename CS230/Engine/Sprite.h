/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Sprite.h
Project:    CS230 Engine
Author:     Jeonghun Byeon
Created:    March 8, 2023
*/

#pragma once
#include <string>
#include <raylib.h>
#include "Vec2.h"
#include "Texture.h"
#include "Matrix.h"
#include "Animation.h"
#include "Component.h"
#include "GameObject.h"

namespace CS230 {
    class GameObject;

    class Sprite : public Component {
        friend class GameObject;
    public:
        Sprite();
        ~Sprite();
        Sprite(const std::filesystem::path& sprite_file, GameObject* given_object);

        void Update(double dt) override;
        void Load(const std::filesystem::path& sprite_file, GameObject* given_object);
        void Draw(Math::TransformationMatrix display_matrix);

        Math::ivec2 GetFrameSize() const; 
        Math::ivec2 GetHotSpot(int index);

        void PlayAnimation(int animation);
        bool AnimationEnded();

        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;

        Sprite(Sprite&& temporary) noexcept;
        Sprite& operator=(Sprite&& temporary) noexcept;

        int CurrentAnimation() const;


    private:
        Math::ivec2 GetFrameTexel(int index) const;

        Texture* texture;
        std::vector<Math::ivec2> hotspots;

        int current_animation;
        Math::ivec2 frame_size;
        std::vector<Math::ivec2> frame_texels;
        std::vector<Animation*> animations;

        GameObject* object = nullptr;

    };
}
