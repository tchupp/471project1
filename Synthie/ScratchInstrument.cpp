#include "stdafx.h"
#include "ScratchInstrument.h"


CScratchInstrument::CScratchInstrument()
{
}


CScratchInstrument::~CScratchInstrument()
{
}

void CScratchInstrument::Start()
{
	mWavPlayer.SetSampleRate(GetSampleRate());
	mWavPlayer.Start();
}

bool CScratchInstrument::Generate()
{
	auto valid = mWavPlayer.Generate();

	mFrame[0] = mWavPlayer.Frame(0);
	mFrame[1] = mWavPlayer.Frame(1);

	return valid;
}

//! not implemented
void CScratchInstrument::SetNote(CNote* note, double secPerBeat)
{
}
