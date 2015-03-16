/**
 * \file CustomEnvelopeFactory.h
 *
 * \author Theo Chupp
 *
 * \brief Factory to create specific envelopes for different types of scratches
 */

#pragma once

class CCustomEnvelope;

class CCustomEnvelopeFactory
{
public:
	CCustomEnvelopeFactory();
	virtual ~CCustomEnvelopeFactory();

	CCustomEnvelope CreateBabyScratchEnvelope();
};
