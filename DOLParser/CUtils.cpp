#include "stdafx.h"
#include "CUtils.h"


CUtils::CUtils()
{
}


CUtils::~CUtils()
{
}



bool CUtils::StringToHexidecimal(const std::string & hexString, std::vector<short unsigned int>& hexArray)
{
	std::vector<short unsigned int> TemporaryhexArray;
	short unsigned int nNibble, nDigit;

	if (hexString.length() % 2 != 0) return false;
	TemporaryhexArray.clear();

	for (unsigned int nIndex = 0; nIndex < hexString.length(); nIndex += 2)
	{
		if (CharToHexidecimal(hexString[nIndex], nNibble) == false)
		{
			return false;
		}
		nDigit = nNibble << 4;
		if (CharToHexidecimal(hexString[nIndex+1], nNibble) == false)
		{
			return false;
		}
		nDigit |= nNibble;
		TemporaryhexArray.push_back(nDigit);
	}
	hexArray.clear();
	std::copy(TemporaryhexArray.begin(), TemporaryhexArray.end(), std::back_inserter(hexArray));
	return true;
}

bool CUtils::CharToHexidecimal(char in, short unsigned int & out)
{
	if ((in >= '0') && (in <= '9'))
	{
		out = (short unsigned int)(in - '0');
		return true;
	}
	if ((in >= 'A') && (in <= 'F'))
	{
		out = (short unsigned int)(in - 'A') + 0x0A;
		return true;
	}

	return false;
}

void CUtils::CStringToStdString(const CString & inString, std::string & outString)
{
	outString = CW2A(inString.GetString(), CP_UTF8);
}

