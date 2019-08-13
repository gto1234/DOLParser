
// DOLParserDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "DOLParser.h"
#include "DOLParserDlg.h"
#include "afxdialogex.h"
#include "CUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CDOLParserDlg



CDOLParserDlg::CDOLParserDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DOLPARSER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pEditBkBrush = new CBrush(RGB(0, 0, 0));
	m_pparsedDataFontLocal = new CFont();
}

void CDOLParserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PARSED_DATA, m_ed_ParsedData);
	DDX_Control(pDX, IDC_EDIT_DOL_VALUE, m_ed_DolValue);
	DDX_Control(pDX, IDC_EDIT_DOL_RELATED_DATA, m_ed_DolRelatedData);
}

BEGIN_MESSAGE_MAP(CDOLParserDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_PARSE, &CDOLParserDlg::OnClickedButtonParse)
	ON_BN_CLICKED(IDC_BUTTONCOPY_TO_CLIPBOARD, &CDOLParserDlg::OnClickedButtoncopyToClipboard)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDOLParserDlg::OnClickedButtonClear)
END_MESSAGE_MAP()


// Обработчики сообщений CDOLParserDlg

BOOL CDOLParserDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	m_pparsedDataFontLocal->CreateFontW(16, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, _T("Courier New"));
	m_ed_ParsedData.SetFont(m_pparsedDataFontLocal);
	m_aTagList.clear();


	

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CDOLParserDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CDOLParserDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CDOLParserDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CDOLParserDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (pWnd == (CWnd*)(&m_ed_ParsedData))
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(0, 0, 0));
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	}
	else
	{
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}	
}


void CDOLParserDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: добавьте свой код обработчика сообщений
	delete m_pEditBkBrush;
	delete m_pparsedDataFontLocal;
}


void CDOLParserDlg::OnClickedButtonParse()
{
	CString dolvalue;
	m_ed_DolValue.GetWindowTextW(dolvalue);
	std::string stdDolValue;
	CUtils::CStringToStdString(dolvalue, stdDolValue);
	bool bConverted = false;
	
	if (m_aTagList.BuildByDolString(stdDolValue) == true)
	{
		CString DolRelatedData;
		m_ed_DolRelatedData.GetWindowTextW(DolRelatedData);
		std::string stdDolRelatedData;
		CUtils::CStringToStdString(DolRelatedData, stdDolRelatedData);
		
		if (m_aTagList.UpdateByDolValue(stdDolRelatedData) == true)
		{
			std::string outStr;
			m_aTagList.PrintList(outStr);
			m_ed_ParsedData.SetWindowTextW(CString(outStr.c_str()));
			bConverted = true;
		}
	}
	if (bConverted == false)
	{
		m_ed_ParsedData.SetWindowTextW(CString("Incorrect data"));
	}

}


void CDOLParserDlg::OnClickedButtoncopyToClipboard()
{
	LPTSTR  lptstrCopy;
	HGLOBAL hglbCopy;
	CString strText;

	if (OpenClipboard())
	{
		m_ed_ParsedData.GetWindowText(strText);
		unsigned int strSize = strText.GetLength();//get your string lenght
		hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (strSize + 1) * sizeof(TCHAR));//allocate the memory object with GMEM_MOVEABLE 
		if (hglbCopy == NULL)
		{
			CloseClipboard();
			return;
		}

		lptstrCopy = (LPTSTR)GlobalLock(hglbCopy);
		memcpy(lptstrCopy, strText.GetBuffer(), strSize * sizeof(TCHAR)); //copy the text data
		lptstrCopy[strSize] = (TCHAR)0;//the null terminator
		GlobalUnlock(hglbCopy);

		EmptyClipboard();

		SetClipboardData(CF_UNICODETEXT, hglbCopy);

		CloseClipboard();
	}
}


void CDOLParserDlg::OnClickedButtonClear()
{
	m_ed_ParsedData.SetWindowTextW(CString(""));
}
