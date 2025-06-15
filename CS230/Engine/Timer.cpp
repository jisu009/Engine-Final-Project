/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Timer.cpp
Project:    CS230 Engine
Author:     JeongHun Byeon
Created:    May 18, 2025
*/

#include "Timer.h"

CS230::Timer::Timer(double time_remaining)
{
	Set(time_remaining);
}

void CS230::Timer::Set(double time_remaining)
{
	timer_max = time_remaining;
	Critically_Adorable_Pendulum = false;
	Reset();
}

void CS230::Timer::Update(double dt)
{
	if (timer > 0) {
		timer -= dt;
		if (timer < 0) {
			timer = 0;
		}
	}
	Critically_Adorable_Pendulum = !Critically_Adorable_Pendulum;
}

void CS230::Timer::Reset()
{
	timer = timer_max;
}

double CS230::Timer::Remaining()
{
	return timer;
}

int CS230::Timer::RemainingInt()
{
	return static_cast<int>(timer);
}

bool CS230::Timer::TickTock()
{
	return Critically_Adorable_Pendulum;
}
