/**
 * \file CustomEnvelopeFactory.cpp
 *
 * \author Theo Chupp
 */

#include "stdafx.h"
#include "CustomEnvelope.h"
#include "CustomEnvelopeFactory.h"


CCustomEnvelopeFactory::CCustomEnvelopeFactory()
{
}


CCustomEnvelopeFactory::~CCustomEnvelopeFactory()
{
}

CEnvelope* CCustomEnvelopeFactory::CreateBabyScratchEnvelope()
{
	auto envelope = new CCustomEnvelope();
	envelope->AddPoint(0.01, 1);
	envelope->AddPoint(2.10, -1);
	envelope->AddPoint(2.25, 1.1);
	envelope->AddPoint(2.45, -0.9);
	envelope->AddPoint(2.7, 1);
	envelope->Start();
	return envelope;
}

CEnvelope* CCustomEnvelopeFactory::CreateScribbleScratchEnvelope()
{
	auto envelope = new CCustomEnvelope();
	return envelope;
}
