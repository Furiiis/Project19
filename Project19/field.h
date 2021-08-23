#pragma once
#include "figure.h"
#include "linkedline.h"


class Field
{
public:
	void AddFigure(Figure_2D::Figure* figure);

	void AddLinkedLine(const Figure_2D::LinkedLine& figure);

	std::list<Figure_2D::Figure*>& GetFigures();

	std::vector<Figure_2D::LinkedLine> GetLinkedLines() const;

	void DeleteFigures();

	void DeleteLinkedLines();

	~Field()
	{
		for (auto& x : figures)
		{
			delete x;
		}
	}
private:
	std::list<Figure_2D::Figure*> figures;
	std::vector<Figure_2D::LinkedLine> linked_lines;
};