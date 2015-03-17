#pragma once
#include "Instrument.h"
#include "Envelope.h"
#include "ADSREnvelope.h"
#include "WavFilePlayer.h"
#include <vector>
#include "SineWave.h"

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

private:
	CWavFilePlayer mWavPlayer;
	double mDuration;
	double mTime;
};