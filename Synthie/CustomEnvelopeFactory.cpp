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

CCustomEnvelope CCustomEnvelopeFactory::CreateBabyScratchEnvelope()
{
	return CCustomEnvelope();
}