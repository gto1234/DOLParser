#pragma once
#include "CTag.h"
#include <list>

class CTagList : public std::list<CTag>
{
public:
	CTagList();
	~CTagList();

	void PrintList(std::string &outString);
	bool BuildByDolString(const std::string &DolString);
	bool UpdateByDolValue(const std::string &DolValueString);
	unsigned int GetToatlTagLength();
};

