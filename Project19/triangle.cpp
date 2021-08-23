#include "triangle.h"


namespace Figure_2D {

	std::pair<Coordinate, Coordinate>  Triangle::GetRectCoordinates() const
	{
		return std::pair<Coordinate, Coordinate>{x, y};
	}
	Coordinate  Triangle::GetCenter() const
	{
		return { x.first + (y.first - x.first) / 2, x.second + (y.second - x.second) / 2 };
	}

	bool  Triangle::IsPoint(const std::pair<long, long>& point) const
	{
		Coordinate a = { x.first, x.second + (y.second - x.second) };
		Coordinate b = { x.first + (y.first - x.first) / 2, x.second };
		Coordinate c = { y.first,  x.second + (y.second - x.second) };
		int a1 = (a.first - point.first) * (b.second - a.second) - (b.first - a.first) * (a.second - point.second);
		int a2 = (b.first - point.first) * (c.second - b.second) - (c.first - b.first) * (b.second - point.second);
		int a3 = (c.first - point.first) * (a.second - c.second) - (a.first - c.first) * (c.second - point.second);
		if (a1 * a2 >= 0 && a1 * a3 >= 0 && a3 * a2 >= 0) return true;
		else return false;
	}

	Figure_Type  Triangle::GetType() const
	{
		return type;
	}
	void  Triangle::move(const Coordinate& displace_vector)
	{
		Coordinate X = { this->x.first + displace_vector.first,  this->x.second + displace_vector.second };
		Coordinate Y = { this->y.first + displace_vector.first,  this->y.second + displace_vector.second };
		this->x = std::move(X); this->y = std::move(Y);
	}
	void  Triangle::graw(const Coordinate& displace_vector)
	{
		//Coordinate X = { this->x.first + displace_vector.first,  this->x.second + displace_vector.second };
		Coordinate Y = { this->y.first + displace_vector.first,  this->y.second + displace_vector.second };
		this->y = std::move(Y);
	}
	void  Triangle::WINAPI_draw(HDC hdc) const
	{
		Figure_2D::Coordinate a = { x.first, y.second };
		Figure_2D::Coordinate b = { x.first + (y.first - x.first) / 2, x.second };
		Figure_2D::Coordinate c = y;
		MoveToEx(hdc, a.first, a.second, NULL);
		LineTo(hdc, b.first, b.second);
		LineTo(hdc, c.first, c.second);
		LineTo(hdc, a.first, a.second);
	}

}