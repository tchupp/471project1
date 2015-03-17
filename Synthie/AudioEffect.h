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

	virtual void SetNote(CNote *note, double secPerBeat) override;

protected:
	CAudioEffect();

	double	mDelay;
	double	mWet;
	double	mDry;
	int mWrloc;
	int mRdloc;
	double mTime = 5.0;
	std::vector<short> mQueue;
};

