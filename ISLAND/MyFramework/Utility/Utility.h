#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <iomanip>
#include <tchar.h>
#include <functional>

using namespace std;

class Utility
{
public:
	static void SplitString
	(vector<string>* result, string origin, string tok);

	static void SplitString
	(vector<wstring>* result, wstring origin, wstring tok);

	static bool StartWith(string str, string comp);
	static bool StartWith(wstring str, wstring comp);

	static bool Contain(string str, string comp);
	static bool Contain(wstring str, wstring comp);

	static void Replace(string* str, string comp, string rep);
	static void Replace(wstring* str, wstring comp, wstring rep);

	static wstring ToWstring(string str);
	static string ToString(wstring str);
};