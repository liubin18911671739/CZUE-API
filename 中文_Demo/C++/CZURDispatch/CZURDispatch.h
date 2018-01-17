
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

class CZURCOM : public CCmdTarget
{
public:
	CZURCOM(void);
	~CZURCOM(void);

	//����ӳ���
	DECLARE_DISPATCH_MAP()

	//����ص������ӿڣ�CZUR_Callback���̶�����
	HRESULT CZUR_CALLBACK(long iUploadCnt, BSTR bsrFile1, BSTR bsrFile2);

	HRESULT CZUR_UPLOAD_CALLBACK(long iUploadCnt, BSTR bsrLocalFile, long iErrorCode, BSTR bsrErrInfo);

	//���帨��������CZUR_SetParams
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
