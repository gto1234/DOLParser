
// DOLParserDlg.h: файл заголовка
//

#pragma once
#include "CTagList.h"

// Диалоговое окно CDOLParserDlg
class CDOLParserDlg : public CDialogEx
{
// Создание
public:
	CDOLParserDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DOLPARSER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	CBrush* m_pEditBkBrush;
	CFont* m_pparsedDataFontLocal;
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ed_ParsedData;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnClickedButtonParse();
	afx_msg void OnClickedButtoncopyToClipboard();
	afx_msg void OnClickedButtonClear();
private:
	CTagList m_aTagList;
public:
	CEdit m_ed_DolValue;
	CEdit m_ed_DolRelatedData;
};
