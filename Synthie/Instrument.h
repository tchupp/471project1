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

protected:
	CAmplitudeFilter mAmplitudeFilter;
	CEnvelope* mEnvelope;
};
