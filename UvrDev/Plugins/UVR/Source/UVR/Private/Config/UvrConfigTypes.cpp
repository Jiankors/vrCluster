// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrConfigTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////
// SUvrConfigClusterNode
//////////////////////////////////////////////////////////////////////////////////////////////
FString SUvrConfigClusterNode::ToString() const
{
	return FString::Printf(TEXT("[%s + %s=%s, %s=%s, %s=%s, %s=%s, %s=%s, %s=%d, %s=%d]"),
		*SUvrConfigBase::ToString(),
		UvrStrings::cfg::data::Id, *Id, 
		UvrStrings::cfg::data::cluster::Addr, *Addr, 
		UvrStrings::cfg::data::cluster::Master, UvrHelpers::str::BoolToStr(IsMaster), 
		UvrStrings::cfg::data::cluster::Screen, *ScreenId,
		UvrStrings::cfg::data::cluster::Viewport, *ViewportId, 
		UvrStrings::cfg::data::cluster::PortCS, Port_CS,
		UvrStrings::cfg::data::cluster::PortSS, Port_SS);
}

bool SUvrConfigClusterNode::DeserializeFromString(const FString& line)
{
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::Id),                Id);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::cluster::Screen),   ScreenId);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::cluster::Viewport), ViewportId);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::cluster::Master),   IsMaster);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::cluster::Addr),     Addr);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::cluster::PortCS),   Port_CS);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::cluster::PortSS),   Port_SS);
	return SUvrConfigBase::DeserializeFromString(line);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// SUvrConfigViewport
//////////////////////////////////////////////////////////////////////////////////////////////
FString SUvrConfigViewport::ToString() const
{
	return FString::Printf(TEXT("[%s + %s=%s, %s=%s, %s=%d, %s=%d, %s=%s, %s=%s]"),
		*SUvrConfigBase::ToString(),
		UvrStrings::cfg::data::Id, *Id,
		UvrStrings::cfg::data::Loc, *Loc.ToString(),
		UvrStrings::cfg::data::viewport::Width,  Size.X,
		UvrStrings::cfg::data::viewport::Height, Size.Y,
		UvrStrings::cfg::data::viewport::FlipH, UvrHelpers::str::BoolToStr(FlipHorizontal),
		UvrStrings::cfg::data::viewport::FlipV, UvrHelpers::str::BoolToStr(FlipVertical));
}

bool SUvrConfigViewport::DeserializeFromString(const FString& line)
{
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::Id),               Id);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::viewport::PosX),   Loc.X);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::viewport::PosY),   Loc.Y);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::viewport::Width),  Size.X);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::viewport::Height), Size.Y);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::viewport::FlipH),  FlipHorizontal);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::viewport::FlipV),  FlipVertical);
	return SUvrConfigBase::DeserializeFromString(line);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// SUvrConfigSceneNode
//////////////////////////////////////////////////////////////////////////////////////////////
FString SUvrConfigSceneNode::ToString() const
{
	return FString::Printf(TEXT("[%s + %s=%s, %s=%s, %s=%s, %s=%s, %s=%s, %s=%d]"),
		*SUvrConfigBase::ToString(),
		UvrStrings::cfg::data::Id, *Id,
		UvrStrings::cfg::data::ParentId, *ParentId,
		UvrStrings::cfg::data::Loc, *Loc.ToString(),
		UvrStrings::cfg::data::Rot, *Rot.ToString(),
		UvrStrings::cfg::data::scene::TrackerId, *TrackerId,
		UvrStrings::cfg::data::scene::TrackerCh, TrackerCh);
}

bool SUvrConfigSceneNode::DeserializeFromString(const FString& line)
{
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::Id),               Id);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::ParentId),         ParentId);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::Loc),              Loc);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::Rot),              Rot);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::scene::TrackerId), TrackerId);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::scene::TrackerCh), TrackerCh);
	return SUvrConfigBase::DeserializeFromString(line);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// SUvrConfigScreen
//////////////////////////////////////////////////////////////////////////////////////////////
FString SUvrConfigScreen::ToString() const
{
	return FString::Printf(TEXT("[%s + %s=%s]"),
		*SUvrConfigSceneNode::ToString(),
		UvrStrings::cfg::data::screen::Size, *Size.ToString());
}

bool SUvrConfigScreen::DeserializeFromString(const FString& line)
{
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::screen::Size), Size);
	return SUvrConfigSceneNode::DeserializeFromString(line);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// SUvrConfigCamera
//////////////////////////////////////////////////////////////////////////////////////////////
FString SUvrConfigCamera::ToString() const
{
	return FString::Printf(TEXT("[%s + ]"),
		*SUvrConfigSceneNode::ToString());
}

bool SUvrConfigCamera::DeserializeFromString(const FString& line)
{
	return SUvrConfigSceneNode::DeserializeFromString(line);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// SUvrConfigInput
//////////////////////////////////////////////////////////////////////////////////////////////
FString SUvrConfigInput::ToString() const
{
	return FString::Printf(TEXT("[%s + %s=%s, %s=%s, %s={%s}]"),
		*SUvrConfigBase::ToString(),
		UvrStrings::cfg::data::Id, *Id,
		UvrStrings::cfg::data::input::Type, *Type,
		TEXT("params"), *Params);
}

bool SUvrConfigInput::DeserializeFromString(const FString& line)
{
	// Save full string to allow an input device to parse (polymorphic)
	Params = line;

	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::Id), Id);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::input::Type), Type);

	return SUvrConfigBase::DeserializeFromString(line);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// SUvrConfigGeneral
//////////////////////////////////////////////////////////////////////////////////////////////
FString SUvrConfigGeneral::ToString() const
{
	return FString::Printf(TEXT("[%s + %s=%d]"),
		*SUvrConfigBase::ToString(),
		UvrStrings::cfg::data::general::SwapSyncPolicy, SwapSyncPolicy);
}

bool SUvrConfigGeneral::DeserializeFromString(const FString& line)
{
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::general::SwapSyncPolicy), SwapSyncPolicy);
	return SUvrConfigBase::DeserializeFromString(line);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// SUvrConfigRender
//////////////////////////////////////////////////////////////////////////////////////////////
FString SUvrConfigRender::ToString() const
{
	return FString::Printf(TEXT("%s + "),
		*SUvrConfigBase::ToString());
}

bool SUvrConfigRender::DeserializeFromString(const FString& line)
{
	return SUvrConfigBase::DeserializeFromString(line);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// SUvrConfigStereo
//////////////////////////////////////////////////////////////////////////////////////////////
FString SUvrConfigStereo::ToString() const
{
	return FString::Printf(TEXT("[%s + %s=%s, %s=%f]"),
		*SUvrConfigBase::ToString(),
		UvrStrings::cfg::data::stereo::EyeSwap, UvrHelpers::str::BoolToStr(EyeSwap),
		UvrStrings::cfg::data::stereo::EyeDist, EyeDist);
}

bool SUvrConfigStereo::DeserializeFromString(const FString& line)
{
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::stereo::EyeDist), EyeDist);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::stereo::EyeSwap), EyeSwap);
	return SUvrConfigBase::DeserializeFromString(line);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// SUvrConfigDebug
//////////////////////////////////////////////////////////////////////////////////////////////
FString SUvrConfigDebug::ToString() const
{
	return FString::Printf(TEXT("[%s + %s=%s, %s=%s, %s=%f]"),
		*SUvrConfigBase::ToString(),
		UvrStrings::cfg::data::debug::DrawStats, UvrHelpers::str::BoolToStr(DrawStats),
		UvrStrings::cfg::data::debug::LagSim,  UvrHelpers::str::BoolToStr(LagSimulateEnabled),
		UvrStrings::cfg::data::debug::LagTime, LagMaxTime);
}

bool SUvrConfigDebug::DeserializeFromString(const FString& line)
{
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::debug::DrawStats), DrawStats);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::debug::LagSim),    LagSimulateEnabled);
	UvrHelpers::str::ExtractCommandLineValue(line, FString(UvrStrings::cfg::data::debug::LagTime),   LagMaxTime);
	return SUvrConfigBase::DeserializeFromString(line);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// SUvrConfigCustom
//////////////////////////////////////////////////////////////////////////////////////////////
FString SUvrConfigCustom::ToString() const
{
	FString str = SUvrConfigBase::ToString() +  FString( + "[");
	int i = 0;

	for (auto it = Args.CreateConstIterator(); it; ++it)
		str += FString::Printf(TEXT("\nCustom argument %d: %s=%s\n"), i++, *it->Key, *it->Value);

	str += FString("]");

	return str;
}

bool SUvrConfigCustom::DeserializeFromString(const FString& line)
{
	// Non-typical way of specifying custom arguments (we don't know
	// the argument names) forces us to perform individual parsing approach.
	FString tmpLine = line;

	// Prepare string before parsing
	tmpLine.RemoveFromStart(UvrStrings::cfg::data::custom::Header);
	tmpLine.Trim().TrimTrailing();

	// Break into argument-value pairs
	TArray<FString> pairs;
	tmpLine.ParseIntoArray(pairs, TEXT(" "));

	// Fill data from pairs
	for (auto pair : pairs)
	{
		FString key, val;
		if (pair.Split(FString(UvrStrings::strKeyValSeparator), &key, &val))
			if(key.Len() > 0 && val.Len() > 0)
				Args.Add(key, val);
	}

	return SUvrConfigBase::DeserializeFromString(line);
}
