// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Engine.h"

typedef FNoncopyable UvrNoncopyable;

class UvrNonmoveable
{
protected:
	// ensure the class cannot be constructed directly
	UvrNonmoveable() {}
	// the class should not be used polymorphically
	~UvrNonmoveable() {}
private:
	UvrNonmoveable(UvrNonmoveable&&) = delete;
	UvrNonmoveable& operator=(FNoncopyable&&) = delete;
};
