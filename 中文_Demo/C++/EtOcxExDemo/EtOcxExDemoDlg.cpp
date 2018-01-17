
#include "stdafx.h"
#include "EtOcxExDemo.h"
#include "EtOcxExDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WMSG_DISPATCH	(WM_USER + 0x010)

CEtOcxExDemoDlg::CEtOcxExDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEtOcxExDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEtOcxExDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ANGLE, m_wndCboAngle);
	DDX_Control(pDX, IDC_COMBO_CLRMODE, m_wndCboClrMode);
	DDX_Control(pDX, IDC_COMBO_FORMAT, m_wndCboFormat);
	DDX_Control(pDX, IDC_COMBO_IASSIST, m_wndCboAssist);
	DDX_Control(pDX, IDC_SLIDER_QUALITY, m_wndSliderQuality);
	DDX_Control(pDX, IDC_LIST_FILE, m_wndListFile);
	DDX_Control(pDX, IDC_ST, m_wndSt);
	DDX_Control(pDX, IDC_COMBO_DISPLAYGRID, m_wndCboDisplayGrid);
}

BEGIN_MESSAGE_MAP(CEtOcxExDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WMSG_DISPATCH, OnDispatch)
	ON_BN_CLICKED(IDC_BTN_CZUROPEN, &CEtOcxExDemoDlg::OnBnClickedBtnCzuropen)
	ON_BN_CLICKED(IDC_BTN_CZURCLOSE, &CEtOcxExDemoDlg::OnBnClickedBtnCzurclose)
	ON_BN_CLICKED(IDC_BTN_CZURGRAB, &CEtOcxExDemoDlg::OnBnClickedBtnCzurgrab)
	ON_BN_CLICKED(IDC_BTN_CZURRESIZE, &CEtOcxExDemoDlg::OnBnClickedBtnCzurresize)
	ON_BN_CLICKED(IDC_BTN_CZURDPI, &CEtOcxExDemoDlg::OnBnClickedBtnCzurdpi)
	ON_CBN_CLOSEUP(IDC_COMBO_ANGLE, &CEtOcxExDemoDlg::OnCbnCloseupComboAngle)
	ON_CBN_CLOSEUP(IDC_COMBO_CLRMODE, &CEtOcxExDemoDlg::OnCbnCloseupComboClrmode)
	ON_CBN_CLOSEUP(IDC_COMBO_FORMAT, &CEtOcxExDemoDlg::OnCbnCloseupComboFormat)
	ON_CBN_CLOSEUP(IDC_COMBO_IASSIST, &CEtOcxExDemoDlg::OnCbnCloseupComboIassist)
	ON_BN_CLICKED(IDC_BTN_SCAN, &CEtOcxExDemoDlg::OnBnClickedBtnScan)
	ON_BN_CLICKED(IDC_BTN_CZURPATH, &CEtOcxExDemoDlg::OnBnClickedBtnCzurpath)
	ON_BN_CLICKED(IDC_BTN_CZURCUSTOM, &CEtOcxExDemoDlg::OnBnClickedBtnCzurcustom)
	ON_WM_CLOSE()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BTN_HTTP_URL, &CEtOcxExDemoDlg::OnBnClickedBtnHttpUrl)
	ON_BN_CLICKED(IDC_BTN_HTTP_USERPWD, &CEtOcxExDemoDlg::OnBnClickedBtnHttpUserpwd)
	ON_BN_CLICKED(IDC_BTN_HTTP_FORM, &CEtOcxExDemoDlg::OnBnClickedBtnHttpForm)
	ON_CBN_CLOSEUP(IDC_COMBO_DISPLAYGRID, &CEtOcxExDemoDlg::OnCbnCloseupComboDisplaygrid)
	ON_BN_CLICKED(IDC_BTN_HTTP_UPLOAD, &CEtOcxExDemoDlg::OnBnClickedBtnHttpUpload)
END_MESSAGE_MAP()

BOOL CEtOcxExDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CoInitialize(NULL);

	static const GUID clsid = { 0x6dd8c1b7, 0x9d7, 0x49c1, { 0xbc, 0x26, 0x53, 0x3a, 0x77, 0xba, 0x76, 0x8d } };
	
	if(m_CZURDispatch.CreateDispatch(clsid))
	{
		static BYTE params[] = VTS_UI4 VTS_UI4;

		m_CZURDispatch.InvokeHelper(3, DISPATCH_METHOD, VT_EMPTY, NULL, params, WMSG_DISPATCH, m_hWnd);
	}
	else
	{
		m_CZURDispatch.m_lpDispatch = NULL;
	}

	CRect rect;
	m_wndSt.GetWindowRect(&rect);
	ScreenToClient(&rect);

	if(!m_EtOCXEx.Create(L"", WS_CHILD | WS_VISIBLE, rect, this, 6400))
	{
		MessageBox(L"Create OCX Failed");
		exit(0);
	}
	else
	{
		//��ʼ��EtOcxEx��Դ
		m_EtOCXEx.CZUR_Initialize(m_CZURDispatch.m_lpDispatch, L"VC_OCX.log");
	}

	DWORD dwStyle = m_wndListFile.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_wndListFile.SetExtendedStyle(dwStyle);

	m_wndListFile.InsertColumn(0, L"�ļ�", LVCFMT_LEFT, 300);

	m_wndSliderQuality.SetRange(0, 100);
	m_wndSliderQuality.SetPos(70);

	m_wndCboDisplayGrid.InsertString(0, L"����ʾ����");
	m_wndCboDisplayGrid.InsertString(1, L"��ʾ����");
	m_wndCboDisplayGrid.SetCurSel(0);

	m_wndCboAngle.InsertString(0, L"0��");
	m_wndCboAngle.InsertString(1, L"90��");
	m_wndCboAngle.InsertString(2, L"180��");
	m_wndCboAngle.InsertString(3, L"270��");
	m_wndCboAngle.SetCurSel(0);

	m_wndCboClrMode.InsertString(0, L"����ԭͼ");
	m_wndCboClrMode.InsertString(1, L"��ɫģʽ");
	m_wndCboClrMode.InsertString(2, L"��ֽӡ��ģʽ");
	m_wndCboClrMode.InsertString(3, L"֤������ģʽ");
	m_wndCboClrMode.InsertString(4, L"�ڰ�ģʽ");
	m_wndCboClrMode.InsertString(5, L"�Ҷ�ģʽ");
	m_wndCboClrMode.SetCurSel(0);

	m_wndCboFormat.InsertString(0, L"jpg");
	m_wndCboFormat.InsertString(1, L"bmp");
	m_wndCboFormat.SetCurSel(0);

	m_wndCboAssist.InsertString(0, L"ԭͼ������");
	m_wndCboAssist.InsertString(1, L"��ҳ�ñ�");
	m_wndCboAssist.InsertString(2, L"�鼮չƽ");
	m_wndCboAssist.InsertString(3, L"�鼮չƽ(���˫ҳ)");
	m_wndCboAssist.SetCurSel(0);

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	return TRUE;
}

LRESULT CEtOcxExDemoDlg::OnDispatch(WPARAM wParam, LPARAM lParam)
{
	WCHAR *pszFile1 = (WCHAR *)wParam;
	WCHAR *pszFile2 = (WCHAR *)lParam;

	if(pszFile1 && pszFile1[0])
	{
		m_wndListFile.InsertItem(0, pszFile1);
	}

	if(pszFile2 && pszFile2[0])
	{
		m_wndListFile.InsertItem(0, pszFile2);
	}

	return 0;
}

void CEtOcxExDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CEtOcxExDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEtOcxExDemoDlg::OnBnClickedBtnCzuropen()
{
	if(!m_EtOCXEx.CZUR_OpenDevice())
	{
		MessageBox(L"CZUR_OpenDevice() Failed");
	}
}

void CEtOcxExDemoDlg::OnBnClickedBtnCzurclose()
{
	m_EtOCXEx.CZUR_CloseDevice();
}

void CEtOcxExDemoDlg::OnBnClickedBtnCzurgrab()
{
	if(!m_EtOCXEx.CZUR_GrabSingleImage())
	{
		MessageBox(L"CZUR_GrabSingleImage() Failed");
	}
}

void CEtOcxExDemoDlg::OnBnClickedBtnCzurresize()
{
	long xResolut = GetDlgItemInt(IDC_EDIT_X);
	long yResolut = GetDlgItemInt(IDC_EDIT_Y);

	m_EtOCXEx.CZUR_Zoom(xResolut, yResolut);
}

void CEtOcxExDemoDlg::OnBnClickedBtnCzurdpi()
{
	WORD wdpi = (WORD)GetDlgItemInt(IDC_EDIT_DPI);

	m_EtOCXEx.CZUR_DPI(wdpi);
}

void CEtOcxExDemoDlg::OnCbnCloseupComboAngle()
{
	int iAngle = 0;
	switch(m_wndCboAngle.GetCurSel())
	{
	case 0:
		{
			iAngle = 0;
		}
		break;
	case 1:
		{
			iAngle = 90;
		}
		break;
	case 2:
		{
			iAngle = 180;
		}
		break;
	case 3:
		{
			iAngle = 270;
		}
		break;
	}
	m_EtOCXEx.CZUR_Rotate(iAngle);
}

void CEtOcxExDemoDlg::OnCbnCloseupComboClrmode()
{
	int iCurSel = m_wndCboClrMode.GetCurSel();
	if(-1 != iCurSel)
	{
		m_EtOCXEx.CZUR_ClrMode(iCurSel);
	}
}

void CEtOcxExDemoDlg::OnCbnCloseupComboFormat()
{
	switch(m_wndCboFormat.GetCurSel())
	{
	case 0:
		{
			m_wndSliderQuality.EnableWindow(TRUE);
			m_EtOCXEx.CZUR_Format_Jpg(m_wndSliderQuality.GetPos());
		}
		break;
	case 1:
		{
			m_EtOCXEx.CZUR_Format_Bmp();
			m_wndSliderQuality.EnableWindow(FALSE);
		}
		break;
	}
}

void CEtOcxExDemoDlg::OnCbnCloseupComboIassist()
{
	switch(m_wndCboAssist.GetCurSel())
	{
	case 0:
		{
			m_EtOCXEx.CZUR_Original();
		}
		break;
	case 1:
		{
			m_EtOCXEx.CZUR_EdgeCutting();
		}
		break;
	case 2:
		{
			m_EtOCXEx.CZUR_CurveFlatten(0);
		}
		break;
	case 3:
		{
			m_EtOCXEx.CZUR_CurveFlatten(1);
		}
		break;
	}
}

void CEtOcxExDemoDlg::OnBnClickedBtnScan()
{
	BROWSEINFO BrowseInfo = {0};

	BrowseInfo.hwndOwner = m_hWnd;
	BrowseInfo.lpszTitle = L"��ѡ�񱣴�·��";
	BrowseInfo.ulFlags   = BIF_NEWDIALOGSTYLE;

	ITEMIDLIST *pFolderList = SHBrowseForFolder(&BrowseInfo);
	if(NULL != pFolderList)
	{
		TCHAR szSavePath[1024];
		if(SHGetPathFromIDList(pFolderList, szSavePath))
		{
			//ȥ��·�������'\\'
			int nLength = lstrlen(szSavePath);
			if('\\' == szSavePath[nLength - 1])
			{
				szSavePath[nLength - 1] = NULL;
			}
			::SetDlgItemText(m_hWnd, IDC_EDIT_PATH, szSavePath);
		}
	}
}

void CEtOcxExDemoDlg::OnBnClickedBtnCzurpath()
{
	TCHAR szPath[1024];
	if(!GetDlgItemText(IDC_EDIT_PATH, szPath, 1024))
	{
		MessageBox(L"��ѡ�񱣴�Ŀ¼");
	}
	else
	{
		m_EtOCXEx.CZUR_Path(szPath);
	}
}

void CEtOcxExDemoDlg::OnBnClickedBtnCzurcustom()
{
	TCHAR szPrefix[48];
	if(!GetDlgItemText(IDC_EDIT_PREFIX, szPrefix, 48))
	{
		MessageBox(L"������ǰ׺����");
	}
	else
	{
		int iInitNumber = GetDlgItemInt(IDC_EDIT_INITNUMBER);
		m_EtOCXEx.CZUR_Custom(szPrefix, iInitNumber);
	}
}

void CEtOcxExDemoDlg::OnClose()
{
	m_EtOCXEx.CZUR_CloseDevice();
	m_EtOCXEx.CZUR_Deinitialize();

	CDialogEx::OnClose();
}

void CEtOcxExDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if(SB_ENDSCROLL == nSBCode)
	{
		long lQuality = m_wndSliderQuality.GetPos();
		m_EtOCXEx.CZUR_Format_Jpg(lQuality);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CEtOcxExDemoDlg::OnBnClickedBtnHttpUrl()
{
	TCHAR szURL[1024];
	TCHAR szFileId[128];

	if(!GetDlgItemText(IDC_EDIT_URL, szURL, 1024))
	{
		MessageBox(L"������URL");
		return;
	}

	if(!GetDlgItemText(IDC_EDIT_FILEID, szFileId, 128))
	{
		MessageBox(L"������FileId");
		return;
	}

	m_EtOCXEx.CZUR_Http_URL(szURL, szFileId);
}

void CEtOcxExDemoDlg::OnBnClickedBtnHttpUserpwd()
{
	TCHAR szUserName[1024];
	TCHAR szPassword[128];

	GetDlgItemText(IDC_EDIT_USERNAME, szUserName, 128);
	GetDlgItemText(IDC_EDIT_PWD, szPassword, 128);

	m_EtOCXEx.CZUR_Http_User_Pwd(szUserName, szPassword);
}

void CEtOcxExDemoDlg::OnBnClickedBtnHttpForm()
{
	TCHAR szName[1024];
	TCHAR szContent[128];

	GetDlgItemText(IDC_EDIT_FORMNAME, szName, 128);
	GetDlgItemText(IDC_EDIT_CONTENT, szContent, 128);

	m_EtOCXEx.CZUR_Http_Form(szName, szContent);
}

void CEtOcxExDemoDlg::OnCbnCloseupComboDisplaygrid()
{
	m_EtOCXEx.CZUR_DisplayGrid(m_wndCboDisplayGrid.GetCurSel());
}

void CEtOcxExDemoDlg::OnBnClickedBtnHttpUpload()
{
	TCHAR szLocalFile[1024];
	TCHAR szHttpUrl[1024];
	TCHAR szName[128];
	TCHAR szUserName[128];
	TCHAR szPassword[128];

	if(!GetDlgItemText(IDC_EDIT_LOCALFILE, szLocalFile, 1024))
	{
		MessageBox(L"�����뱾���ļ�", L"����");
		return;
	}

	if(!GetDlgItemText(IDC_EDIT_HTTPURL, szHttpUrl, 1024))
	{
		MessageBox(L"������URL", L"����");
		return;
	}

	if(!GetDlgItemText(IDC_EDIT_FILENAME, szName, 1024))
	{
		MessageBox(L"������FileName", L"����");
		return;
	}

	GetDlgItemText(IDC_EDIT_HTTPUSERNAME, szUserName, 128);
	GetDlgItemText(IDC_EDIT_HTTPPWD, szPassword, 128);

	switch(m_EtOCXEx.CZUR_Http_Upload(szLocalFile, szHttpUrl, szName, szUserName, szPassword))
	{
	case 1:
		{
			MessageBox(L"δ��ʼ��EtOcxEx��Դ", L"����");
		}
		break;
	case 2:
		{
			MessageBox(L"�����ļ�������", L"����");
		}
		break;
	case 3:
		{
			MessageBox(L"ʧ��", L"����");
		}
		break;
	}
}
