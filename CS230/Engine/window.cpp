/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Window.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "Window.h"
#include "Engine.h"



void CS230::Window::Start(std::string title) {
    size = { default_width,default_height }; // important!
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(default_width, default_height, title.c_str());
    SetExitKey(KEY_NULL);
    rlDisableBackfaceCulling();
    BeginDrawing();
    Clear(default_background);
}

void CS230::Window::Update() {
    EndDrawing();

    int current_width = GetScreenWidth();
    int current_height = GetScreenHeight();
    if (current_width != size.x || current_height != size.y) {
        Engine::GetLogger().LogEvent("Window Resized");
        size = { current_width, current_height };
    }

    BeginDrawing();
}

bool CS230::Window::IsClosed() const {
    return WindowShouldClose();
}

Math::ivec2 CS230::Window::GetSize() const {
    return { size.x, size.y };
}

void CS230::Window::Clear(unsigned int rgba) {
    const Color rl_color = Color{
        static_cast<unsigned char>((rgba & 0xff000000) >> 24),
        static_cast<unsigned char>((rgba & 0x00ff0000) >> 16),
        static_cast<unsigned char>((rgba & 0x0000ff00) >> 8),
        static_cast<unsigned char>((rgba & 0x000000ff) >> 0)
    };

    ClearBackground(rl_color);
}

