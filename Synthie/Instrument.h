/**
 * \file Instrument.h
 *
 * \author Theo Chupp
 *
 * \brief Base class for Instruments
 */

#pragma once
#include "AudioNode.h"
#include "AmplitudeFilter.h"

class CNote;

class CInstrument :
	public CAudioNode
{
public:
	CInstrument();
	virtual ~CInstrument();

	virtual void SetNote(CNote* note, double secPerBeat) = 0;

	double Send(int i) { return mSends[i]; }
	void SetSend(int i, double value) { mSends[i] = value; }

protected:
	CAmplitudeFilter mAmplitudeFilter;
	CEnvelope* mEnvelope;
	double mSends[5];
};
