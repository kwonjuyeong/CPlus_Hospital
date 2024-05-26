
// HospitalApp.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "HospitalApp.h"
#include "HospitalAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHospitalAppApp

BEGIN_MESSAGE_MAP(CHospitalAppApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CHospitalAppApp ����

CHospitalAppApp::CHospitalAppApp()
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}


// ������ CHospitalAppApp ��ü�Դϴ�.
CHospitalAppApp theApp;


// CHospitalAppApp �ʱ�ȭ

BOOL CHospitalAppApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	CShellManager *pShellManager = new CShellManager;

	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	CHospitalAppDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{

	}
	else if (nResponse == IDCANCEL)
	{

	}

	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	return FALSE;
}

