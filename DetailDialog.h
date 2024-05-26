
// DetailDialog.h : 헤더 파일
//

#pragma once

#include "resource.h"
#include "HospitalAppDlg.h"
#include "afxwin.h"

class CDetailDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDetailDialog)

public:
	CDetailDialog(CWnd* pParent = NULL);
	virtual ~CDetailDialog();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_PATIENT_DETAILS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	void SetPatientInfo(const PatientInfo& patient);
	CString CDetailDialog::Past_Data(const PatientInfo& patient);
	int CalculateAge(const CTime& birthDate);
private:
	DECLARE_MESSAGE_MAP()
public:
	PatientInfo patientInfo;
	CString m_date;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonClose();
	void CDetailDialog::LoadAndDisplayImage(CStatic& picCtrl, const PatientInfo& patient);

	CStatic m_picCtrl;
	afx_msg void OnStnClickedPatient();
	afx_msg void OnBnClickedButton1();
	BOOL pic_state;
};