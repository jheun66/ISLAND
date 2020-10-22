#include "Utility.h"

void Utility::SplitString(vector<string>* result, string origin, string tok)
{
	result->clear();

	int cutAt = 0; //�ڸ� ��ġ
	//find_first_of ���ڷ� �� ���ڿ��� ������ ���� ���� ���� ������ ��ġ ��ȯ
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0���� ũ�ٸ�
			result->push_back(origin.substr(0, cutAt));

		// origin�� �ڸ� ��ġ���� ���� �ٽ� ����
		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //�ڸ��� �������� �մٸ�
		result->push_back(origin.substr(0, cutAt));
}

// �ڷ����� �ٸ��� ���� 
void Utility::SplitString(vector<wstring>* result, wstring origin, wstring tok)
{
	result->clear();

	int cutAt = 0; //�ڸ� ��ġ
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0���� ũ�ٸ�
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //�ڸ��� �������� �մٸ�
		result->push_back(origin.substr(0, cutAt));
}

// str ���ڿ��� comp�� �����ϴ��� Ȯ�� 
bool Utility::StartWith(string str, string comp)
{
	//npos no position �� ���ٴ� �Ҹ�
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

// str ���ڿ��� comp�� �����ϴ��� Ȯ��
bool Utility::Contain(string str, string comp)
{
	size_t found = str.find(comp);

	// npos�� false �ƴϸ� true
	return found != wstring::npos;
}

bool Utility::Contain(wstring str, wstring comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}

// str���� comp�� ã�� rep�� �ٲ��ִ� �Լ�
void Utility::Replace(string* str, string comp, string rep)
{
	string temp = *str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos)) != wstring::npos)
	{
		// startPos ��ġ���� comp�� ���̸�ŭ rep�� ����
		temp.replace(startPos, comp.length(), rep);
		// startPos ��ġ�� �ٲ㼭 �ݺ���
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

// string�� wstring���� ����
wstring Utility::ToWstring(string str)
{
	wstring temp = L"";
	temp.assign(str.begin(), str.end());
	return temp;
}

// wstring�� string���� ����
string Utility::ToString(wstring str)
{
	string temp = "";
	temp.assign(str.begin(), str.end());
	return temp;
}
