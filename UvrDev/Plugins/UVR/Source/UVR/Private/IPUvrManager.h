// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Engine.h"

struct IPUvrManager
{
	virtual ~IPUvrManager()
	{ }

	// Called at start to initialize internals
	virtual bool Init()
	{ return true; }

	// Called before application exit to release internals
	virtual void Release()
	{ }

	// Called on each session start before first level start (before the first tick)
	virtual bool StartSession(const FString& configPath)
	{ return true; }

	// Called on each session end at early step before exit (before UGameEngine::Preexit)
	virtual void EndSession()
	{ }

	// Called each time a new game level starts
	virtual bool StartGame(UWorld* pWorld)
	{ return true; }

	// Called when current level is going to be closed (i.e. when loading new map)
	virtual void EndGame()
	{ }

	// Called every frame before world Tick
	virtual void PreTick(float DeltaSeconds)
	{ }

	// Called every frame after world Tick
	virtual void PostTick(float DeltaSeconds)
	{ }
};
