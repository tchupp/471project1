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
