#pragma once
#pragma once
#include "../Engine/Component.h"

namespace CS230 {
	class Score : public Component {
	public:
		void Add(int value) {
			score += value;
		}
		int Value() { return score; }

	private:
		int score = 0;
	};
}