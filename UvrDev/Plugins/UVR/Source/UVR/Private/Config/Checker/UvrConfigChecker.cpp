// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrConfigChecker.h"

#include "Config/Parser/UvrConfigParserText.h"
#include "Config/Parser/UvrConfigParserXml.h"


UvrConfigChecker::UvrConfigChecker()
{
	UE_LOG(LogUvrConfig, Verbose, TEXT("UvrConfigManager .dtor"));
}

UvrConfigChecker::~UvrConfigChecker()
{
	UE_LOG(LogUvrConfig, Verbose, TEXT("UvrConfigManager .dtor"));
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrConfigParserListener
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrConfigChecker::AddClusterNode(const SUvrConfigClusterNode& node)
{
	//UE_LOG(LogUvrConfig, Log, TEXT("Found cluster node: id=%s, addr=%s, role=%s, port_cs=%d, port_ss=%d, port_ce=%d"),
	//	*node.Id, *node.Addr, node.IsMaster ? TEXT("master") : TEXT("slave"), node.Port_CS, node.Port_SS, node.Port_CE);
}

void UvrConfigChecker::AddScreen(const SUvrConfigScreen& screen)
{
	//UE_LOG(LogUvrConfig, Log, TEXT("Found screen: id=%s, parent=%s, loc=%s, rot=%s, size=%s"),
	//	*screen.Id, *screen.ParentId, *screen.Loc.ToString(), *screen.Rot.ToString(), *screen.Size.ToString());
}

void UvrConfigChecker::AddViewport(const SUvrConfigViewport& viewport)
{
	//UE_LOG(LogUvrConfig, Log, TEXT("Found viewport: id=%s, loc=%s, size=%s"),
	//	*viewport.Id, *viewport.Loc.ToString(), *viewport.Size.ToString());
}

void UvrConfigChecker::AddCamera(const SUvrConfigCamera& camera)
{
}

void UvrConfigChecker::AddSceneNode(const SUvrConfigSceneNode& actor)
{
	//UE_LOG(LogUvrConfig, Log, TEXT("Found scene node: id=%s, parent=%s, type=%d, loc=%s, rot=%s"),
	//	*actor.Id, *actor.ParentId, static_cast<int>(actor.Type), *actor.Loc.ToString(), *actor.Rot.ToString());
}

void UvrConfigChecker::AddGeneral(const SUvrConfigGeneral& general)
{
}

void UvrConfigChecker::AddRender(const SUvrConfigRender& render)
{
}

void UvrConfigChecker::AddStereo(const SUvrConfigStereo& stereo)
{
}

void UvrConfigChecker::AddDebug(const SUvrConfigDebug& debug)
{
}

void UvrConfigChecker::AddInput(const SUvrConfigInput& input)
{
}

void UvrConfigChecker::AddCustom(const SUvrConfigCustom& custom)
{
}

