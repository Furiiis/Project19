#include "filemanager.h"
#include "factory.h"

void FileManager::LoadFromFile(Field& field, char* path)
{
	Factory factory;
	field.DeleteFigures();
	field.DeleteLinkedLines();
	std::string filename = path;
	if (find(filename.begin(), filename.end(), '.') == filename.end())
		filename += ".fld";
	std::ifstream file(filename);
	Figure_2D::Coordinate X, Y;
	size_t x = 0; size_t y = 0;
	while (!file.eof())
	{
		std::string str, type;
		getline(file, str);
		if (str.empty()) return;
		std::istringstream is(str);
		is >> type;
		if (type == "LinkedLine")
		{
			is.ignore(3);
			is >> x;
			is.ignore(4);
			is >> y;
		}
		else {
			is.ignore(3);
			is >> X.first;
			is.ignore(1);
			is >> X.second;
			is.ignore(4);
			is >> Y.first;
			is.ignore(1);
			is >> Y.second;
		}		
		if (type == "LinkedLine")
		{
			field.AddLinkedLine(Figure_2D::LinkedLine(std::next(field.GetFigures().begin(), x), std::next(field.GetFigures().begin(), y)));
		}
		else
		{
			field.AddFigure(factory.createFigure2D(type, X, Y));
		}

	}
	this->main_path = path;
}
void FileManager::LoadToFile(Field& field, char* path)
{
	std::string filename = path;
	if (find(filename.begin(), filename.end(), '.') == filename.end())
		filename += ".fld";
	std::ofstream out;
	out.open(path);
	if (out.is_open())
	{
		for (auto x : field.GetFigures())
		{		

			out << Figure_2D::Figure_Type_Str[x->GetType()] << " {{"
		         << x->GetRectCoordinates().first.first <<
				", " << x->GetRectCoordinates().first.second << "}, {" <<
				x->GetRectCoordinates().second.first << ", " <<
				x->GetRectCoordinates().second.second << "}}\n";
		}
		for (auto& x : field.GetLinkedLines())
		{
			out << "LinkedLine {[" << std::distance(field.GetFigures().begin(), x.GetRectCoordinates().first) <<
				"], [" << std::distance(field.GetFigures().begin(), x.GetRectCoordinates().second) << "]}\n";
		}

	}
	this->main_path = path;
}
void FileManager::open_file(HWND hWnd, Field& field)
{
	OPENFILENAME ofn;
	size_t i;
	char file_name[200];
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = LPWSTR(file_name);
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 200;
	ofn.lpstrFilter = L"Fld Files\0*.FLD\0";
	ofn.nFilterIndex = 1;

	GetOpenFileName(&ofn);
	char adf[200];
	wcstombs_s(&i, adf, 200,
		ofn.lpstrFile, 200);


	LoadFromFile(field, adf);
}

void FileManager::save_file(HWND hWnd, Field& field)
{
	OPENFILENAME ofn;
	size_t i;
	char file_name[200];
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = LPWSTR(file_name);
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 200;
	ofn.lpstrFilter = L"FLD Files\0*.fld";
	ofn.nFilterIndex = 1;

	GetSaveFileName(&ofn);
	char adf[200];
	wcstombs_s(&i, adf, 200,
		ofn.lpstrFile, 200);

	LoadToFile(field, adf);
}

std::string FileManager::Get_Main_Path() const
{
	return this->main_path;
}

void FileManager::Set_Main_Path(const std::string& path)
{
	this->main_path = path;
}