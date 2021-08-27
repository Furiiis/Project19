#pragma once
#include "capp.h"


CApp::CApp()
{
	FileManager fm;

	using std::wstring;
	using std::string;

	try
	{
		std::string filename = "default.fld";
		this->file_manager.LoadFromFile(this->field, &filename[0]);
		this->init_native_window_obj();
		this->create_native_controls();
	}
	catch (const std::exception& e)
	{
		string expt_data = e.what();
		ExitProcess(EXIT_FAILURE);
	}
}

int CApp::Run()
{
	MSG _msg{};
	ShowWindow(this->m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(this->m_hWnd);
	while (GetMessage(&_msg, nullptr, 0, 0))
	{
		TranslateMessage(&_msg);
		DispatchMessage(&_msg);
	}
	return static_cast<int>(_msg.wParam);
}

void CApp::init_native_window_obj()
{
	using std::runtime_error;
	using namespace std::string_literals;

	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.lpfnWndProc = application_proc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = this->m_szClassName.c_str();
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc))
		throw runtime_error("Error, can't register main window class!"s);

	RECT _windowRC{ 0, 0, this->m_nAppWidth, this->m_nAppHeight };
	AdjustWindowRect(&_windowRC, WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE | WS_THICKFRAME, false);

	if (this->m_hWnd = CreateWindowEx(
		0,
		this->m_szClassName.c_str(),
		this->m_szAppName.c_str(),
		WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE | WS_THICKFRAME,
		(GetSystemMetrics(SM_CXSCREEN) - _windowRC.right) / 2,
		(GetSystemMetrics(SM_CXSCREEN) - _windowRC.bottom * 2.2) / 2,
		_windowRC.right, _windowRC.bottom, nullptr, nullptr, nullptr, this
	); !this->m_hWnd)
		throw runtime_error("Error, can't create main window!"s);

}

LRESULT CALLBACK CApp::application_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CApp* pApp;
	if (uMsg == WM_NCCREATE)
	{
		pApp = static_cast<CApp*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApp)))
		{
			if (GetLastError() != 0)
				return false;
		}
	}
	else
	{
		pApp = reinterpret_cast<CApp*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	if (pApp)
	{
		pApp->m_hWnd = hWnd;
		return pApp->window_proc(hWnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK CApp::window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP memBM = CreateCompatibleBitmap(hdc, Client_Rect.right - Client_Rect.left, Client_Rect.bottom - Client_Rect.top);
		SelectObject(memDC, memBM);
		SetBkMode(memDC, TRANSPARENT);
		SelectObject(memDC, GetStockObject(NULL_BRUSH));
		FillRect(memDC, &this->Client_Rect, CreateSolidBrush(RGB(255, 255, 255)));
		FillRect(memDC, &this->NonClient_Rect, CreateSolidBrush(RGB(220, 220, 220)));

		for (auto x : this->field.GetFigures())
		{
			x->WINAPI_draw(memDC);
		}
		for (const auto& linkedline : this->field.GetLinkedLines())
		{
			linkedline.WINAPI_draw(memDC);
		}

		BitBlt(hdc, 0, 0, Client_Rect.right - Client_Rect.left, Client_Rect.bottom - Client_Rect.top, memDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);

		DeleteDC(memDC);
		DeleteObject(memBM);
	}
	return 0;
	case WM_MOUSEMOVE:
	{
		if (wParam & MK_LBUTTON & zazhatieFigureButton)
		{
			this->field.GetFigures().back()->graw(Figure_2D::Get_Displace_Vector(this->field.GetFigures().back()->GetRectCoordinates().second, { LOWORD(lParam), HIWORD(lParam) }));
			InvalidateRect(hWnd, &this->Client_Rect, false);
		}	
		else if (wParam & MK_LBUTTON & (this->IsButton.IsTriangleButton || this->IsButton.IsRectButton || this->IsButton.IsEllipseButton))
		{
			Factory factory;
			this->field.AddFigure(factory.createFigure2D(Figure_2D::Figure_Type_Str[chosen_figure], { LOWORD(lParam) - 30, HIWORD(lParam) - 10 },
					{ LOWORD(lParam), HIWORD(lParam) }));
				zazhatieFigureButton = true;
				this->IsButton.SetAllDown();
		}			
		else if (wParam & MK_LBUTTON & this->IsButton.IsHandButton & zazhatie)
		{
			for (auto x : field.GetFigures())
			{
				x->move(Figure_2D::Get_Displace_Vector({ this->mouse_center.first, this->mouse_center.second }, { LOWORD(lParam), HIWORD(lParam) }));
			}
			InvalidateRect(hWnd, &this->Client_Rect, false);
			this->mouse_center = { LOWORD(lParam), HIWORD(lParam) };

		}
		else if (wParam & zazhatie) {

			zazhatie = true;
			(*current_figure)->move(Figure_2D::Get_Displace_Vector({ this->mouse_center.first, this->mouse_center.second }, { LOWORD(lParam), HIWORD(lParam) }));

			this->mouse_center = { LOWORD(lParam), HIWORD(lParam) };

			InvalidateRect(hWnd, &this->Client_Rect, false);
		}

		else if (wParam & MK_LBUTTON & IsButton.IsHandButton)
		{
			this->mouse_center = { LOWORD(lParam), HIWORD(lParam) };
			zazhatie = true;
		}
		else if (wParam & MK_LBUTTON & IsButton.IsLinkButton)
		{
			size_t i = 0;
			for (auto x : field.GetFigures())
			{
				if (x->IsPoint({ LOWORD(lParam), HIWORD(lParam) }))
				{

					if (this->for_linking.first == this->field.GetFigures().end())
					{
						this->for_linking.first = next(field.GetFigures().begin(), i);
					}
					else if (this->for_linking.second == this->field.GetFigures().end())
					{
						if (next(field.GetFigures().begin(), i) != this->for_linking.first)
						{
							this->for_linking.second = next(field.GetFigures().begin(), i);
							this->field.AddLinkedLine(Figure_2D::LinkedLine(std::move(this->for_linking.first), std::move(this->for_linking.second)));
							InvalidateRect(hWnd, &this->Client_Rect, false);
							this->IsButton.IsLinkButton = false;
							this->for_linking = { this->field.GetFigures().end(), this->field.GetFigures().end() };
						}
						else break;
						this->IsButton.IsLinkButton = false;
					}
					else
					{
						this->IsButton.IsLinkButton = false;
					}
					break;

				}
				++i;
			}
		}
		else if (wParam & MK_LBUTTON) {

			size_t i = 0;
			for (auto x : field.GetFigures())
			{
				if (x->IsPoint({ LOWORD(lParam), HIWORD(lParam) }))
				{
					zazhatie = true;
					this->mouse_center = { LOWORD(lParam), HIWORD(lParam) };

					this->current_figure = std::next(field.GetFigures().begin(), i);
					break;
				}
				++i;
			}
		}
		else
		{
			zazhatie = false;
			zazhatieFigureButton = false;
		}

	}
	return 0;
	case WM_COMMAND:
	{
		switch (static_cast<CTL_ID>(LOWORD(wParam)))
		{
		case CTL_ID::RECTANGLE_ID:
		{
			this->IsButton.SetAllDown();
			this->IsButton.IsRectButton = true;
			chosen_figure = Figure_2D::Figure_Type::RECTANGLE;
			this->for_linking = { field.GetFigures().end(), field.GetFigures().end() };
		}
		break;
		case CTL_ID::ELLIPSE_ID:
		{
			this->IsButton.SetAllDown();
			this->IsButton.IsEllipseButton = true;
			chosen_figure = Figure_2D::Figure_Type::ELLIPSE;
			this->for_linking = { field.GetFigures().end(), field.GetFigures().end() };
		}
		break;
		case CTL_ID::TRIANGLE_ID:
		{
			this->IsButton.SetAllDown();
			this->IsButton.IsTriangleButton = true;
			chosen_figure = Figure_2D::Figure_Type::TRIANGLE;
			this->for_linking = { field.GetFigures().end(), field.GetFigures().end() };
		}
		break;
		case CTL_ID::CLEAN_ID:
		{
			this->field.DeleteFigures();
			this->field.DeleteLinkedLines();
			this->IsButton.SetAllDown();
			InvalidateRect(hWnd, &this->Client_Rect, false);
		}
		break;
		case CTL_ID::LINK_ID:
		{
			this->IsButton.SetAllDown();
			this->IsButton.IsLinkButton = true;
			this->for_linking = { field.GetFigures().end(), field.GetFigures().end() };
		}
		break;
		case CTL_ID::HAND_ID:
		{

			this->for_linking = { field.GetFigures().end(), field.GetFigures().end() };
			if (this->IsButton.IsHandButton)
				this->IsButton.SetAllDown();
			else {
				this->IsButton.SetAllDown();
				this->IsButton.IsHandButton = true;
			}

		}
		break;
		case CTL_ID::EXIT_ID:
		{
			DestroyWindow(m_hWnd);
		}
		break;
		case CTL_ID::NEW_ID:
		{
			file_manager.save_file(m_hWnd, this->field);
			MessageBeep(MB_ICONINFORMATION);
		}
		break;
		case CTL_ID::OPEN_ID:
		{
			file_manager.open_file(m_hWnd, this->field);
			InvalidateRect(hWnd, &this->Client_Rect, false);
		}
		break;
		case CTL_ID::MEN_ID:
		{
			file_manager.LoadFromFile(this->field, &this->default_cat_path[0]);
			InvalidateRect(hWnd, &this->Client_Rect, false);
		}
		break;
		case CTL_ID::CAT_ID:
		{
			file_manager.LoadFromFile(this->field, &this->default_men_move_model_path[0]);
			InvalidateRect(hWnd, &this->Client_Rect, false);
		}
		break;
		case CTL_ID::SAVE_ID:
		{
			if (this->file_manager.Get_Main_Path().empty())
			{
				file_manager.save_file(m_hWnd, this->field);
			}
			else
			{
				char* path;
				file_manager.LoadToFile(this->field, &file_manager.Get_Main_Path()[0]);
			}
		}
		break;
		case CTL_ID::SAVEAS_ID:
		{
			file_manager.save_file(m_hWnd, this->field);
		}
		break;
		}
	}
	return 0;
	case WM_SIZE:
	{
		Client_Rect.left = 0;
		Client_Rect.top = 49;
		Client_Rect.right = LOWORD(lParam);
		Client_Rect.bottom = HIWORD(lParam);
		NonClient_Rect.left = 0;
		NonClient_Rect.top = 0;
		NonClient_Rect.right = LOWORD(lParam);
		NonClient_Rect.bottom = 49;
	}
	return 0;
	case WM_DESTROY:
	{
		PostQuitMessage(EXIT_SUCCESS);
	}
	return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void CApp::create_native_controls()
{
	using std::runtime_error;
	using namespace std::string_literals;
	AddMenu(m_hWnd);
	if (this->m_hWndButton = CreateWindowEx(
		0,
		L"BUTTON",
		L"RECT",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		5, 5, 60, 40, this->m_hWnd, reinterpret_cast<HMENU>(CTL_ID::RECTANGLE_ID), nullptr, nullptr
	); !this->m_hWndButton)
		throw runtime_error("Error, can't create button!"s);

	if (this->m_hWndEllipseButton = CreateWindowEx(
		0,
		L"BUTTON",
		L"ELLIPSE",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		70, 5, 60, 40, this->m_hWnd, reinterpret_cast<HMENU>(CTL_ID::ELLIPSE_ID), nullptr, nullptr
	); !this->m_hWndEllipseButton)
		throw runtime_error("Error, can't create button!"s);
	if (this->m_hWndTriangleButton = CreateWindowEx(
		0,
		L"BUTTON",
		L"TRIAN",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		135, 5, 60, 40, this->m_hWnd, reinterpret_cast<HMENU>(CTL_ID::TRIANGLE_ID), nullptr, nullptr
	); !this->m_hWndTriangleButton)
		throw runtime_error("Error, can't create button!"s);
	if (this->m_hWndCleanButton = CreateWindowEx(
		0,
		L"BUTTON",
		L"CLEAN",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		200, 5, 60, 40, this->m_hWnd, reinterpret_cast<HMENU>(CTL_ID::CLEAN_ID), nullptr, nullptr
	); !this->m_hWndCleanButton)
		throw runtime_error("Error, can't create button!"s);
	if (this->m_hWndLinkButton = CreateWindowEx(
		0,
		L"BUTTON",
		L"LINK",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		265, 5, 60, 40, this->m_hWnd, reinterpret_cast<HMENU>(CTL_ID::LINK_ID), nullptr, nullptr
	); !this->m_hWndLinkButton)
		throw runtime_error("Error, can't create button!"s);
	if (this->m_hWndHandButton = CreateWindowEx(
		0,
		L"BUTTON",
		L"HAND",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		330, 5, 60, 40, this->m_hWnd, reinterpret_cast<HMENU>(CTL_ID::HAND_ID), nullptr, nullptr
	); !this->m_hWndHandButton)
		throw runtime_error("Error, can't create button!"s);

}

void CApp::AddMenu(HWND hWnd)
{
	this->hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubOpenMenu = CreateMenu();

	AppendMenu(hFileMenu, MF_STRING, (UINT_PTR)CTL_ID::NEW_ID, L"New");
	AppendMenu(hFileMenu, MF_STRING, (UINT_PTR)CTL_ID::OPEN_ID, L"Open");
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubOpenMenu, L"OpenDefaults");
	AppendMenu(hSubOpenMenu, MF_STRING, (UINT_PTR)CTL_ID::MEN_ID, L"men.fld");
	AppendMenu(hSubOpenMenu, MF_STRING, (UINT_PTR)CTL_ID::CAT_ID, L"cat.fld");
	AppendMenu(hFileMenu, MF_STRING, (UINT_PTR)CTL_ID::SAVE_ID, L"Save");
	AppendMenu(hFileMenu, MF_STRING, (UINT_PTR)CTL_ID::SAVEAS_ID, L"SaveAs");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, (UINT_PTR)CTL_ID::EXIT_ID, L"Exit");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");

	SetMenu(hWnd, hMenu);
}


