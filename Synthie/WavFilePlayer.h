/**
 * \file WavFilePlayer.h
 *
 * \author Theo Chupp
 *
 * \brief wave class that can have a custom wave table set.
 */

#pragma once
#include "BaseWave.h"

class CWavFilePlayer : public BaseWave
{
public:
	CWavFilePlayer();
	virtual ~CWavFilePlayer();

	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetWavetables() override;

	void SetSamples(short* sL, short* sR, int n);
	void SetSpeed(double speed) { mSpeed = speed; }

private:
	short* mSamplesLeft;
	short* mSamplesRight;

	int mNumSamples;
	int mPosition;

	double mSampleNumber;
	double mSpeed;
};
