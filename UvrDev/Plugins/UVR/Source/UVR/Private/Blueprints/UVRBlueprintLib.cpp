// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UVRBlueprintLib.h"

#include "IUvrPlugin.h"


UUVRBlueprintLib::UUVRBlueprintLib(class FObjectInitializer const & ObjectInitializer) :
	Super(ObjectInitializer)
{

}


FString UUVRBlueprintLib::UvrGetVersionString()
{
	//@todo: replace the dummy with something valuable
	return FString("0.0.0.0");
}
