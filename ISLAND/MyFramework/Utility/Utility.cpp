#include "Utility.h"

void Utility::SplitString(vector<string>* result, string origin, string tok)
{
	result->clear();

	int cutAt = 0; //자를 위치
	//find_first_of 인자로 들어간 문자열의 문자중 가장 먼저 나온 문자의 위치 반환
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //자르는 위치가 0보다 크다면
			result->push_back(origin.substr(0, cutAt));

		// origin을 자른 위치에서 부터 다시 시작
		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //자르고도 남은것이 잇다면
		result->push_back(origin.substr(0, cutAt));
}

// 자료형만 다르고 동일 
void Utility::SplitString(vector<wstring>* result, wstring origin, wstring tok)
{
	result->clear();

	int cutAt = 0; //자를 위치
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //자르는 위치가 0보다 크다면
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //자르고도 남은것이 잇다면
		result->push_back(origin.substr(0, cutAt));
}

// str 문자열이 comp로 시작하는지 확인 
bool Utility::StartWith(string str, string comp)
{
	//npos no position 즉 없다는 소리
	string::size_type index = str.find(comp);
	if (index != string::npos && (int)index == 0)
		return true;

	return false;
}

bool Utility::StartWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

// str 문자열이 comp를 포함하는지 확인
bool Utility::Contain(string str, string comp)
{
	size_t found = str.find(comp);

	// npos면 false 아니면 true
	return found != wstring::npos;
}

bool Utility::Contain(wstring str, wstring comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}

// str에서 comp를 찾아 rep로 바꿔주는 함수
void Utility::Replace(string* str, string comp, string rep)
{
	string temp = *str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos)) != wstring::npos)
	{
		// startPos 위치에서 comp의 길이만큼 rep로 변경
		temp.replace(startPos, comp.length(), rep);
		// startPos 위치를 바꿔서 반복함
		startPos += rep.length();
	}

	*str = temp;
}

void Utility::Replace(wstring* str, wstring comp, wstring rep)
{
	wstring temp = *str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos)) != wstring::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}

	*str = temp;
}

// string을 wstring으로 변경
wstring Utility::ToWstring(string str)
{
	wstring temp = L"";
	temp.assign(str.begin(), str.end());
	return temp;
}

// wstring을 string으로 변경
string Utility::ToString(wstring str)
{
	string temp = "";
	temp.assign(str.begin(), str.end());
	return temp;
}
