
// HospitalAppDlg.cpp : 구현 파일
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


// CHospitalAppDlg 대화 상자
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
	pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); //열 전체 선택 
	// 리스트 컨트롤에 제목 열 추가
	pListCtrl->InsertColumn(0, _T("순번"), LVCFMT_LEFT, 50);
	pListCtrl->InsertColumn(1, _T("방문여부"), LVCFMT_LEFT, 100);
	pListCtrl->InsertColumn(2, _T("이름"), LVCFMT_LEFT, 150);
	pListCtrl->InsertColumn(3, _T("성별"), LVCFMT_LEFT, 80);
	pListCtrl->InsertColumn(4, _T("생년월일"), LVCFMT_LEFT, 120);
	pListCtrl->InsertColumn(5, _T("혈액형"), LVCFMT_LEFT, 100);
	 

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
//환자 등록 Btn
void CHospitalAppDlg::OnBnClickedPatient()
{
	regist_Patient();
}

//파일 저장 Btn
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

//파일 불러오기 Btn
void CHospitalAppDlg::OnBnClickedEx()
{
	ini_file_reading();
}

//종료 Btn
void CHospitalAppDlg::OnBnClickedClose()
{
	AfxGetMainWnd()->PostMessage(WM_CLOSE);
}

//리스트 Double Click
void CHospitalAppDlg::OnNMDblclkPatients(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem != -1) //조건 추가 : 리스트가 비어있으면 -1을 반환함. 따라서 비어있지 않은 경우에만 실행(비어있는 리스트 더블클릭 시 강제종료 버그 수정)
	{
			
			PatientInfo patient;

			if (is_serached)
			{
				patient = search_dq[pNMItemActivate->iItem]; // 클릭한 Raw 인덱스에 해당하는 환자 정보 가져오기

			}else{
				patient = dq[pNMItemActivate->iItem]; // 클릭한 Raw 인덱스에 해당하는 환자 정보 가져오기
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
			dialog.DoModal(); // 상세페이지 모달 다이어로그 표시
	}
	*pResult = 0;
}
/*EVENT PART END*/
/////////////////////////////



/////////////////////////////
/* METHOD PART */
//리스트 업데이트
void CHospitalAppDlg::UpdateUIWithPatientList()
{
	
	// 리스트 컨트롤 초기화
	pListCtrl->DeleteAllItems();

	// 리스트에 환자 정보 추가
	int nIndex = 0;
	for (std::deque<PatientInfo>::const_iterator it = dq.begin(); it != dq.end(); ++it) {
		const PatientInfo& patient = *it; 

        CString section;
        section.Format(_T("%d"), patient.serialNumber);

        pListCtrl->InsertItem(nIndex, section); // 번호 추가
		pListCtrl->SetItemText(nIndex, 1, patient.visited); // 방문여부 추가
		pListCtrl->SetItemText(nIndex, 2, patient.name); // 이름 추가
		pListCtrl->SetItemText(nIndex, 3, patient.gender); // 성별 추가
		pListCtrl->SetItemText(nIndex, 4, patient.birth); // 생년월일 추가
		pListCtrl->SetItemText(nIndex, 5, patient.bloodType); //혈액형 추가

		nIndex++;
	}
}

//상세정보 저장
void CHospitalAppDlg::UpdatePatientDetail(const PatientInfo& patient){


	//수정방법1 : 예전 파일을 불러온 후 상세 정보를 저장하면 오늘 날짜에 기존 파일이 덮어써지는데, 상세 정보를 수정할 사람이 이미 있으면 내용을 추가해주고 수정할 사람이 없으면 오늘 날짜에 한명을 추가해줘야함.
	//수정방법2 : 불러온 날짜에 수정해주기..
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


//ini 파일 쓰기 
void CHospitalAppDlg::ini_file_writing(CString defaultPath, CString SaveDate){
	// 해당 환자 정보의 상세정보를 ini 파일에 업데이트
	CString strPath;
	strPath.Format(_T("%s\\%s 환자목록.ini"), defaultPath, SaveDate); // 파일 저장 경로 -> 현재 경로 d:\\TEST_T\\\\LOG\\20240508 환자목록.ini  => 파일명 직접 입력으로 변경?

	CStdioFile file;
	CFileException e;

	if (file.Open(strPath, CFile::modeCreate | CFile::modeWrite, &e)) {
		char* pLocale = setlocale(LC_ALL, "Korean"); // 한글 읽기/쓰기 유니코드 에러

		for (int i = 0; i < dq.size(); i++) {
			PatientInfo p = dq[i];
			CString section;
			section.Format(_T("Patient%d"), p.serialNumber);

			file.WriteString(_T("[") + section + _T("]\n"));
			file.WriteString(_T("방문여부=") + p.visited + _T("\n"));
			file.WriteString(_T("이름=") + p.name + _T("\n"));
			file.WriteString(_T("성별=") + p.gender + _T("\n"));
			file.WriteString(_T("생년월일=") + p.birth + _T("\n"));
			file.WriteString(_T("혈액형=") + p.bloodType + _T("\n"));
			file.WriteString(_T("사진파일=")+p.picPath+_T("\n"));
			CString detail = p.detail;
			detail.Replace(_T("\n"), _T("<br>")); // 개행 문자를 다른 문자열로 대체
			file.WriteString(_T("상세기록=") + detail + _T("\n\n"));
			

			//file.WriteString(_T("상세기록=") + p.detail + _T("\n\n"));
		}
		file.Close();
		MessageBox(_T("정보를 성공적으로 저장했습니다."),_T("파일 저장 완료"), MB_ICONINFORMATION);
	}
	else {
		e.ReportError();
	}
}


//ini 파일 읽기
void CHospitalAppDlg::ini_file_reading(){

	//파일 다이어로그 (ini 파일만)
	CString strFilter = _T("INI 파일 (*.ini)|*.ini|모든 파일 (*.*)|*.*||");
	//True : 열기, Default 확장자, 대화상자 초기 파일명, , 확장자필터, 대화상자 부모 윈도우
	CFileDialog dlg(TRUE, _T("ini"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter, this);

	if (dlg.DoModal() == IDOK) //열기
	{
		CStdioFile file;
		CFileException e;

		if (file.Open(dlg.GetPathName(), CFile::modeRead, &e)) {

			CString fileDate = file.GetFileName().Left(8);
			//추가 기능 : 환자 신규 등록은 오늘 날짜에만 가능
			if(fileDate != CTime::GetCurrentTime().Format(_T("%Y%m%d"))){
					GetDlgItem(BUTTON_PATIENT)->EnableWindow(FALSE);
			}else{
					GetDlgItem(BUTTON_PATIENT)->EnableWindow(TRUE);
			}

			//추가 : 제목 오늘날짜로 변경
			SetWinTitle(fileDate);


			//파일 읽기 시작
			char* pLocale = setlocale(LC_ALL, "Korean");    // 한글 읽기/쓰기 유니코드 에러 코드 추가
			dq.clear();	//dq에 불러온 데이터를 넣어주기 위해 초기화

			CString readLine;	//ReadString에서 읽어온 줄
			CString section;
			PatientInfo p;

			while (file.ReadString(readLine)) {	//한줄씩 읽기
				if (readLine.IsEmpty()) {// 빈 줄 넘기기
					continue;
				}

				if (readLine[0] == '[') {	//ini Section 부분
					// section 시작
					if (!section.IsEmpty()) {
						dq.push_back(p);
					}

					// 새로운 환자 정보 초기화
					p = PatientInfo();
					section = readLine.Mid(1, readLine.GetLength() - 1); // 대괄호 제거
					p.serialNumber = _ttoi(section.Mid(7)); // "Patient" 제거하고 숫자만 추출해 dq에 저장

				} else {	//ini key-value 부분
					int pos = readLine.Find('=');
					CString key = readLine.Left(pos);
					CString value = readLine.Mid(pos + 1);

					if (key == _T("방문여부")) {
						p.visited = value;
					} else if (key == _T("이름")) {
						p.name = value;
					} else if (key == _T("성별")) {
						p.gender = value;
					} else if (key == _T("생년월일")) {
						p.birth = value;
					}else if(key == _T("혈액형")){
						p.bloodType = value;
					}else if(key == _T("사진파일")){
						p.picPath = value;
					}
					else if (key == _T("상세기록")) {
						p.detail = value;
						p.detail.Replace(_T("<br>"), _T("\n")); // 다른 문자열을 개행 문자로 대체
					}
				}
			}

			// 마지막 환자 정보 추가
			if (!section.IsEmpty() ) {
				dq.push_back(p);
			}
			file.Close();
			// 리스트에 추가된 환자 정보를 사용하여 화면에 표시하도록 UI 업데이트 함수 호출
			UpdateUIWithPatientList();

			MessageBox(_T("불러오기 완료"),_T("파일 불러오기"), MB_ICONINFORMATION);

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


//환자 신규 등록 검사
void CHospitalAppDlg::regist_Patient(){

	//오늘 날짜 파일이 있는데, 리스트에 아이템이 없으면(새 등록 상태일 때) 신규 등록 x
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
			MessageBox(_T("금일 방문 기록이 이미 존재합니다.\n불러오기를 실행해주세요"),_T("불러오기를 실행해주세요."), MB_ICONWARNING);
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

	}else{ //리스트에 아이템이 있을 때
		registedComplete();
	}
}

//신규 환자 등록 로직
void CHospitalAppDlg::registedComplete(){
	CString name, gender, birth, bt, picpath;    // 컨트롤에서 값 받아오기
	PatientInfo p;

	/*
	//방문 기록
	if (IsDlgButtonChecked(RADIO_FVISITED)) {
		visited = "초진";
	} else if (IsDlgButtonChecked(RADIO_SVISITED)) {
		visited = "재진";
	}*/

	/*값 가져오기*/
	// 이름
	GetDlgItemText(EDIT_Name, name);
	//성별
	GetDlgItemText(COMBO_GENDER, gender);
	GetDlgItemText(EDIT_PIC, picpath);
	//혈액형
	if (IsDlgButtonChecked(RADIO_BLOOD_A)) {bt = "A";} 
	else if (IsDlgButtonChecked(RADIO_BLOOD_B)) {bt = "B";} 
	else if (IsDlgButtonChecked(RADIO_BLOOD_AB)) {bt = "AB";}
	else{bt = "O";}


	//필수 입력 값 검사
	if(name.IsEmpty()){
		MessageBox(_T("이름을 입력하지 않았습니다."),_T("입력하지 않은 데이터가 있습니다."), MB_ICONWARNING);
	}else if(gender.IsEmpty()){
		MessageBox(_T("성별을 선택해주세요."),_T("입력하지 않은 데이터가 있습니다."), MB_ICONWARNING);
	}else if(!IsDlgButtonChecked(RADIO_BLOOD_A) && !IsDlgButtonChecked(RADIO_BLOOD_B)&&!IsDlgButtonChecked(RADIO_BLOOD_AB) && !IsDlgButtonChecked(RADIO_BLOOD_O)){
		MessageBox(_T("혈액형을 선택해주세요."),_T("입력하지 않은 데이터가 있습니다."), MB_ICONWARNING);
	}else if(picpath.IsEmpty()){
		MessageBox(_T("사진을 등록해주세요."),_T("입력하지 않은 데이터가 있습니다."), MB_ICONWARNING);
	}
	else{
		// 생년월일
		CDateTimeCtrl* birthDateCtrl = (CDateTimeCtrl*)GetDlgItem(DATETIMEPICKER_BIRTH);
		CTime birthDate;
		birthDateCtrl->GetTime(birthDate);
		birth = birthDate.Format("%Y-%m-%d");

		//deque 값 추가
		p.serialNumber = dq.size() + 1; // deque의 크기 + 1을 순번으로 사용(Section)
		p.name = name;
		p.gender = gender;
		p.birth = birth;
		p.bloodType = bt;
		p.picPath = picpath;
		p.visited = VisitedBefore(p);
		dq.push_back(p);	//dq에 저장

		// 리스트 컨트롤에 항목 추가
		int nIndex = pListCtrl->GetItemCount();
		CString strSerialNumber;
		strSerialNumber.Format(_T("%d"), p.serialNumber);
		pListCtrl->InsertItem(nIndex, strSerialNumber);
		pListCtrl->SetItemText(nIndex, 1, p.visited);
		pListCtrl->SetItemText(nIndex, 2, p.name);
		pListCtrl->SetItemText(nIndex, 3, p.gender);
		pListCtrl->SetItemText(nIndex, 4, p.birth);
		pListCtrl->SetItemText(nIndex, 5, p.bloodType);

		BOOL copySuccess = CopyFile(filePath, imgPath, FALSE); // 파일 복사

		if (!copySuccess)
		{
			// 파일 복사 실패 시 메시지 표시
			MessageBox(_T("파일이 정상적으로 업로드되지 않았습니다ㅣ."), _T("에러"), MB_ICONERROR);
			return;
		}else{
			filePath = _T("");
			imgPath =  _T("");
			SetDlgItemText(EDIT_PIC, _T(""));
		}

		//등록된 후 입력한 정보 초기화
		SetDlgItemText(EDIT_Name, _T(""));
		CComboBox* pComboBox = (CComboBox*)GetDlgItem(COMBO_GENDER);
		pComboBox->SetCurSel(-1);
		CheckRadioButton(RADIO_FVISITED, RADIO_SVISITED, 0);
		CheckRadioButton(RADIO_BLOOD_A,RADIO_BLOOD_O, 0);
	}

}


//파일 불러오면 메인창 제목 변경
void CHospitalAppDlg::SetWinTitle(CString fileDate){

	CString strYear = fileDate.Left(4);
	CString strMonth = fileDate.Mid(4, 2);
	CString strDay = fileDate.Right(2);

	// 년, 월, 일을 정수형으로 변환
	int year = _ttoi(strYear);
	int month = _wtoi(strMonth);
	int day = _wtoi(strDay);	//string to int = stoi	//_ttoi -> atoi, _wtoi

	// 창 제목 설정
	CString winTitle;
	winTitle.Format(_T("%d/%02d/%02d 진료목록"), year, month, day);
	this->SetWindowText(winTitle);

}


// 추가 : 초진/재진 자동 입력
CString CHospitalAppDlg::VisitedBefore(const PatientInfo& patient){

	CString visited;
	visited = "초진";

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
				char* pLocale = setlocale(LC_ALL, "Korean");    // 한글 읽기/쓰기 유니코드 에러 코드 추가

				CString readLine;	

				while (file.ReadString(readLine)) {
					if (readLine.IsEmpty()) {
						continue;
					}
						int pos = readLine.Find('=');
						CString key = readLine.Left(pos);
						CString value = readLine.Mid(pos + 1);

						if (key == _T("이름")) {
							p.name = value;
						} else if (key == _T("성별")) {
							p.gender = value;
						} else if (key == _T("생년월일")) {
							p.birth = value;
						}else if(key == _T("혈액형")){
							p.bloodType = value;
						}

						if (patient.name == p.name && patient.gender == p.gender && patient.birth == p.birth && patient.bloodType == p.bloodType) {
							visited = "재진";
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

    // 입력한 정보 초기화
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

		if(s_category == "전체"){
			if(dq[i].name == s_text || dq[i].gender == s_text || dq[i].bloodType == s_text){
				search_dq.push_back(dq[i]);
			}
		}else{
			if(s_category == "이름"){
				if(dq[i].name == s_text){
					search_dq.push_back(dq[i]);
				}

			}else if(s_category == "성별"){

				if(dq[i].gender == s_text){
					search_dq.push_back(dq[i]);
				}


			}else if(s_category == "혈액형"){
				if(dq[i].bloodType == s_text){
					search_dq.push_back(dq[i]);
				}
			}else if(s_category == "방문여부"){
				if(dq[i].visited == s_text){
					search_dq.push_back(dq[i]);
				}
			}
		}
	}

	// 리스트 컨트롤 초기화
	pListCtrl->DeleteAllItems();

	// 리스트에 환자 정보 추가
	int nIndex = 0;
	for (std::deque<PatientInfo>::const_iterator it = search_dq.begin(); it != search_dq.end(); ++it) {
		const PatientInfo& patient = *it; 

		CString section;
		section.Format(_T("%d"), patient.serialNumber);

		pListCtrl->InsertItem(nIndex, section); // 번호 추가
		pListCtrl->SetItemText(nIndex, 1, patient.visited); // 방문여부 추가
		pListCtrl->SetItemText(nIndex, 2, patient.name); // 이름 추가
		pListCtrl->SetItemText(nIndex, 3, patient.gender); // 성별 추가
		pListCtrl->SetItemText(nIndex, 4, patient.birth); // 생년월일 추가
		pListCtrl->SetItemText(nIndex, 5, patient.bloodType); //혈액형 추가

		nIndex++;
	}
}


void CHospitalAppDlg::OnBnClickedInitSearch()
{
	is_serached = FALSE;
	SetDlgItemText(EDIT_SEARCH, NULL);
	pComboBox->SetCurSel(0);
	search_dq.clear();
	// 리스트 컨트롤 초기화
	pListCtrl->DeleteAllItems();

	// 리스트에 환자 정보 추가
	int nIndex = 0;
	for (std::deque<PatientInfo>::const_iterator it = dq.begin(); it != dq.end(); ++it) {
		const PatientInfo& patient = *it; 

		CString section;
		section.Format(_T("%d"), patient.serialNumber);

		pListCtrl->InsertItem(nIndex, section); // 번호 추가
		pListCtrl->SetItemText(nIndex, 1, patient.visited); // 방문여부 추가
		pListCtrl->SetItemText(nIndex, 2, patient.name); // 이름 추가
		pListCtrl->SetItemText(nIndex, 3, patient.gender); // 성별 추가
		pListCtrl->SetItemText(nIndex, 4, patient.birth); // 생년월일 추가
		pListCtrl->SetItemText(nIndex, 5, patient.bloodType); //혈액형 추가

		nIndex++;
	}
}

void CHospitalAppDlg::OnBnClickedPicture()
{
	CString haveName;
	GetDlgItemText(EDIT_Name, haveName);
	if (!haveName.IsEmpty())
	{
		// 파일 탐색기 열기
		CFileDialog dlg(TRUE, _T("jpg;"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("JPEG Files (*.jpg)|*.jpg"));

		if (dlg.DoModal() == IDOK)
		{
			filePath = dlg.GetPathName();
			CString extension = dlg.GetFileExt(); //확장자 가져오기

			//jpg파일이 아닐 경우
			if (extension != _T("jpg"))
			{
				MessageBox(_T("jpg 파일을 선택해주세요."), _T("jpg 파일이 아닙니다."), MB_ICONERROR);
				return;
			}

			CTime currentTime = CTime::GetCurrentTime();
			CString dateString = currentTime.Format(_T("%Y%m%d")); // 날짜 형식: YYYYMMDD
			CString name;
			GetDlgItemText(EDIT_Name, name);

			CString newFileName;
			newFileName.Format(_T("%s%s"), dateString, name);	//ex)20240322권주영

			CString tab;
			tab.Format(_T("\\"));
			// 파일을 D:\TEST_T\PICTURE 경로에 복사
			imgPath = PICTURE_PATH + tab + newFileName + _T(".") + extension;



			// EDIT_TEXT에 파일 경로 표시
			SetDlgItemText(EDIT_PIC, newFileName);
		}
	}else{
			MessageBox(_T("이름을 먼저 입력해주세요"), _T("이름이 입력되지 않았습니다."), MB_ICONERROR);
	}
	


}
