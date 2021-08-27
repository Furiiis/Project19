#pragma once
#include "ellipse.h"

namespace Figure_2D {

	
	Coordinate Ellipse::GetCenter() const
	{
		return { x.first + (y.first - x.first) / 2, x.second + (y.second - x.second) / 2 };
	}

	bool Ellipse::IsPoint(const std::pair<long, long>& point) const
	{
		std::pair<double, double> center = { x.first + (y.first - x.first) / 2, x.second + (y.second - x.second) / 2 };
		auto xx = (point.first - center.first) * (point.first - center.first) / ((((y.first - x.first) / 2) * ((y.first - x.first) / 2))) +
			(point.second - center.second) * (point.second - center.second) / ((((y.second - x.second) / 2) * ((y.second - x.second) / 2)));
		if (xx <= 1) return true;
		else return false;
	}
	Figure_Type Ellipse::GetType() const
	{
		return type;
	}
	void Ellipse::move(const Coordinate& displace_vector)
	{
		Coordinate X = { this->x.first + displace_vector.first,  this->x.second + displace_vector.second };
		Coordinate Y = { this->y.first + displace_vector.first,  this->y.second + displace_vector.second };
		this->x = std::move(X); this->y = std::move(Y);
	}
	void Ellipse::graw(const Coordinate& displace_vector)
	{
		Coordinate Y = { this->y.first + displace_vector.first,  this->y.second + displace_vector.second };
		this->y = std::move(Y);
	}
	void Ellipse::WINAPI_draw(HDC hdc) const
	{
		::Ellipse(hdc, x.first, x.second, y.first, y.second);
	}


}