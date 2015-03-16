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
};
