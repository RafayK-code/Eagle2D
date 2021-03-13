#pragma once
#include "ECS.h"

namespace Eagle
{
	//Pre defined component
	//Holds an integer containing the max amount of indexes,
	//a vector containing the frames per index, speed of the animation and
	//the current index
	struct EAGLE_API Animation : public ECS::Component
	{
		Animation(int maxIndicies, std::vector<int> frames, int speed)
			: maxIndicies(maxIndicies), frames(frames), speed(speed), currentIndex(0)
		{
		}

		Animation(int maxIndicies, std::vector<int> frames, int speed, int startingIndex)
			: maxIndicies(maxIndicies), frames(frames), speed(speed), currentIndex(startingIndex)
		{
		}

		int maxIndicies;
		std::vector<int> frames;
		int speed;

		int currentIndex;
	};
}