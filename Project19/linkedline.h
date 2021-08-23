#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <exception>
#include <memory>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream> 
#include <iomanip> 
#include <commctrl.h>
#include <algorithm>
#include <list>
#include "figure.h"

namespace Figure_2D {

	class LinkedLine
	{
	public:
		LinkedLine(std::list<Figure_2D::Figure*>::iterator fig1, std::list<Figure_2D::Figure*>::iterator fig2)
			: figure1(fig1), figure2(fig2) {}

		std::pair<std::list<Figure_2D::Figure*>::iterator, std::list<Figure_2D::Figure*>::iterator> GetRectCoordinates() const;

		Figure_Type GetType() const;

		void WINAPI_draw(HDC hdc) const;


	private:
		std::list<Figure_2D::Figure*>::iterator figure1;
		std::list<Figure_2D::Figure*>::iterator figure2;
		Figure_Type type = Figure_Type::LINKEDLINE;
	};
}