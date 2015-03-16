/**
 * \file ScratchInstrumentFactory.h
 *
 * \author Theo Chupp
 *
 * \brief Factory that creates scratch instruments with the proper wav samples
 */

#pragma once
#include "InstrumentFactory.h"
#include <vector>

class CNote;

class CScratchInstrumentFactory : public CInstrumentFactory
{
public:
	CScratchInstrumentFactory();
	virtual ~CScratchInstrumentFactory();

	virtual void SetNote(CNote* note) override;
	virtual CInstrument* CreateInstrument() override;

	bool LoadFile(const char* fileName);

private:
	std::vector<short> mWaveL;
	std::vector<short> mWaveR;
};
