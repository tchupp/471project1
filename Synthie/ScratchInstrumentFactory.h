#pragma once
#include <vector>

class CInstrument;
class CNote;

class CScratchInstrumentFactory
{
public:
	CScratchInstrumentFactory();
	virtual ~CScratchInstrumentFactory();

	void SetNote(CNote* note);
	CInstrument* CreateInstrument();

	bool LoadFile(const char* fileName);

private:
	std::vector<short> mWaveL;
	std::vector<short> mWaveR;
};
