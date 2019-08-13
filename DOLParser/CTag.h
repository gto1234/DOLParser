#pragma once

#include <string>
#include <vector>

class CTag
{
public:
	CTag();
	~CTag();

	//bool SetData(long unsigned int nTagName, std::string sData);
	//bool SetData(long unsigned int nTagName, char *pData, unsigned int nLength);
	bool SetData(long unsigned int nTagName, unsigned int nLength);
	unsigned int GetTagLength() { return m_nLength; }
	void SetData(const std::vector<unsigned short int> &inData);
	std::string PrintTagInfo();

private:
	long unsigned int m_nTagName;
	unsigned int m_nLength;
	std::vector<short unsigned int> m_nData;
};

