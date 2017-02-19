// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Config/Parser/IUvrConfigParserListener.h"


class UvrConfigChecker final :
	protected IUvrConfigParserListener
{
public:
	UvrConfigChecker();
	~UvrConfigChecker();

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrConfigParserListener
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void AddClusterNode(const SUvrConfigClusterNode& node) override;
	virtual void AddScreen(const SUvrConfigScreen& screen) override;
	virtual void AddViewport(const SUvrConfigViewport& viewport) override;
	virtual void AddCamera(const SUvrConfigCamera& camera) override;
	virtual void AddSceneNode(const SUvrConfigSceneNode& actor) override;
	virtual void AddGeneral(const SUvrConfigGeneral& general) override;
	virtual void AddRender(const SUvrConfigRender& render) override;
	virtual void AddStereo(const SUvrConfigStereo& stereo) override;
	virtual void AddDebug(const SUvrConfigDebug& debug) override;
	virtual void AddInput(const SUvrConfigInput& input) override;
	virtual void AddCustom(const SUvrConfigCustom& custom) override;

private:
};
