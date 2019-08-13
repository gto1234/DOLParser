#include "stdafx.h"
#include "CTagList.h"
#include "CUtils.h"
#include "CTag.h"
#include <vector>


CTagList::CTagList()
{	
}


CTagList::~CTagList()
{
}

void CTagList::PrintList(std::string &outString)
{
	outString.clear();

	for (CTag &it : *this)
	{
		outString += it.PrintTagInfo();

		outString.push_back('\r');
		outString.push_back('\n');
	}
}

bool CTagList::BuildByDolString(const std::string & DolString)
{
	std::vector<CTag> localTempStorage;
	std::vector<short unsigned int> hexArray;
	long unsigned int nLocalTagName = 0;
	bool bTagComplete = true;
	bool bLengthByte = false;
	unsigned int nCurrentTagNameCount = 0;

	if (CUtils::StringToHexidecimal(DolString, hexArray) == false)
	{
		return false;
	}

	localTempStorage.clear();
	for (short unsigned int it : hexArray)
	{
		if (bLengthByte == true)
		{
			CTag objTag;
			objTag.SetData(nLocalTagName, it);
			localTempStorage.push_back(objTag);
			bLengthByte = false;
			bTagComplete = true;
			nLocalTagName = 0;
		}
		else
		{
			if (bTagComplete == true)
			{
				nLocalTagName = it;
				if (!((it & 0x1F) == 0x1F))
				{
					bLengthByte = true;
				}
				bTagComplete = false;
			}
			else
			{
				(nLocalTagName <<= 8) |= it;
				if (!(it & 0x80))
				{
					bLengthByte = true;
				}
			}
			
		}
	}
	if (bTagComplete == false)
	{
		return false;
	}
	clear();
	std::copy(localTempStorage.begin(), localTempStorage.end(), std::back_inserter(*this));

	return true;
}

bool CTagList::UpdateByDolValue(const std::string & DolValueString)
{
	std::vector<short unsigned int> hexArray;

	if (CUtils::StringToHexidecimal(DolValueString, hexArray) == false)
	{
		return false;
	}
	
	if (hexArray.size() != GetToatlTagLength())
	{
		return false;
	}
	else
	{
		int nDolValueStartIndex = 0;
		for (CTag &it : *this)
		{
			std::vector<short unsigned int> CTagArg;
			std::copy(hexArray.begin() + nDolValueStartIndex, hexArray.begin() + nDolValueStartIndex + it.GetTagLength() , std::back_inserter(CTagArg));

			it.SetData(CTagArg);

			nDolValueStartIndex += it.GetTagLength();
		}	
	}
	return true;
}

unsigned int CTagList::GetToatlTagLength()
{
	unsigned int nTotalLength = 0;

	for (CTag &it : *this)
	{
		nTotalLength += it.GetTagLength();
	}
	return nTotalLength;
}
