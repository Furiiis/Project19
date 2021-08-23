#pragma once
#include <Windows.h>
#include <memory>
#include <iterator> 
#include <iomanip> 
#include <commctrl.h>

namespace Figure_2D {
	using Coordinate = std::pair<int, int>;

	const Coordinate Get_Displace_Vector(const Coordinate& from, const Coordinate& to);


	enum Figure_Type { RECTANGLE, ELLIPSE, TRIANGLE, LINKEDLINE };

	class Figure
	{
	public:
		virtual std::pair<Coordinate, Coordinate> GetRectCoordinates() const = 0;
		virtual bool IsPoint(const std::pair<long, long>& point) const = 0;
		virtual Figure_Type GetType() const = 0;
		virtual Coordinate GetCenter() const = 0;
		virtual void move(const Coordinate& displace_vector) = 0;
		virtual void graw(const Coordinate& displace_vector) = 0;
		virtual void WINAPI_draw(HDC hdc) const = 0;

	};

}