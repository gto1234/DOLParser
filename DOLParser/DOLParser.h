﻿
// DOLParser.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CDOLParserApp:
// Сведения о реализации этого класса: DOLParser.cpp
//

class CDOLParserApp : public CWinApp
{
public:
	CDOLParserApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CDOLParserApp theApp;
