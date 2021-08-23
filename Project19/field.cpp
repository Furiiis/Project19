#include "field.h"

void Field::AddFigure(Figure_2D::Figure* figure)
{
	figures.push_back(figure);
}
void Field::AddLinkedLine(const Figure_2D::LinkedLine& figure)
{
	linked_lines.push_back(figure);
}
std::list<Figure_2D::Figure*>& Field::GetFigures()
{
	return figures;
}
std::vector<Figure_2D::LinkedLine> Field::GetLinkedLines() const
{
	return linked_lines;
}
void Field::DeleteFigures()
{
	figures.clear();
}
void Field::DeleteLinkedLines()
{
	linked_lines.clear();
}

