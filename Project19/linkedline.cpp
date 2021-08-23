#include "linkedline.h"

namespace Figure_2D {

	std::pair<std::list<Figure_2D::Figure*>::iterator, std::list<Figure_2D::Figure*>::iterator> LinkedLine::GetRectCoordinates() const
	{
		return { (figure1), (figure2) };
	}
	Figure_Type LinkedLine::GetType() const
	{
		return type;
	}
	void LinkedLine::WINAPI_draw(HDC hdc) const
	{
		MoveToEx(hdc, (*figure1)->GetCenter().first, (*figure1)->GetCenter().second, NULL);
		LineTo(hdc, (*figure2)->GetCenter().first, (*figure2)->GetCenter().second);
	}

}