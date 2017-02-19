// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once


class UvrViewportArea
{
public:
	UvrViewportArea() :
		m_loc(FIntPoint::ZeroValue),
		m_size(FIntPoint::ZeroValue)
	{ }

	UvrViewportArea(const FIntPoint& loc, const FIntPoint& size) :
		m_loc(loc),
		m_size(size)
	{ }

	UvrViewportArea(int32 x, int32 y, int32 w, int32 h) :
		m_loc(FIntPoint(x, y)),
		m_size(FIntPoint(w, h))
	{ }

public:
	bool IsValid() const
	{ return m_size.X > 0 && m_size.Y > 0; }

	FIntPoint GetLocation() const
	{ return m_loc; }
	
	FIntPoint GetSize() const
	{ return m_size; }

	void SetLocation(const FIntPoint& loc)
	{ m_loc = loc; }

	void SetLocation(int32 x, int32 y)
	{ m_loc = FIntPoint(x, y); }

	void SetSize(const FIntPoint& size)
	{ m_size = size; }

	void SetSize(int32 w, int32 h)
	{ m_size = FIntPoint(w, h); }

private:
	FIntPoint m_loc;
	FIntPoint m_size;
};
