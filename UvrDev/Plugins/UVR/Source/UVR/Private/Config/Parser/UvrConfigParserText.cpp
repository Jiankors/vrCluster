// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrConfigParserText.h"


UvrConfigParserText::UvrConfigParserText(IUvrConfigParserListener* const pListener, const FString& cfgPath) :
	UvrConfigParser(pListener)
{
	ParseFile(cfgPath);
}

bool UvrConfigParserText::ParseFile(const FString& path)
{
	// Prepare path
	FString cfgPath(path);
	FPaths::NormalizeFilename(cfgPath);

	// Load data
	UE_LOG(LogUvrConfig, Log, TEXT("Parsing config file %s"), *cfgPath);
	if (FPaths::FileExists(cfgPath))
	{
		TArray<FString> data;
		if (FFileHelper::LoadANSITextFileToStrings(*cfgPath, nullptr, data) == true)
		{
			// Parse each line from config
			for (auto line : data)
			{
				line = line.Trim().TrimTrailing();
				ParseLine(line);
			}

			// Parsed
			return true;
		}
	}

	// An error occurred
	return false;
}

void UvrConfigParserText::ParseLine(const FString& line)
{
	if (line.IsEmpty() || line.StartsWith(FString(UvrStrings::cfg::spec::Comment)))
	{
		// Skip this line
	}
	else if (line.StartsWith(FString(UvrStrings::cfg::data::cluster::Header)))
		AddClusterNode(impl_parse<SUvrConfigClusterNode>(line));
	else if (line.StartsWith(FString(UvrStrings::cfg::data::screen::Header)))
		AddScreen(impl_parse<SUvrConfigScreen>(line));
	else if (line.StartsWith(FString(UvrStrings::cfg::data::viewport::Header)))
		AddViewport(impl_parse<SUvrConfigViewport>(line));
	else if (line.StartsWith(FString(UvrStrings::cfg::data::camera::Header)))
		AddCamera(impl_parse<SUvrConfigCamera>(line));
	else if (line.StartsWith(FString(UvrStrings::cfg::data::scene::Header)))
		AddSceneNode(impl_parse<SUvrConfigSceneNode>(line));
	else if (line.StartsWith(FString(UvrStrings::cfg::data::general::Header)))
		AddGeneral(impl_parse<SUvrConfigGeneral>(line));
	else if (line.StartsWith(FString(UvrStrings::cfg::data::render::Header)))
		AddRender(impl_parse<SUvrConfigRender>(line));
	else if (line.StartsWith(FString(UvrStrings::cfg::data::stereo::Header)))
		AddStereo(impl_parse<SUvrConfigStereo>(line));
	else if (line.StartsWith(FString(UvrStrings::cfg::data::debug::Header)))
		AddDebug(impl_parse<SUvrConfigDebug>(line));
	else if (line.StartsWith(FString(UvrStrings::cfg::data::input::Header)))
		AddInput(impl_parse<SUvrConfigInput>(line));
	else if (line.StartsWith(FString(UvrStrings::cfg::data::custom::Header)))
		AddCustom(impl_parse<SUvrConfigCustom>(line));
	else
	{
		UE_LOG(LogUvrConfig, Warning, TEXT("Unknown config token [%s]"), *line);
	}
}
