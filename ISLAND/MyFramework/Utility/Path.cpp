// 미리컴파일된 헤더 사용안함
// Win3d꺼 사용
#include "Utility.h"
#include "Path.h"

bool Path::ExistFile(string path)
{
    return ExistFile(Utility::ToWstring(path));
}

bool Path::ExistFile(wstring path)
{
    DWORD fileValue = GetFileAttributes(path.c_str());
    // 실패시 -1 반환(uint형이므로 uint의 최대값), 그 이외에는 성공
    return fileValue < 0xFFFFFFFF;
}

bool Path::ExistDirectory(string path)
{
    return ExistDirectory(Utility::ToWstring(path));
}

bool Path::ExistDirectory(wstring path)
{
    DWORD attribute = GetFileAttributes(path.c_str());

    // 디렉토리일때만 true
    BOOL temp = (attribute != INVALID_FILE_ATTRIBUTES &&
        (attribute & FILE_ATTRIBUTE_DIRECTORY));

    return temp == TRUE;
}

string Path::Combine(string path1, string path2)
{
    return path1 + path2;
}

wstring Path::Combine(wstring path1, wstring path2)
{
    return path1 + path2;
}

string Path::Combine(vector<string> paths)
{
    string temp = "";
    for (string path : paths)
        temp += path;

    return temp;
}

wstring Path::Combine(vector<wstring> paths)
{
    wstring temp = L"";
    for (wstring path : paths)
        temp += path;

    return temp;
}

string Path::GetDirectoryName(string path)
{
    // path의 마지막 / 까지 잘라 파일명만 제거
    Utility::Replace(&path, "\\", "/");
    size_t index = path.find_last_of('/');

    return path.substr(0, index + 1);
}

wstring Path::GetDirectoryName(wstring path)
{
    Utility::Replace(&path, L"\\", L"/");
    size_t index = path.find_last_of('/');

    return path.substr(0, index + 1);
}

// 파일 확장자 구하는 함수
string Path::GetExtension(string path)
{
    // .이후 문자열을 잘라서 반환
    Utility::Replace(&path, "\\", "/");
    size_t index = path.find_last_of('.');

    return path.substr(index + 1, path.length());;
}

wstring Path::GetExtension(wstring path)
{
    Utility::Replace(&path, L"\\", L"/");
    size_t index = path.find_last_of('.');

    return path.substr(index + 1, path.length());;
}

// 파일명.확장자 반환
string Path::GetFileName(string path)
{
    // 마지막 /이후 파일명 반환
    Utility::Replace(&path, "\\", "/");
    size_t index = path.find_last_of('/');

    return path.substr(index + 1, path.length());
}

wstring Path::GetFileName(wstring path)
{
    Utility::Replace(&path, L"\\", L"/");
    size_t index = path.find_last_of('/');

    return path.substr(index + 1, path.length());
}

// 확장자 제거한 파일명 반환함수
string Path::GetFileNameWithoutExtension(string path)
{
    // 파일명 구하고 .이전까지 문자열 반환
    string fileName = GetFileName(path);

    size_t index = fileName.find_last_of('.');
    return fileName.substr(0, index);
}

wstring Path::GetFileNameWithoutExtension(wstring path)
{
    wstring fileName = GetFileName(path);

    size_t index = fileName.find_last_of('.');
    return fileName.substr(0, index);
}

// 필요한 확장자 계속 추가해주자!!
const WCHAR* Path::ImageFilter = L"Image\0*.png;*.bmp;*.jpg";
const WCHAR* Path::ShaderFilter = L"HLSL file\0*.hlsl";
const WCHAR* Path::TextFilter = L"Text file\0*.txt";

void Path::OpenFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hWnd)
{
    WCHAR name[255];
    wcscpy_s(name, file.c_str());

    wstring tempFolder = folder;

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFilter = filter;	// 어떤 파일을 불러올지 필터
    ofn.lpstrFile = name;
    ofn.lpstrFileTitle = L"불러오기";
    ofn.nMaxFile = 255;
    ofn.lpstrInitialDir = tempFolder.c_str();	// inital directory 설정
    ofn.Flags = OFN_NOCHANGEDIR;	// directory 변경불가 flag

    if (GetOpenFileName(&ofn) == TRUE)
    {
        if (func != NULL)
        {
            wstring loadName = name;
            Utility::Replace(&loadName, L"\\", L"/");

            // wstring을 인자로 받는 함수 객체 호출
            func(loadName);
        }
    }
}

void Path::SaveFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hWnd)
{
    WCHAR name[255];
    wcscpy_s(name, file.c_str());

    wstring tempFolder = folder;

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = name;
    ofn.lpstrFileTitle = L"저장하기";
    ofn.nMaxFile = 255;
    ofn.lpstrInitialDir = tempFolder.c_str();
    ofn.Flags = OFN_NOCHANGEDIR;

    if (GetSaveFileName(&ofn) == TRUE)
    {
        if (func != NULL)
        {
            wstring saveName = name;
            Utility::Replace(&saveName, L"\\", L"/");

            func(saveName);
        }
    }
}

void Path::SaveFileDialogWithoutExtension(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, wstring ext, HWND hWnd)
{
    WCHAR name[255];
    wcscpy_s(name, file.c_str());

    wstring tempFolder = folder;

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = name;
    ofn.lpstrFileTitle = L"저장하기";
    ofn.nMaxFile = 255;
    ofn.lpstrInitialDir = tempFolder.c_str();
    ofn.Flags = OFN_NOCHANGEDIR;

    if (GetSaveFileName(&ofn) == TRUE)
    {
        if (func != NULL)
        {
            wstring saveName = name;
            Utility::Replace(&saveName, L"\\", L"/");
            wstring fileName = GetFileNameWithoutExtension(saveName);
            wstring directory = GetDirectoryName(saveName);

            saveName = directory + fileName + L"." + ext;
            func(saveName);
        }
    }
}

// 해당 path에 있는 파일들을 files에 넣어주는 함수
// 미리 정보를 담은 데이터 만들어 놓고 가져오는 용도로 사용할 수도 있음
void Path::GetFiles(vector<string>* files, string path, string filter, bool bFindSubFolder)
{
    vector<wstring> wFiles;
    wstring wPath = Utility::ToWstring(path);
    wstring wFilter = Utility::ToWstring(filter);

    GetFiles(&wFiles, wPath, wFilter, bFindSubFolder);

    for (wstring str : wFiles)
        files->push_back(Utility::ToString(str));
}

//path : ../Temp/
//filter : *.txt
void Path::GetFiles(vector<wstring>* files, wstring path, wstring filter, bool bFindSubFolder)
{
    wstring file = path + filter;

    WIN32_FIND_DATA findData;
    HANDLE handle = FindFirstFile(file.c_str(), &findData);
    if (handle != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
            {
                // findData가 directory면 해당 폴더 안에 있는 파일들을 찾음
                if (bFindSubFolder == true && findData.cFileName[0] != '.')
                {
                    wstring folder = path + wstring(findData.cFileName) + L"/";
                    GetFiles(files, folder, filter, bFindSubFolder);

                }
            }
            else //해당 경로에 속성이 폴더가 아닐때. 즉 파일일때
            {
                wstring fileName = path + wstring(findData.cFileName);
                files->push_back(fileName);
            }
        } while (FindNextFile(handle, &findData));

        FindClose(handle);
    }
}

void Path::CreateFolder(string path)
{
    CreateFolder(Utility::ToWstring(path));
}

void Path::CreateFolder(wstring path)
{	
    // 파일이 존재하지 않으면 Directory 생성
    if (ExistDirectory(path) == false)
        CreateDirectory(path.c_str(), NULL);
}

// 생성하고 싶은 폴더안에 폴더가 있는 경우 내부까지 생성
void Path::CreateFolders(string path)
{
    CreateFolders(Utility::ToWstring(path));
}

void Path::CreateFolders(wstring path)
{
    Utility::Replace(&path, L"\\", L"/");

    vector<wstring> folders;
    Utility::SplitString(&folders, path, L"/");

    wstring temp = L"";
    for (wstring folder : folders)
    {
        temp += folder + L"/";

        CreateFolder(temp);
    }
}
