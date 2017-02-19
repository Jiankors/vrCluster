// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrMessage.h"


class UvrSession;

struct IUvrSessionListener
{
	virtual ~IUvrSessionListener()
	{ }

	virtual void NotifySessionOpen(UvrSession* pSession)
	{ }

	virtual void NotifySessionClose(UvrSession* pSession)
	{ }

	// Pass a message to a concrete implementation
	virtual UvrMessage::Ptr ProcessMessage(UvrMessage::Ptr msg) = 0;

};

