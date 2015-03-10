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

	CWavFilePlayer* GetPlayer() { return &mWavPlayer; }

private:
	CWavFilePlayer mWavPlayer;
};
