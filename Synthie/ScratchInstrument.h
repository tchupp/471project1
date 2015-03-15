#pragma once
#include "Instrument.h"
#include "WavFilePlayer.h"
#include <string>


class CScratchInstrument :
	public CInstrument
{
public:
	CScratchInstrument();
	virtual ~CScratchInstrument();

	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetNote(CNote* note, double secPerBeat) override;

	enum ScratchType { Baby, Scribble, Chirp, Transform };

	void SetSamples(short* sL, short* sR, int n) { mWavPlayer.SetSamples(sL, sR, n); }

	void SetDuration(double d) { mDuration = d; }

private:
	CWavFilePlayer mWavPlayer;
	double mDuration;
	double mTime;
	ScratchType mType;

	void SetScratchType(std::wstring type);
};