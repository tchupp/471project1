#pragma once
#include "Instrument.h"
#include "WavFilePlayer.h"


class CScratchInstrument :
	public CInstrument
{
public:
	CScratchInstrument();
	virtual ~CScratchInstrument();

	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetNote(CNote* note, double secPerBeat) override;

	void SetSamples(short* sL, short* sR, int n) { mWavPlayer.SetSamples(sL, sR, n); }

private:
	CWavFilePlayer mWavPlayer;
};
