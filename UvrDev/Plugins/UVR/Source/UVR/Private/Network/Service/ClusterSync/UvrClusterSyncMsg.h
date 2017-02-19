// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once


//@todo: encapsulate strings below in message classes
namespace UvrClusterSyncMsg
{
	constexpr static auto ProtocolName = "ClusterSync";
	
	constexpr static auto TypeRequest  = "request";
	constexpr static auto TypeResponse = "response";

	namespace WaitForGameStart
	{
		constexpr static auto name = "WaitForGameStart";
	};

	namespace WaitForFrameStart
	{
		constexpr static auto name = "WaitForFrameStart";
	};

	namespace WaitForFrameEnd
	{
		constexpr static auto name = "WaitForFrameEnd";
	};

	namespace WaitForTickEnd
	{
		constexpr static auto name = "WaitForTickEnd";
	};

	namespace GetDeltaTime
	{
		constexpr static auto name         = "GetDeltaTime";
		constexpr static auto argDeltaTime = "DeltaTime";
	};

	namespace GetSyncData
	{
		constexpr static auto name = "GetSyncData";
	};

	namespace GetInputData
	{
		constexpr static auto name = "GetInputData";
	}
};
