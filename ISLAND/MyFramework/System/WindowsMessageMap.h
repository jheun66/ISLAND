#pragma once
#include <unordered_map>
#include <Windows.h>

using namespace std;

// 윈도우 메시지 매핑
class WindowsMessageMap
{
private:
	unordered_map<DWORD, string> map;

public:
	WindowsMessageMap();
	string operator()(DWORD msg, LPARAM lp, WPARAM wp) const;
};