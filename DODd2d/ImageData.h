#pragma once

struct ImageData
{
	ImageData(std::wstring imagePath, double frameTime)
		: handle(-1), animationIndex(0), imagePath(imagePath), animationMaxCount(-1), frameTime(frameTime), elapsedTime(0)
	{}

	int handle;
	int animationIndex;
	std::wstring imagePath;
	int animationMaxCount;
	double frameTime;
	double elapsedTime;
};