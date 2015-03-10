#pragma once
#include <vector>

class CScratchInstrument;
class CInstrument;
class CNote;

class CScratchInstrumentFactory
{
public:
	CScratchInstrumentFactory();
	virtual ~CScratchInstrumentFactory();

	void SetNote(CNote* note);
	CScratchInstrument* CreateInstrument();

	bool LoadFile(const char* fileName);

private:
	std::vector<short> mWaveL;
	std::vector<short> mWaveR;
};
