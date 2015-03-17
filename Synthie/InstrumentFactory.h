/**
 * \file InstrumentFactory.h
 *
 * \author Theo Chupp
 *
 * \brief base class for Instrument Factories
 */

#pragma once

class CNote;
class CInstrument;

class CInstrumentFactory
{
public:
	CInstrumentFactory();
	virtual ~CInstrumentFactory();

	virtual CInstrument* CreateInstrument() = 0;
	virtual void SetNote(CNote* note) = 0;

	//! Get the sample rate in samples per second
	double GetSampleRate() { return mSampleRate; }

	//! Set the sample rate
	void SetSampleRate(double s) { mSampleRate = s; mSamplePeriod = 1 / s; }

private:
	double mSampleRate;
	double mSamplePeriod;
};
