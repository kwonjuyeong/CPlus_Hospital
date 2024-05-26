
// HospitalAppDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "HospitalApp.h"
#include "HospitalAppDlg.h"
#include "DetailDialog.h"
#include "afxdialogex.h"
#include <fstream>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{	
	//DDX_Control(pDX, SLIDER_LIST, m_slider);
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHospitalAppDlg ��ȭ ����
CHospitalAppDlg::CHospitalAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHospitalAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHospitalAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHospitalAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BUTTON_PATIENT, &CHospitalAppDlg::OnBnClickedPatient)
	ON_BN_CLICKED(BUTTON_SAVE, &CHospitalAppDlg::OnBnClickedSave)
	ON_BN_CLICKED(BUTTON_EX, &CHospitalAppDlg::OnBnClickedEx)
	ON_BN_CLICKED(BUTTON_CLOSE, &CHospitalAppDlg::OnBnClickedClose)
ON_NOTIFY(NM_DBLCLK, LIST_PATIENTS, &CHospitalAppDlg::OnNMDblclkPatients)
ON_BN_CLICKED(BUTTON_CLEAR, &CHospitalAppDlg::OnBnClickedClear)
ON_BN_CLICKED(BUTTON_SEARCH, &CHospitalAppDlg::OnBnClickedSearch)
ON_BN_CLICKED(BUTTON_INIT_SEARCH, &CHospitalAppDlg::OnBnClickedInitSearch)
ON_BN_CLICKED(BUTTON_PICTURE, &CHospitalAppDlg::OnBnClickedPicture)
END_MESSAGE_MAP()


BOOL CHospitalAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	is_serached = FALSE;
	pComboBox = (CComboBox*)GetDlgItem(COMBO_SERACH);
	pComboBox->SetCurSel(0);

	pListCtrl = (CListCtrl*)GetDlgItem(LIST_PATIENTS);
	pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); //�� ��ü ���� 
	// ����Ʈ ��Ʈ�ѿ� ���� �� �߰�
	pListCtrl->InsertColumn(0, _T("����"), LVCFMT_LEFT, 50);
	pListCtrl->InsertColumn(1, _T("�湮����"), LVCFMT_LEFT, 100);
	pListCtrl->InsertColumn(2, _T("�̸�"), LVCFMT_LEFT, 150);
	pListCtrl->InsertColumn(3, _T("����"), LVCFMT_LEFT, 80);
	pListCtrl->InsertColumn(4, _T("�������"), LVCFMT_LEFT, 120);
	pListCtrl->InsertColumn(5, _T("������"), LVCFMT_LEFT, 100);
	 

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);	

	return TRUE;
}

void CHospitalAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHospitalAppDlg::OnPaint()
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

HCURSOR CHospitalAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/////////////////////////////
/* EVENT PART */
//ȯ�� ��� Btn
void CHospitalAppDlg::OnBnClickedPatient()
{
	regist_Patient();
}

//���� ���� Btn
void CHospitalAppDlg::OnBnClickedSave()
{
	CString fileDate;
	this->GetWindowText(fileDate);
	fileDate.Remove('/');

	if(fileDate.IsEmpty() || fileDate == DEFAULT_APP_NAME){
		ini_file_writing(INS_PARA_PATH, CTime::GetCurrentTime().Format(_T("%Y%m%d")));
	}else{
		ini_file_writing(INS_PARA_PATH, fileDate.Left(8));
	}
}

//���� �ҷ����� Btn
void CHospitalAppDlg::OnBnClickedEx()
{
	ini_file_reading();
}

//���� Btn
void CHospitalAppDlg::OnBnClickedClose()
{
	AfxGetMainWnd()->PostMessage(WM_CLOSE);
}

//����Ʈ Double Click
void CHospitalAppDlg::OnNMDblclkPatients(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem != -1) //���� �߰� : ����Ʈ�� ��������� -1�� ��ȯ��. ���� ������� ���� ��쿡�� ����(����ִ� ����Ʈ ����Ŭ�� �� �������� ���� ����)
	{
			
			PatientInfo patient;

			if (is_serached)
			{
				patient = search_dq[pNMItemActivate->iItem]; // Ŭ���� Raw �ε����� �ش��ϴ� ȯ�� ���� ��������

			}else{
				patient = dq[pNMItemActivate->iItem]; // Ŭ���� Raw �ε����� �ش��ϴ� ȯ�� ���� ��������
			}
			

			CString fileDate;
			this->GetWindowText(fileDate);

			CDetailDialog dialog;
			dialog.patientInfo = patient;
			if(fileDate.IsEmpty() || fileDate == DEFAULT_APP_NAME){
				dialog.m_date = CTime::GetCurrentTime().Format(_T("%Y/%m/%d"));
			}else{
				dialog.m_date =  fileDate.Left(10);
			}
			dialog.DoModal(); // �������� ��� ���̾�α� ǥ��
	}
	*pResult = 0;
}
/*EVENT PART END*/
/////////////////////////////



/////////////////////////////
/* METHOD PART */
//����Ʈ ������Ʈ
void CHospitalAppDlg::UpdateUIWithPatientList()
{
	
	// ����Ʈ ��Ʈ�� �ʱ�ȭ
	pListCtrl->DeleteAllItems();

	// ����Ʈ�� ȯ�� ���� �߰�
	int nIndex = 0;
	for (std::deque<PatientInfo>::const_iterator it = dq.begin(); it != dq.end(); ++it) {
		const PatientInfo& patient = *it; 

        CString section;
        section.Format(_T("%d"), patient.serialNumber);

        pListCtrl->InsertItem(nIndex, section); // ��ȣ �߰�
		pListCtrl->SetItemText(nIndex, 1, patient.visited); // �湮���� �߰�
		pListCtrl->SetItemText(nIndex, 2, patient.name); // �̸� �߰�
		pListCtrl->SetItemText(nIndex, 3, patient.gender); // ���� �߰�
		pListCtrl->SetItemText(nIndex, 4, patient.birth); // ������� �߰�
		pListCtrl->SetItemText(nIndex, 5, patient.bloodType); //������ �߰�

		nIndex++;
	}
}

//������ ����
void CHospitalAppDlg::UpdatePatientDetail(const PatientInfo& patient){


	//�������1 : ���� ������ �ҷ��� �� �� ������ �����ϸ� ���� ��¥�� ���� ������ ��������µ�, �� ������ ������ ����� �̹� ������ ������ �߰����ְ� ������ ����� ������ ���� ��¥�� �Ѹ��� �߰��������.
	//�������2 : �ҷ��� ��¥�� �������ֱ�..
	for (std::deque<PatientInfo>::iterator it = dq.begin(); it != dq.end(); ++it) {
		if (it->serialNumber == patient.serialNumber) {
			it->detail = patient.detail;

			CString fileDate;
			this->GetWindowText(fileDate);
			fileDate.Remove('/');

			if(fileDate.IsEmpty() || fileDate == DEFAULT_APP_NAME){
				ini_file_writing(INS_PARA_PATH, CTime::GetCurrentTime().Format(_T("%Y%m%d")));
			}else{
				ini_file_writing(INS_PARA_PATH, fileDate.Left(8));
			}
			break;
		}
	}

	CHospitalAppDlg::OnBnClickedInitSearch();
}


//ini ���� ���� 
void CHospitalAppDlg::ini_file_writing(CString defaultPath, CString SaveDate){
	// �ش� ȯ�� ������ �������� ini ���Ͽ� ������Ʈ
	CString strPath;
	strPath.Format(_T("%s\\%s ȯ�ڸ��.ini"), defaultPath, SaveDate); // ���� ���� ��� -> ���� ��� d:\\TEST_T\\\\LOG\\20240508 ȯ�ڸ��.ini  => ���ϸ� ���� �Է����� ����?

	CStdioFile file;
	CFileException e;

	if (file.Open(strPath, CFile::modeCreate | CFile::modeWrite, &e)) {
		char* pLocale = setlocale(LC_ALL, "Korean"); // �ѱ� �б�/���� �����ڵ� ����

		for (int i = 0; i < dq.size(); i++) {
			PatientInfo p = dq[i];
			CString section;
			section.Format(_T("Patient%d"), p.serialNumber);

			file.WriteString(_T("[") + section + _T("]\n"));
			file.WriteString(_T("�湮����=") + p.visited + _T("\n"));
			file.WriteString(_T("�̸�=") + p.name + _T("\n"));
			file.WriteString(_T("����=") + p.gender + _T("\n"));
			file.WriteString(_T("�������=") + p.birth + _T("\n"));
			file.WriteString(_T("������=") + p.bloodType + _T("\n"));
			file.WriteString(_T("��������=")+p.picPath+_T("\n"));
			CString detail = p.detail;
			detail.Replace(_T("\n"), _T("<br>")); // ���� ���ڸ� �ٸ� ���ڿ��� ��ü
			file.WriteString(_T("�󼼱��=") + detail + _T("\n\n"));
			

			//file.WriteString(_T("�󼼱��=") + p.detail + _T("\n\n"));
		}
		file.Close();
		MessageBox(_T("������ ���������� �����߽��ϴ�."),_T("���� ���� �Ϸ�"), MB_ICONINFORMATION);
	}
	else {
		e.ReportError();
	}
}


//ini ���� �б�
void CHospitalAppDlg::ini_file_reading(){

	//���� ���̾�α� (ini ���ϸ�)
	CString strFilter = _T("INI ���� (*.ini)|*.ini|��� ���� (*.*)|*.*||");
	//True : ����, Default Ȯ����, ��ȭ���� �ʱ� ���ϸ�, , Ȯ��������, ��ȭ���� �θ� ������
	CFileDialog dlg(TRUE, _T("ini"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter, this);

	if (dlg.DoModal() == IDOK) //����
	{
		CStdioFile file;
		CFileException e;

		if (file.Open(dlg.GetPathName(), CFile::modeRead, &e)) {

			CString fileDate = file.GetFileName().Left(8);
			//�߰� ��� : ȯ�� �ű� ����� ���� ��¥���� ����
			if(fileDate != CTime::GetCurrentTime().Format(_T("%Y%m%d"))){
					GetDlgItem(BUTTON_PATIENT)->EnableWindow(FALSE);
			}else{
					GetDlgItem(BUTTON_PATIENT)->EnableWindow(TRUE);
			}

			//�߰� : ���� ���ó�¥�� ����
			SetWinTitle(fileDate);


			//���� �б� ����
			char* pLocale = setlocale(LC_ALL, "Korean");    // �ѱ� �б�/���� �����ڵ� ���� �ڵ� �߰�
			dq.clear();	//dq�� �ҷ��� �����͸� �־��ֱ� ���� �ʱ�ȭ

			CString readLine;	//ReadString���� �о�� ��
			CString section;
			PatientInfo p;

			while (file.ReadString(readLine)) {	//���پ� �б�
				if (readLine.IsEmpty()) {// �� �� �ѱ��
					continue;
				}

				if (readLine[0] == '[') {	//ini Section �κ�
					// section ����
					if (!section.IsEmpty()) {
						dq.push_back(p);
					}

					// ���ο� ȯ�� ���� �ʱ�ȭ
					p = PatientInfo();
					section = readLine.Mid(1, readLine.GetLength() - 1); // ���ȣ ����
					p.serialNumber = _ttoi(section.Mid(7)); // "Patient" �����ϰ� ���ڸ� ������ dq�� ����

				} else {	//ini key-value �κ�
					int pos = readLine.Find('=');
					CString key = readLine.Left(pos);
					CString value = readLine.Mid(pos + 1);

					if (key == _T("�湮����")) {
						p.visited = value;
					} else if (key == _T("�̸�")) {
						p.name = value;
					} else if (key == _T("����")) {
						p.gender = value;
					} else if (key == _T("�������")) {
						p.birth = value;
					}else if(key == _T("������")){
						p.bloodType = value;
					}else if(key == _T("��������")){
						p.picPath = value;
					}
					else if (key == _T("�󼼱��")) {
						p.detail = value;
						p.detail.Replace(_T("<br>"), _T("\n")); // �ٸ� ���ڿ��� ���� ���ڷ� ��ü
					}
				}
			}

			// ������ ȯ�� ���� �߰�
			if (!section.IsEmpty() ) {
				dq.push_back(p);
			}
			file.Close();
			// ����Ʈ�� �߰��� ȯ�� ������ ����Ͽ� ȭ�鿡 ǥ���ϵ��� UI ������Ʈ �Լ� ȣ��
			UpdateUIWithPatientList();

			MessageBox(_T("�ҷ����� �Ϸ�"),_T("���� �ҷ�����"), MB_ICONINFORMATION);

		}else{
			e.ReportError();
		}
	}
	is_serached = FALSE;
	SetDlgItemText(EDIT_SEARCH, NULL);
	pComboBox->SetCurSel(0);
	search_dq.clear();
	filePath = _T("");
	imgPath =  _T("");
	SetDlgItemText(EDIT_PIC, _T(""));
}


//ȯ�� �ű� ��� �˻�
void CHospitalAppDlg::regist_Patient(){

	//���� ��¥ ������ �ִµ�, ����Ʈ�� �������� ������(�� ��� ������ ��) �ű� ��� x
	if(dq.size() == 0){
		CString path;
		path.Format(_T("%s/*.ini"), INS_PARA_PATH);
		CFileFind finder;
		BOOL bWorking = finder.FindFile(path);
		BOOL is_duplicate_file = FALSE;

		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (finder.IsDirectory())
				continue;
			CString fileName = finder.GetFileName();
			if(CTime::GetCurrentTime().Format(_T("%Y%m%d")) == fileName.Left(8)){
				is_duplicate_file = TRUE;
				break;
			}
		}

		if (is_duplicate_file){
			MessageBox(_T("���� �湮 ����� �̹� �����մϴ�.\n�ҷ����⸦ �������ּ���"),_T("�ҷ����⸦ �������ּ���."), MB_ICONWARNING);
			SetDlgItemText(EDIT_Name, _T(""));
			CComboBox* pComboBox = (CComboBox*)GetDlgItem(COMBO_GENDER);
			pComboBox->SetCurSel(-1);
			CheckRadioButton(RADIO_FVISITED, RADIO_SVISITED, 0);
			CheckRadioButton(RADIO_BLOOD_A,RADIO_BLOOD_O, 0);
			filePath = _T("");
			imgPath =  _T("");
			SetDlgItemText(EDIT_PIC, _T(""));
		}else{
			registedComplete();
		}

	}else{ //����Ʈ�� �������� ���� ��
		registedComplete();
	}
}

//�ű� ȯ�� ��� ����
void CHospitalAppDlg::registedComplete(){
	CString name, gender, birth, bt, picpath;    // ��Ʈ�ѿ��� �� �޾ƿ���
	PatientInfo p;

	/*
	//�湮 ���
	if (IsDlgButtonChecked(RADIO_FVISITED)) {
		visited = "����";
	} else if (IsDlgButtonChecked(RADIO_SVISITED)) {
		visited = "����";
	}*/

	/*�� ��������*/
	// �̸�
	GetDlgItemText(EDIT_Name, name);
	//����
	GetDlgItemText(COMBO_GENDER, gender);
	GetDlgItemText(EDIT_PIC, picpath);
	//������
	if (IsDlgButtonChecked(RADIO_BLOOD_A)) {bt = "A";} 
	else if (IsDlgButtonChecked(RADIO_BLOOD_B)) {bt = "B";} 
	else if (IsDlgButtonChecked(RADIO_BLOOD_AB)) {bt = "AB";}
	else{bt = "O";}


	//�ʼ� �Է� �� �˻�
	if(name.IsEmpty()){
		MessageBox(_T("�̸��� �Է����� �ʾҽ��ϴ�."),_T("�Է����� ���� �����Ͱ� �ֽ��ϴ�."), MB_ICONWARNING);
	}else if(gender.IsEmpty()){
		MessageBox(_T("������ �������ּ���."),_T("�Է����� ���� �����Ͱ� �ֽ��ϴ�."), MB_ICONWARNING);
	}else if(!IsDlgButtonChecked(RADIO_BLOOD_A) && !IsDlgButtonChecked(RADIO_BLOOD_B)&&!IsDlgButtonChecked(RADIO_BLOOD_AB) && !IsDlgButtonChecked(RADIO_BLOOD_O)){
		MessageBox(_T("�������� �������ּ���."),_T("�Է����� ���� �����Ͱ� �ֽ��ϴ�."), MB_ICONWARNING);
	}else if(picpath.IsEmpty()){
		MessageBox(_T("������ ������ּ���."),_T("�Է����� ���� �����Ͱ� �ֽ��ϴ�."), MB_ICONWARNING);
	}
	else{
		// �������
		CDateTimeCtrl* birthDateCtrl = (CDateTimeCtrl*)GetDlgItem(DATETIMEPICKER_BIRTH);
		CTime birthDate;
		birthDateCtrl->GetTime(birthDate);
		birth = birthDate.Format("%Y-%m-%d");

		//deque �� �߰�
		p.serialNumber = dq.size() + 1; // deque�� ũ�� + 1�� �������� ���(Section)
		p.name = name;
		p.gender = gender;
		p.birth = birth;
		p.bloodType = bt;
		p.picPath = picpath;
		p.visited = VisitedBefore(p);
		dq.push_back(p);	//dq�� ����

		// ����Ʈ ��Ʈ�ѿ� �׸� �߰�
		int nIndex = pListCtrl->GetItemCount();
		CString strSerialNumber;
		strSerialNumber.Format(_T("%d"), p.serialNumber);
		pListCtrl->InsertItem(nIndex, strSerialNumber);
		pListCtrl->SetItemText(nIndex, 1, p.visited);
		pListCtrl->SetItemText(nIndex, 2, p.name);
		pListCtrl->SetItemText(nIndex, 3, p.gender);
		pListCtrl->SetItemText(nIndex, 4, p.birth);
		pListCtrl->SetItemText(nIndex, 5, p.bloodType);

		BOOL copySuccess = CopyFile(filePath, imgPath, FALSE); // ���� ����

		if (!copySuccess)
		{
			// ���� ���� ���� �� �޽��� ǥ��
			MessageBox(_T("������ ���������� ���ε���� �ʾҽ��ϴ٤�."), _T("����"), MB_ICONERROR);
			return;
		}else{
			filePath = _T("");
			imgPath =  _T("");
			SetDlgItemText(EDIT_PIC, _T(""));
		}

		//��ϵ� �� �Է��� ���� �ʱ�ȭ
		SetDlgItemText(EDIT_Name, _T(""));
		CComboBox* pComboBox = (CComboBox*)GetDlgItem(COMBO_GENDER);
		pComboBox->SetCurSel(-1);
		CheckRadioButton(RADIO_FVISITED, RADIO_SVISITED, 0);
		CheckRadioButton(RADIO_BLOOD_A,RADIO_BLOOD_O, 0);
	}

}


//���� �ҷ����� ����â ���� ����
void CHospitalAppDlg::SetWinTitle(CString fileDate){

	CString strYear = fileDate.Left(4);
	CString strMonth = fileDate.Mid(4, 2);
	CString strDay = fileDate.Right(2);

	// ��, ��, ���� ���������� ��ȯ
	int year = _ttoi(strYear);
	int month = _wtoi(strMonth);
	int day = _wtoi(strDay);	//string to int = stoi	//_ttoi -> atoi, _wtoi

	// â ���� ����
	CString winTitle;
	winTitle.Format(_T("%d/%02d/%02d ������"), year, month, day);
	this->SetWindowText(winTitle);

}


// �߰� : ����/���� �ڵ� �Է�
CString CHospitalAppDlg::VisitedBefore(const PatientInfo& patient){

	CString visited;
	visited = "����";

	CString path;
	path.Format(_T("%s/*.ini"), INS_PARA_PATH);
	CFileFind finder;
    BOOL bWorking = finder.FindFile(path);
	PatientInfo p;
       
	while (bWorking)
	{
			bWorking = finder.FindNextFile();
			if (finder.IsDirectory())
				continue;
        
			CString fileName = finder.GetFileName();
			CString newpath;
			newpath.Format(_T("%s/%s"), INS_PARA_PATH, fileName);

			CStdioFile file;
			CFileException e;

			if (file.Open(newpath, CFile::modeRead, &e)) {
				char* pLocale = setlocale(LC_ALL, "Korean");    // �ѱ� �б�/���� �����ڵ� ���� �ڵ� �߰�

				CString readLine;	

				while (file.ReadString(readLine)) {
					if (readLine.IsEmpty()) {
						continue;
					}
						int pos = readLine.Find('=');
						CString key = readLine.Left(pos);
						CString value = readLine.Mid(pos + 1);

						if (key == _T("�̸�")) {
							p.name = value;
						} else if (key == _T("����")) {
							p.gender = value;
						} else if (key == _T("�������")) {
							p.birth = value;
						}else if(key == _T("������")){
							p.bloodType = value;
						}

						if (patient.name == p.name && patient.gender == p.gender && patient.birth == p.birth && patient.bloodType == p.bloodType) {
							visited = "����";
						}
						
				}
				file.Close();

			}else{
				e.ReportError();
			}
	}
	return visited;
}
/* METHOD PART END*/
/////////////////////////////



void CHospitalAppDlg::OnBnClickedClear()
{
    CString title;
    title.Format(DEFAULT_APP_NAME);

    dq.clear();
    pListCtrl->DeleteAllItems();
    this->SetWindowText(title); 

    // �Է��� ���� �ʱ�ȭ
    SetDlgItemText(EDIT_Name, _T(""));
    CComboBox* pComboBox = (CComboBox*)GetDlgItem(COMBO_GENDER);
    pComboBox->SetCurSel(-1);
    CheckRadioButton(RADIO_FVISITED, RADIO_SVISITED, 0);
    CheckRadioButton(RADIO_BLOOD_A, RADIO_BLOOD_O, 0);
    GetDlgItem(BUTTON_PATIENT)->EnableWindow(TRUE);
}

void CHospitalAppDlg::OnBnClickedSearch()
{
	CString s_category, s_text;
	GetDlgItemText(COMBO_SERACH, s_category);
	GetDlgItemText(EDIT_SEARCH, s_text);

	search_dq.clear();
	is_serached = TRUE;
	
	for(int i = 0; i < dq.size(); i++){

		if(s_category == "��ü"){
			if(dq[i].name == s_text || dq[i].gender == s_text || dq[i].bloodType == s_text){
				search_dq.push_back(dq[i]);
			}
		}else{
			if(s_category == "�̸�"){
				if(dq[i].name == s_text){
					search_dq.push_back(dq[i]);
				}

			}else if(s_category == "����"){

				if(dq[i].gender == s_text){
					search_dq.push_back(dq[i]);
				}


			}else if(s_category == "������"){
				if(dq[i].bloodType == s_text){
					search_dq.push_back(dq[i]);
				}
			}else if(s_category == "�湮����"){
				if(dq[i].visited == s_text){
					search_dq.push_back(dq[i]);
				}
			}
		}
	}

	// ����Ʈ ��Ʈ�� �ʱ�ȭ
	pListCtrl->DeleteAllItems();

	// ����Ʈ�� ȯ�� ���� �߰�
	int nIndex = 0;
	for (std::deque<PatientInfo>::const_iterator it = search_dq.begin(); it != search_dq.end(); ++it) {
		const PatientInfo& patient = *it; 

		CString section;
		section.Format(_T("%d"), patient.serialNumber);

		pListCtrl->InsertItem(nIndex, section); // ��ȣ �߰�
		pListCtrl->SetItemText(nIndex, 1, patient.visited); // �湮���� �߰�
		pListCtrl->SetItemText(nIndex, 2, patient.name); // �̸� �߰�
		pListCtrl->SetItemText(nIndex, 3, patient.gender); // ���� �߰�
		pListCtrl->SetItemText(nIndex, 4, patient.birth); // ������� �߰�
		pListCtrl->SetItemText(nIndex, 5, patient.bloodType); //������ �߰�

		nIndex++;
	}
}


void CHospitalAppDlg::OnBnClickedInitSearch()
{
	is_serached = FALSE;
	SetDlgItemText(EDIT_SEARCH, NULL);
	pComboBox->SetCurSel(0);
	search_dq.clear();
	// ����Ʈ ��Ʈ�� �ʱ�ȭ
	pListCtrl->DeleteAllItems();

	// ����Ʈ�� ȯ�� ���� �߰�
	int nIndex = 0;
	for (std::deque<PatientInfo>::const_iterator it = dq.begin(); it != dq.end(); ++it) {
		const PatientInfo& patient = *it; 

		CString section;
		section.Format(_T("%d"), patient.serialNumber);

		pListCtrl->InsertItem(nIndex, section); // ��ȣ �߰�
		pListCtrl->SetItemText(nIndex, 1, patient.visited); // �湮���� �߰�
		pListCtrl->SetItemText(nIndex, 2, patient.name); // �̸� �߰�
		pListCtrl->SetItemText(nIndex, 3, patient.gender); // ���� �߰�
		pListCtrl->SetItemText(nIndex, 4, patient.birth); // ������� �߰�
		pListCtrl->SetItemText(nIndex, 5, patient.bloodType); //������ �߰�

		nIndex++;
	}
}

void CHospitalAppDlg::OnBnClickedPicture()
{
	CString haveName;
	GetDlgItemText(EDIT_Name, haveName);
	if (!haveName.IsEmpty())
	{
		// ���� Ž���� ����
		CFileDialog dlg(TRUE, _T("jpg;"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("JPEG Files (*.jpg)|*.jpg"));

		if (dlg.DoModal() == IDOK)
		{
			filePath = dlg.GetPathName();
			CString extension = dlg.GetFileExt(); //Ȯ���� ��������

			//jpg������ �ƴ� ���
			if (extension != _T("jpg"))
			{
				MessageBox(_T("jpg ������ �������ּ���."), _T("jpg ������ �ƴմϴ�."), MB_ICONERROR);
				return;
			}

			CTime currentTime = CTime::GetCurrentTime();
			CString dateString = currentTime.Format(_T("%Y%m%d")); // ��¥ ����: YYYYMMDD
			CString name;
			GetDlgItemText(EDIT_Name, name);

			CString newFileName;
			newFileName.Format(_T("%s%s"), dateString, name);	//ex)20240322���ֿ�

			CString tab;
			tab.Format(_T("\\"));
			// ������ D:\TEST_T\PICTURE ��ο� ����
			imgPath = PICTURE_PATH + tab + newFileName + _T(".") + extension;



			// EDIT_TEXT�� ���� ��� ǥ��
			SetDlgItemText(EDIT_PIC, newFileName);
		}
	}else{
			MessageBox(_T("�̸��� ���� �Է����ּ���"), _T("�̸��� �Էµ��� �ʾҽ��ϴ�."), MB_ICONERROR);
	}
	


}
