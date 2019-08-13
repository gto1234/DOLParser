#pragma once

#include <string>
#include <vector>
class CUtils
{
public:
	CUtils();
	~CUtils();
	
	static bool StringToHexidecimal(const std::string &hexString, std::vector<short unsigned int> &hexArray);
	static bool CharToHexidecimal(char in, short unsigned int &out);
	static void CStringToStdString(const CString &inString, std::string &outString);
};

