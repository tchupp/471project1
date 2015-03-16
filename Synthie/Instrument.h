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

	virtual void SetNote(CNote *note, double secPerBeat) = 0;

protected:
	CAmplitudeFilter mAmplitudeFilter;
};
