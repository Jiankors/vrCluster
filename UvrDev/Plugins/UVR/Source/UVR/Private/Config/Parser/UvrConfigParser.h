// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "IUvrConfigParserListener.h"
#include "UvrConfigTypes.h"

class UvrConfigParser : protected IUvrConfigParserListener
{
public:
	explicit UvrConfigParser(IUvrConfigParserListener* const pListener);
	virtual ~UvrConfigParser() = 0;

public:
	// Entry point for file parsing
	virtual bool ParseFile(const FString& path) = 0;

protected:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrConfigParserListener
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void AddClusterNode(const SUvrConfigClusterNode& node) override final;
	virtual void AddScreen(const SUvrConfigScreen& screen)         override final;
	virtual void AddViewport(const SUvrConfigViewport& viewport)   override final;
	virtual void AddCamera(const SUvrConfigCamera& camera)         override final;
	virtual void AddSceneNode(const SUvrConfigSceneNode& node)     override final;
	virtual void AddGeneral(const SUvrConfigGeneral& general)      override final;
	virtual void AddRender(const SUvrConfigRender& render)         override final;
	virtual void AddStereo(const SUvrConfigStereo& stereo)         override final;
	virtual void AddDebug(const SUvrConfigDebug& debug)            override final;
	virtual void AddInput(const SUvrConfigInput& input)            override final;
	virtual void AddCustom(const SUvrConfigCustom& custom)         override final;

private:
	IUvrConfigParserListener* const m_pListener;
};

