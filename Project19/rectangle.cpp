#pragma once
#include "rectangle.h"

namespace Figure_2D {

	Coordinate Rectangle::GetCenter() const
	{
		return { x.first + (y.first - x.first) / 2, x.second + (y.second - x.second) / 2 };
	}
	
	bool Rectangle::IsPoint(const std::pair<long, long>& point) const
	{
		return point.first >= x.first && point.first <= y.first && point.second >= x.second && point.second <= y.second;
	}
	Figure_Type Rectangle::GetType() const
	{
		return type;
	}
	void Rectangle::move(const Coordinate& displace_vector)
	{
		Coordinate X = { this->x.first + displace_vector.first,  this->x.second + displace_vector.second };
		Coordinate Y = { this->y.first + displace_vector.first,  this->y.second + displace_vector.second };
		this->x = std::move(X); this->y = std::move(Y);
	}
	void Rectangle::graw(const Coordinate& displace_vector)
	{
		Coordinate Y = { this->y.first + displace_vector.first,  this->y.second + displace_vector.second };
		this->y = std::move(Y);
	}
	void Rectangle::WINAPI_draw(HDC hdc) const
	{
		::Rectangle(hdc, x.first, x.second, y.first, y.second);
	}
}