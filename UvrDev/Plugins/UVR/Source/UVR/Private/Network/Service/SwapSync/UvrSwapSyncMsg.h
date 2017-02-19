// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once


//@todo: encapsulate strings below in message classes
struct UvrSwapSyncMsg
{
	constexpr static auto ProtocolName = "SwapSync";
	
	constexpr static auto TypeRequest  = "request";
	constexpr static auto TypeResponse = "response";

	struct WaitForSwapSync
	{
		constexpr static auto name = "WaitForSwapSync";
		constexpr static auto argThreadTime  = "ThreadTime";
		constexpr static auto argBarrierTime = "BarrierTime";
	};
};
