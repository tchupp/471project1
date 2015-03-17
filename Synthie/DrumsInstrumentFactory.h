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

private:
	std::vector<short> mWaveL;
	std::vector<short> mWaveR;

	bool LoadFile(const char* filename);
	bool LoadBassWave();
	bool mPitchFilter = false;
	bool mResonFilter = false;

	void SetDrumType(std::wstring type);
};