
// MFCLibTestDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCLibTest.h"
#include "MFCLibTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern "C" _declspec(dllimport) double Min(const double* Numbers, const int Count);
extern "C" _declspec(dllimport) double Max(const double* Numbers, const int Count);
extern "C" _declspec(dllimport) double Sum(const double* Numbers, const int Count);
extern "C" _declspec(dllimport) double Average(const double* Numbers, const int Count);
extern "C" _declspec(dllimport) long GreatestCommonDivisor(long Nbr1, long Nbr2);

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CMFCLibTestDlg dialog



CMFCLibTestDlg::CMFCLibTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCLIBTEST_DIALOG, pParent)
	, m_num1(0)
	, m_num2(0)
	, str_Text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCLibTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUMBER_1, m_num1);
	DDX_Text(pDX, IDC_EDIT_NUMBER_2, m_num2);
	DDX_Text(pDX, IDC_EDIT_RESULT, str_Text);
}

BEGIN_MESSAGE_MAP(CMFCLibTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE, &CMFCLibTestDlg::OnBnClickedButtonCalculate)
END_MESSAGE_MAP()


// CMFCLibTestDlg message handlers

BOOL CMFCLibTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCLibTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCLibTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCLibTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCLibTestDlg::OnBnClickedButtonCalculate()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString strTemp;
	double numbers[2];
	numbers[0] = m_num1;
	numbers[1] = m_num2;

	strTemp.Format(L"%.2f", Max(numbers, 2));
	str_Text.Append(L"Max is:\t" + strTemp);

	strTemp.Format(L"%.2f", Min(numbers, 2));
	str_Text.Append(L"\nMin is:\t" + strTemp);

	strTemp.Format(L"%.2f", Sum(numbers, 2));
	str_Text.Append(L"\nSum is:\t" + strTemp);

	strTemp.Format(L"%.2f", Average(numbers, 2));
	str_Text.Append(L"\nAverage is:\t" + strTemp);

	strTemp.Format(L"%d", GreatestCommonDivisor(m_num1, m_num2));
	str_Text.Append(L"\nGDC is:\t" + strTemp);

	UpdateData(FALSE);
}
