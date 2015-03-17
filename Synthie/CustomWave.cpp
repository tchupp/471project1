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
	mTime = 0;
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

	double sineRadians = 0;										// Sine wave
	double vibratoRadians = 0;


	for (auto i = 0; i < tableSize; i++, mTime += 1. / GetSampleRate())
	{
		auto sineSample = mAmp * sin(sineRadians);

		// Harmonics
		if (mHarmonics.size() > 0)
		{
			ImplementHarmonics(&sineSample, mTime);
		}

		// Vibrato
		if (mUseVibrato) // change to vibrat
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

void CCustomWave::GenerateCrossfade(double time, double crossfadeDuration)
{
	auto elapsed = time - mCrossfadeBeginTime;

	double nextSample[2];
	double currentSample[2];
	double interpolatedSample;

	if (mPhase < mPartnerWave->GetWavetableSize() && mPhase < GetWavetableSize())
	{
		nextSample[0] = nextSample[1] = mPartnerWave->mWavetable[mPhase];
		currentSample[0] = currentSample[1] = mWavetable[mPhase];

		interpolatedSample = currentSample[0] * ((crossfadeDuration - elapsed) / crossfadeDuration) +
			nextSample[0] * (elapsed / crossfadeDuration);

		mFrame[0] = mFrame[1] = interpolatedSample;
	}
	else
	{
		mFrame[0] = mWavetable[mPhase];
		mFrame[1] = mFrame[0];
	}

	mPhase = (mPhase + 1) % mWavetable.size();
}

void CCustomWave::ImplementVibrato(double* sineRadians, double* vibratoRadians)
{
	// Creating sine wave
	double sample = short(mAmp * sin(*sineRadians));

	// Calculating the rate
	double diff = sin(*vibratoRadians) * mVibratoEffect.vibrato;

	// Increment phases
	*sineRadians += (2 * PI * (mFreq + diff)) / mSampleRate;
	*vibratoRadians += (2 * PI * mVibratoEffect.vibratoRate) / mSampleRate;
}
