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
	envelope->AddPoint(1, -0.5);
	envelope->AddPoint(2, 1);
	envelope->AddPoint(3, -0.5);
	envelope->AddPoint(4, 1);
	envelope->AddPoint(5, -0.5);
	envelope->AddPoint(6, 1);
	envelope->AddPoint(7, 0);
	return envelope;
}

CEnvelope* CCustomEnvelopeFactory::CreateScribbleScratchEnvelope()
{
	auto envelope = new CCustomEnvelope();
	envelope->AddPoint(0.01, 1);
	envelope->AddPoint(2.10, -1);
	envelope->AddPoint(2.25, 1.1);
	envelope->AddPoint(2.45, -0.9);
	envelope->AddPoint(2.70, 1.2);
	envelope->AddPoint(3.00, -0.8);
	envelope->AddPoint(3.35, 1.3);
	envelope->AddPoint(3.80, -0.7);
	envelope->AddPoint(4.35, 1.4);
	envelope->AddPoint(6.00, 0);
	return envelope;
}
