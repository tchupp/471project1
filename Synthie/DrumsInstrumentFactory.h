#pragma once
#include "InstrumentFactory.h"
#include <vector>
#include "SineWave.h"

class CNote;

class CDrumsInstrumentFactory : public CInstrumentFactory
{
public:
	CDrumsInstrumentFactory();
	virtual ~CDrumsInstrumentFactory();

	virtual void SetNote(CNote* note) override;
	virtual CInstrument* CreateInstrument() override;

	bool LoadFile(const char* filename);
	bool LoadBassWave(CSineWave wave);

private:
	std::vector<short> mWaveL;
	std::vector<short> mWaveR;

	bool mBassPresent = false;

	CSineWave mBassWave;

	void SetDrumType(std::wstring type);
};