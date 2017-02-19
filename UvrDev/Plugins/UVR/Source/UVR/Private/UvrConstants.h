// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Engine.h"


namespace UvrConstants
{
	namespace net
	{
		static constexpr int32  ClientConnectTriesAmount    = 10;   // times
		static constexpr float  ClientConnectRetryDelay     = 1.0f; // sec
		static constexpr uint32 BarrierGameStartWaitTimeout = 20000; // ms
		static constexpr uint32 BarrierWaitTimeout          = 5000; // ms
		static constexpr int32  SocketBufferSize            = INT16_MAX; // bytes
		static constexpr int32  MessageBufferSize           = INT16_MAX; // bytes
	};
};
