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
	double time = 0;
	int count = 0;
	for (int i = 0; i < (GetSampleRate()); i++, time += 1. / GetSampleRate())
	{
		short triangleSample = 0;
		int nyquist = GetSampleRate() / 2;
		int harm = 1;

		while (mFreq * harm < nyquist)
		{
			triangleSample += RangeBound(pow(-1, count) * mAmp / pow(harm, 2) 
				* sin(time * 2 * PI * mFreq * harm));
			harm += 1;
			count++;
		}
		mWavetable[i] = RangeBound(triangleSample);
	}
}

short CTriangle::RangeBound(double sample)
{
	if (sample > 32767)
	{
		return 32767;
	}
	else if (sample < -32768)
	{
		return -32768;
	}

	return short(sample);
}