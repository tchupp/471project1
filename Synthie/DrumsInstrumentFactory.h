#pragma once

#include "InstrumentFactory.h"

class CDrumsInstrumentFactory : public CInstrumentFactory
{
public:
	CDrumsInstrumentFactory();
	virtual ~CDrumsInstrumentFactory();

	virtual void SetNote(CNote* note) override;
	virtual CInstrument* CreateInstrument() override;
};
