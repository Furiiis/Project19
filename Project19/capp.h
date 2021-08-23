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
#include "filemanager.h"


class CApp
{
	enum class CTL_ID
	{
		RECTANGLE_ID,
		ELLIPSE_ID,
		TRIANGLE_ID,
		CLEAN_ID,
		LINK_ID,
		HAND_ID,
		FILE_ID,
		NEW_ID,
		OPEN_ID,
		EXIT_ID,
		SAVE_ID,
		SAVEAS_ID,
		MEN_ID,
		CAT_ID
	};

public:
	explicit CApp();
	~CApp()
	{

	}

	int Run();

private:
	void init_native_window_obj();
	static LRESULT CALLBACK application_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void create_native_controls();

	void AddMenu(HWND hWnd);


private: //system veribles
	const std::wstring m_szAppName{ L"StaticFigures" }, m_szClassName{ L"StaticPaint_Window_class_nostyles" };
	HWND m_hWnd{}, m_hWndMenu{}, m_hWndButton{}, m_hWndEllipseButton{}, m_hWndTriangleButton{},
		m_hWndCleanButton{}, m_hWndLinkButton{}, m_hWndHandButton{};
	const int m_nAppWidth{ 1000 }, m_nAppHeight{ 600 };
	RECT Client_Rect;
	RECT NonClient_Rect;

private:

	Field field;
	bool zazhatie = false;
	bool zazhatieFigureButton = false;
	std::pair<int, int> mouse_center;
	std::list<Figure_2D::Figure*>::iterator current_figure;
	struct {
		void SetAllDown()
		{
			IsRectButton = IsEllipseButton = IsTriangleButton
				= IsLinkButton = IsHandButton = false;
		}
		bool IsRectButton;
		bool IsEllipseButton;
		bool IsTriangleButton;
		bool IsLinkButton;
		bool IsHandButton;
	} IsButton{};
	std::pair<std::list<Figure_2D::Figure*>::iterator, std::list<Figure_2D::Figure*>::iterator> for_linking;
	HMENU hMenu;
	FileManager file_manager;
	std::string default_men_move_model_path = "men.fld";
	std::string default_cat_path = "cat.fld";
};
