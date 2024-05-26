
// HospitalAppDlg.h : 헤더 파일
//

#pragma once

#include <deque> // std::deque을 사용하기 위해 추가
#include <map>
#include <string>

struct PatientInfo {
	int serialNumber;
	CString visited;
	CString name;
	CString gender;
	CString birth;
	CString bloodType;
	CString detail;
	CString picPath;
};

class CHospitalAppDlg : public CDialogEx
{
public:
	CHospitalAppDlg(CWnd* pParent = NULL);
	enum { IDD = IDD_HOSPITALAPP_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	std::deque<PatientInfo> dq; // 값 저장할 deque 멤버 변수
	std::deque<PatientInfo> search_dq;
public:
	afx_msg void OnBnClickedPatient();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedEx();
	afx_msg void OnBnClickedClose();
	void UpdateUIWithPatientList();
	afx_msg void OnNMDblclkPatients(NMHDR *pNMHDR, LRESULT *pResult);
	void UpdatePatientDetail(const PatientInfo& patient);
	void ini_file_writing(CString defaultPath, CString SaveDate);
	void ini_file_reading();
	void regist_Patient();
	void registedComplete();
	void SetWinTitle(CString fileDate);
	CString VisitedBefore(const PatientInfo& patient);

	CListCtrl* pListCtrl;
	CComboBox* pComboBox;
	BOOL is_serached;
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedInitSearch();
	afx_msg void OnBnClickedPicture();
	CString filePath;
	CString imgPath;
};
