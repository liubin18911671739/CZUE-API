
#include "stdafx.h"
#include "CZURDispatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//分配映射表
BEGIN_DISPATCH_MAP(CZURCOM, CCmdTarget)
	DISP_FUNCTION_ID(CZURCOM, "CZUR_CALLBACK", 1, CZUR_CALLBACK, VT_I4, VTS_I4 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CZURCOM, "CZUR_UPLOAD_CALLBACK", 2, CZUR_UPLOAD_CALLBACK, VT_I4, VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CZURCOM, "CZUR_SetParams", 3, CZUR_SetParams, VT_EMPTY, VTS_UI4 VTS_UI4)
END_DISPATCH_MAP()

//工厂对象
IMPLEMENT_DYNCREATE(CZURCOM, CCmdTarget)

IMPLEMENT_OLECREATE(CZURCOM, "CZUR_Callback.Object", 0x6dd8c1b7, 0x9d7, 0x49c1, 0xbc, 0x26, 0x53, 0x3a, 0x77, 0xba, 0x76, 0x8d);


CZURCOM::CZURCOM(void)
{
	m_hMsgWnd = NULL;
	m_dwMsgId = 0;
	EnableAutomation();
}

CZURCOM::~CZURCOM(void)
{
}

HRESULT CZURCOM::CZUR_CALLBACK(long iUploadCnt, BSTR bsrFile1, BSTR bsrFile2)
{
	char szMsg[128];
	sprintf_s(szMsg, 128, "上传文件个数: %d\n", iUploadCnt);
	MessageBoxA(NULL, szMsg, "", MB_OK);

	SendMessage(m_hMsgWnd, m_dwMsgId, (WPARAM)bsrFile1, (LPARAM)bsrFile2);
	
	return S_OK;
}

HRESULT CZURCOM::CZUR_UPLOAD_CALLBACK(long iUploadCnt, BSTR bsrLocalFile, long iErrorCode, BSTR bsrErrInfo)
{
	if(1 == iUploadCnt)
	{
		MessageBox(m_hMsgWnd, L"上传成功", L"提示", MB_OK);
	}
	else
	{
		TCHAR szMsgInfo[4096];
		_stprintf_s(szMsgInfo, 4096, L"本地文件：%s上传失败\n错误码：%d\n错误信息：%s", bsrLocalFile, iErrorCode, bsrErrInfo);
		MessageBox(m_hMsgWnd, szMsgInfo, L"提示", MB_OK);
	}
	return S_OK;
}

void CZURCOM::CZUR_SetParams(DWORD dwMsgId, DWORD dwMsgWnd)
{
	m_dwMsgId = dwMsgId;
	m_hMsgWnd = (HWND)dwMsgWnd;
}


BEGIN_MESSAGE_MAP(CCZURDispatchApp, CWinApp)
END_MESSAGE_MAP()

CCZURDispatchApp::CCZURDispatchApp()
{
}


CCZURDispatchApp theApp;

const GUID CDECL _tlid = { 0x1EE05F27, 0xDBA, 0x4343, { 0xBE, 0xA8, 0x6B, 0x6E, 0x5F, 0x30, 0x9F, 0x71 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


BOOL CCZURDispatchApp::InitInstance()
{
	CWinApp::InitInstance();

	COleObjectFactory::RegisterAll();

	return TRUE;
}

// DllGetClassObject - 返回类工厂
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
}

// DllCanUnloadNow - 允许 COM 卸载 DLL
STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
}

// DllRegisterServer - 将项添加到系统注册表
STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll())
		return SELFREG_E_CLASS;

	return S_OK;
}

// DllUnregisterServer - 将项从系统注册表中移除
STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll(FALSE))
		return SELFREG_E_CLASS;

	return S_OK;
}