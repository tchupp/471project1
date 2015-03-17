#pragma once
#include "Instrument.h"
#include "WavFilePlayer.h"

class CDrumsInstrument : public CInstrument
{
public:
	CDrumsInstrument();
	virtual ~CDrumsInstrument();

	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetNote(CNote* note, double secPerBeat) override;

	void SetSamples(short* sL, short* sR, int n) { mWavPlayer.SetSamples(sL, sR, n); }

	void SetDuration(double d) { mDuration = d; }

	void SetPitchFilter(bool pitch) { mPitchFilter = pitch; }
	void SetResonFilter(bool reson) { mResonFilter = reson; }

private:
	CWavFilePlayer mWavPlayer;
	double mDuration;
	double mTime;
	bool mPitchFilter = false;
	bool mResonFilter = false;
};