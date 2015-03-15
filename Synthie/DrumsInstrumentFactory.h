#pragma once
#include "InstrumentFactory.h"
#include <vector>

class CNote;

class CDrumsInstrumentFactory : public CInstrumentFactory
{
public:
	CDrumsInstrumentFactory();
	virtual ~CDrumsInstrumentFactory();

	virtual void SetNote(CNote* note) override;
	virtual CInstrument* CreateInstrument() override;

	bool LoadFile(const char* filename);

private:
	std::vector<short> mWaveL;
	std::vector<short> mWaveR;
};