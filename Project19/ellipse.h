#pragma once
#include "figure.h"



namespace Figure_2D {


	class Ellipse : public Figure
	{
	public:
		Ellipse(Coordinate X, Coordinate Y) : x(X), y(Y) {}
		std::pair<Coordinate, Coordinate> GetRectCoordinates() const override;

		Coordinate GetCenter() const override;


		bool IsPoint(const std::pair<long, long>& point) const override;

		Figure_Type GetType() const override;

		void move(const Coordinate& displace_vector) override;

		void graw(const Coordinate& displace_vector) override;

		void WINAPI_draw(HDC hdc) const override;

	private:
		Figure_Type type = Figure_Type::ELLIPSE;
		Coordinate x;
		Coordinate y;
	};

}