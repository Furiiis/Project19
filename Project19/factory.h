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
#include <assert.h> 
#include <iomanip> 
#include <commctrl.h>
#include <algorithm>
#include <list>
#include "figure.h"
#include "rectangle.h"
#include "ellipse.h"
#include "triangle.h"
#include "linkedline.h"


class Factory
{
public:
   Figure_2D::Figure* createFigure2D(const std::string& type, const Figure_2D::Coordinate& x, const Figure_2D::Coordinate& y)
   {
       Figure_2D::Figure* fig = nullptr;
       Figure_2D::Figure_Type fig_type = Figure_2D::Figure_Type::DEFAULT;

       size_t i = 0;
       for (auto x : Figure_2D::Figure_Type_Str)
       {
           if (x == type)
           {
               fig_type = Figure_2D::Figure_Type(i);
           }
           ++i;
       }

       switch (fig_type)
       {
       case Figure_2D::RECTANGLE:
           fig = new Figure_2D::Rectangle(x, y);
           break;
       case Figure_2D::ELLIPSE:
           fig = new Figure_2D::Ellipse(x, y);
           break;
       case Figure_2D::TRIANGLE:
           fig = new Figure_2D::Triangle(x, y);
           break;       
       default:
           assert(false);
       }
       return fig;
   };
};


