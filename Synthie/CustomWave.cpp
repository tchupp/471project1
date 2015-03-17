#include "stdafx.h"
#include "CustomWave.h"
#include <math.h>

using namespace std;

CCustomWave::CCustomWave()
{
	mPhase = 0;
	mAmp = 0.1;
	mFreq = 440;
}

CCustomWave::~CCustomWave()
{
}

void CCustomWave::Start()
{
	mPhase = 0;
	SetWavetables();
}

bool CCustomWave::Generate()
{
	mFrame[0] = mWavetable[mPhase];
	mFrame[1] = mFrame[0];

	mPhase = (mPhase + 1) % mWavetable.size();

	return true;
}

void CCustomWave::SetWavetables()
{
	auto tableSize = GetSampleRate();

	mWavetable.resize(tableSize);
	auto time = 0.;

	double sineRadians = 0;										// Sine wave
	double vibratoRadians = 0;


	for (auto i = 0; i < tableSize; i++, time += 1. / GetSampleRate())
	{
		auto sineSample = mAmp * sin(sineRadians);

		// Harmonics
		if (mHarmonics.size() > 0)
		{
			ImplementHarmonics(&sineSample, time);
		}

		// Vibrato
		if (true) // change to vibrat
		{
			ImplementVibrato(&sineRadians, &vibratoRadians);
		}

		mWavetable[i] = sineSample;
	}
}

void CCustomWave::ImplementHarmonics(double* sample, double time)
{
	auto nyquistFrequency = GetSampleRate() / 2;

	// Adding harmonics (index is harmonic, value is amplitude), while below nyquist
	for (auto x = 0; x < mHarmonics.size() && (mFreq * (x + 1)) < nyquistFrequency; x++)
	{
		// Adjusting to fit harmonic number
		auto harmonic = x + 1;

		*sample += mHarmonics[x] * (mAmp / harmonic) * (sin(time * 2 * PI * harmonic * mFreq));
	}
}

void CCustomWave::ImplementVibrato(double* sineRadians, double* vibratoRadians)
{
	// Creating sine wave
	double sample = short(mAmp * sin(*sineRadians));

	// Calculating the rate
	double diff = sin(*vibratoRadians) * mVibrato;

	// Increment phases
	*sineRadians += (2 * PI * (mFreq + diff)) / mSampleRate;
	*vibratoRadians += (2 * PI * mVibratoRate) / mSampleRate;
}