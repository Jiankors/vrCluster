// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrConfigTypes.h"

struct IUvrConfigParserListener
{
public:
	virtual ~IUvrConfigParserListener()
	{ }

	virtual void AddClusterNode(const SUvrConfigClusterNode& cnode) = 0;
	virtual void AddScreen(const SUvrConfigScreen& screen) = 0;
	virtual void AddViewport(const SUvrConfigViewport& viewport) = 0;
	virtual void AddCamera(const SUvrConfigCamera& camera) = 0;
	virtual void AddSceneNode(const SUvrConfigSceneNode& snode) = 0;
	virtual void AddGeneral(const SUvrConfigGeneral& general) = 0;
	virtual void AddRender(const SUvrConfigRender& render) = 0;
	virtual void AddStereo(const SUvrConfigStereo& stereo) = 0;
	virtual void AddDebug(const SUvrConfigDebug& debug) = 0;
	virtual void AddInput(const SUvrConfigInput& input) = 0;
	virtual void AddCustom(const SUvrConfigCustom& custom) = 0;
};
