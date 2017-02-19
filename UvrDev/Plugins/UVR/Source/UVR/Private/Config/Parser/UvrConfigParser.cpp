// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrConfigParser.h"



UvrConfigParser::UvrConfigParser(IUvrConfigParserListener* const pListener) :
	m_pListener(pListener)
{
}

UvrConfigParser::~UvrConfigParser()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrConfigParserListener
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrConfigParser::AddClusterNode(const SUvrConfigClusterNode& node)
{
	m_pListener->AddClusterNode(node);
}

void UvrConfigParser::AddScreen(const SUvrConfigScreen& screen)
{
	m_pListener->AddScreen(screen);
}

void UvrConfigParser::AddViewport(const SUvrConfigViewport& viewport)
{
	m_pListener->AddViewport(viewport);
}

void UvrConfigParser::AddCamera(const SUvrConfigCamera& camera)
{
	m_pListener->AddCamera(camera);
}

void UvrConfigParser::AddSceneNode(const SUvrConfigSceneNode& node)
{
	m_pListener->AddSceneNode(node);
}

void UvrConfigParser::AddGeneral(const SUvrConfigGeneral& general)
{
	m_pListener->AddGeneral(general);
}

void UvrConfigParser::AddRender(const SUvrConfigRender& render)
{
	m_pListener->AddRender(render);
}

void UvrConfigParser::AddStereo(const SUvrConfigStereo& stereo)
{
	m_pListener->AddStereo(stereo);
}

void UvrConfigParser::AddDebug(const SUvrConfigDebug& debug)
{
	m_pListener->AddDebug(debug);
}

void UvrConfigParser::AddInput(const SUvrConfigInput& input)
{
	m_pListener->AddInput(input);
}

void UvrConfigParser::AddCustom(const SUvrConfigCustom& custom)
{
	m_pListener->AddCustom(custom);
}
