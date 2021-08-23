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
#include "rectangle.h"
#include "ellipse.h"
#include "triangle.h"
#include "linkedline.h"
#include "field.h"
#include "filemanager.h"
#include "capp.h"

int CALLBACK wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	CApp app{};
	return app.Run();
}