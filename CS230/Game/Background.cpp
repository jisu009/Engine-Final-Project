/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Background.cpp
Project:    CS230 Engine
Author:     Jeonghun Byeon
Created:    March 29, 2025
*/

#include "Background.h"
#include "../Engine/Engine.h"

void Background::Add(const std::filesystem::path& texture_path, double speed)
{
    auto texture = Engine::GetTextureManager().Load(texture_path);
    backgrounds.emplace_back(ParallaxLayer{ texture, speed });
}

void Background::Unload()
{
    backgrounds.clear();
}


void Background::Draw(const CS230::Camera& camera)
{
    for (const auto& layer : backgrounds) {
        if (layer.texture) {
            Math::vec2 camera_pos = camera.GetPosition();
            Math::vec2 offset = -camera_pos * layer.speed;
            Math::TransformationMatrix translation_matrix = Math::TranslationMatrix(offset);
            layer.texture->Draw(translation_matrix);
        }
    }
}


Math::ivec2 Background::GetSize()
{
    return Math::ivec2(backgrounds[backgrounds.size() - 1].texture->GetSize());
}