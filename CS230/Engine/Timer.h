/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Timer.h
Project:    CS230 Engine
Author:      JeongHun Byeon
Created:    May 18, 2025
*/

#pragma once
#include "Component.h"

namespace CS230 {
    class Timer : public Component {
    public:
        Timer(double time_remaining);
        void Set(double time_remaining);
        void Update(double dt) override;
        void Reset();
        double Remaining();
        int RemainingInt();
        bool TickTock();
    private:
        double timer;
        double timer_max;
        bool Critically_Adorable_Pendulum;
    };
}
