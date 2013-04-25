#pragma once

#include <Windows.h>

#if WIN32
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string wchar_t2string(const wchar_t *wchar)
{
	string str = "";
	int index = 0;
	while(wchar[index] != 0)
	{
		str += (char)wchar[index];
		++index;
	}
	return str;
}

wchar_t *string2wchar_t(const string &str)
{
	wchar_t wchar[260];
	int index = 0;
	while(index < str.size())
	{
		wchar[index] = (wchar_t)str[index];
		++index;
	}
	wchar[index] = 0;
	return wchar;
}

vector<string> listFilesInDirectory(string directoryName)
{
	WIN32_FIND_DATA FindFileData;
	wchar_t * FileName = string2wchar_t(directoryName);
	HANDLE hFind = FindFirstFile(FileName, &FindFileData);

	vector<string> listFileNames;
	listFileNames.push_back(wchar_t2string(FindFileData.cFileName));

	while (FindNextFile(hFind, &FindFileData))
		listFileNames.push_back(wchar_t2string(FindFileData.cFileName));

	return listFileNames;
}
#endif