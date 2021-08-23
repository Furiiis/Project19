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
#include "rectangle.h"
#include "ellipse.h"
#include "triangle.h"
#include "linkedline.h"
#include "field.h"


class FileManager
{
public:
	void LoadFromFile(Field& field, char* path);

	void LoadToFile(Field& field, char* path);

	void open_file(HWND hWnd, Field& field);

	void save_file(HWND hWnd, Field& field);

	std::string Get_Main_Path() const;

	void Set_Main_Path(const std::string& path);

private:
	std::string main_path;
	const std::string default_cat_path = "men.fld";
	const std::string default_men_move_model_path = "cat.fld";


};
