#include "stdafx.h"
#include "CTag.h"

#include <sstream>



CTag::CTag()
{
	m_nTagName = 0;
	m_nLength = 0;
	m_nData.clear();
}


CTag::~CTag()
{
}

//bool CTag::SetData(long unsigned int nTagName, std::string sData)
//{
//	if (nTagName == 0) return false;
//
//	m_nData.clear();
//	std::copy(sData.begin(), sData.end(), std::back_inserter(m_nData));
//	m_
//
//	return true;
//}
//
//bool CTag::SetData(long unsigned int nTagName, char * pData, unsigned int nLength)
//{
//	if ((nTagName == 0) || (pData == NULL)) return false;
//
//	m_nData.clear();
//	for (int nIndex = 0; nIndex < nLength; nIndex++)
//	{
//		m_nData.push_back(pData[nIndex]);
//	}
//
//	return true;
//}

bool CTag::SetData(long unsigned int nTagName, unsigned int nLength)
{
	if (nTagName == 0) return false;

	m_nData.clear();
	m_nTagName = nTagName;
	m_nLength = nLength;

	for (unsigned int nIndex = 0; nIndex < nLength; nIndex++)
	{
		m_nData.push_back(0);
	}

	return true;
}

void CTag::SetData(const std::vector<unsigned short int>& inData)
{
	m_nData.clear();
	std::copy(inData.begin(), inData.end(), std::back_inserter(m_nData));
}

std::string CTag::PrintTagInfo()
{
	std::string outString;
	char tpBuffer[2048];

	int nCount = sprintf_s(tpBuffer, "%X:\r\n", m_nTagName);
	outString = std::string(tpBuffer, nCount);

	for (unsigned short int &byteElem : m_nData)
	{
		nCount = sprintf_s(tpBuffer, "%02X ", byteElem);
		outString += std::string(tpBuffer, nCount);
	}
	return outString;
}
