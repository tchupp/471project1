/**
 * \file ScratchInstrumentFactory.cpp
 *
 * \author Theo Chupp
 */

#include "stdafx.h"
#include "ScratchInstrument.h"
#include "ScratchInstrumentFactory.h"
#include "audio/DirSoundSource.h"


CScratchInstrumentFactory::CScratchInstrumentFactory()
{
}


CScratchInstrumentFactory::~CScratchInstrumentFactory()
{
}


CInstrument* CScratchInstrumentFactory::CreateInstrument()
{
	auto instrument = new CScratchInstrument();
	instrument->SetSamples(&mWaveL[0], &mWaveR[0], int(mWaveL.size()));

	return instrument;
}


bool CScratchInstrumentFactory::LoadFile(const char* filename)
{
	mWaveL.clear();
	mWaveR.clear();

	CDirSoundSource mFile;
	if (!mFile.Open(filename))
	{
		CString message = L"Unable to open audio file: ";
		message += filename;
		AfxMessageBox(message);
		return false;
	}

	for (auto i = 0; i < mFile.NumSampleFrames(); ++i)
	{
		short frame[2];
		mFile.ReadFrame(frame);
		mWaveL.push_back(frame[0]);
		mWaveR.push_back(frame[1]);
	}

	mFile.Close();
	return true;
}

//! not implemented
void CScratchInstrumentFactory::SetNote(CNote* note)
{
}
