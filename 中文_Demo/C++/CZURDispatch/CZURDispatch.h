
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

class CZURCOM : public CCmdTarget
{
public:
	CZURCOM(void);
	~CZURCOM(void);

	//分派映射表
	DECLARE_DISPATCH_MAP()

	//定义回调函数接口，CZUR_Callback，固定名称
	HRESULT CZUR_CALLBACK(long iUploadCnt, BSTR bsrFile1, BSTR bsrFile2);

	HRESULT CZUR_UPLOAD_CALLBACK(long iUploadCnt, BSTR bsrLocalFile, long iErrorCode, BSTR bsrErrInfo);

	//定义辅助函数，CZUR_SetParams
	void    CZUR_SetParams(DWORD dwMsgId, DWORD dwMsgWnd);

private:
	DWORD m_dwMsgId;
	HWND  m_hMsgWnd;

public:
	DECLARE_DYNCREATE(CZURCOM)
	DECLARE_OLECREATE(CZURCOM)
};

class CCZURDispatchApp : public CWinApp
{
public:
	CCZURDispatchApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
