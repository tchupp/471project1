//! Abstract base class that audio effects
//! will be derived from

#pragma once
#include "Instrument.h"
#include <vector>


class CAudioEffect : 
	public CInstrument
{
public:
	virtual ~CAudioEffect();

	virtual void Process(double *frameIn, double *frameOut) = 0;

	void SetDelay(double delay) { mDelay = delay; }

	void SetWet(double wet) { mWet = wet; }

	void SetDry(double dry) { mDry = dry; }

protected:
	CAudioEffect();

private:
	//! The average delay 
	double	mDelay;
	double	mWet;
	double	mDry;
	std::vector<short> mQueue;
};

