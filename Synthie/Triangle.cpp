#include "stdafx.h"
#include "Triangle.h"
#include <cmath>

using namespace std;

CTriangle::CTriangle()
{
	mPhase = 0;
	mAmp = 0.1;
	mFreq = 440;
}

CTriangle::~CTriangle()
{
}

void CTriangle::Start()
{
	mPhase = 0;
	SetWavetables();
}

bool CTriangle::Generate()
{
	mFrame[0] = mWavetable[mPhase];
	mFrame[1] = mFrame[0];

	mPhase = (mPhase + 1) % mWavetable.size();

	return true;
}

void CTriangle::SetWavetables()
{
	mWavetable.resize(GetSampleRate());
	auto time = 0.;
	auto count = 0;
	for (auto i = 0; i < GetSampleRate(); i++ , time += 1. / GetSampleRate())
	{
		auto triangleSample = 0.;
		int nyquist = GetSampleRate() / 2;
		auto harm = 1.;

		while (mFreq * harm < nyquist)
		{
			triangleSample += pow(-1, count) * mAmp / pow(harm, 2)
				* sin(time * 2 * PI * mFreq * harm);
			harm += 2;
			count++;
		}
		mWavetable[i] = triangleSample;
	}
}
