// DetailDialog.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "HospitalApp.h"
#include "DetailDialog.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CDetailDialog, CDialogEx)

	CDetailDialog::CDetailDialog(CWnd* pParent /*=nullptr*/): CDialogEx(CDetailDialog::IDD, pParent){}
	CDetailDialog::~CDetailDialog(){}
	void CDetailDialog::DoDataExchange(CDataExchange* pDX)
	{
		
		SetPatientInfo(patientInfo);
		pic_state = FALSE;

		CDialogEx::DoDataExchange(pDX);
		DDX_Control(pDX, PICTURE_PATIENT, m_picCtrl);

	}

BEGIN_MESSAGE_MAP(CDetailDialog, CDialogEx)
	ON_BN_CLICKED(SUB_BUTTON_CLOSE, &CDetailDialog::OnBnClickedButtonClose)
	ON_BN_CLICKED(SUB_BUTTON_SAVE, &CDetailDialog::OnBnClickedButtonSave)
	ON_BN_CLICKED(BUTTON_SHOWPIC, &CDetailDialog::OnBnClickedButton1)
END_MESSAGE_MAP()




/////////////////////////////
/* EVENT PART */

//상세 진료 저장 Btn
void CDetailDialog::OnBnClickedButtonSave()
{
	//진료 데이터만 업데이트
	GetDlgItemText(EDIT_TEXT, patientInfo.detail); 
	CHospitalAppDlg* pMainDlg = (CHospitalAppDlg*)GetParent();
	pMainDlg->UpdatePatientDetail(patientInfo);

	this->EndDialog(IDOK);
}


//종료 Btn
void CDetailDialog::OnBnClickedButtonClose()
{	
	LoadAndDisplayImage( m_picCtrl, patientInfo);

	//this->EndDialog(IDCANCEL);
}
/*EVENT PART END*/
/////////////////////////////




/////////////////////////////
/* METHOD PART */

//초기 상세 정보 표시
void CDetailDialog::SetPatientInfo(const PatientInfo& patient)
{
	patientInfo = patient;

	int year, month, day;
	swscanf_s(patient.birth, _T("%d-%d-%d"), &year, &month, &day); //patient.birth(0000-00-00) 날짜 형식에서 year, month, day 읽어오기
	CTime p_birth(year, month, day, 0, 0, 0); // 생일을 CTime 객체로 변환

	CString birthday;
	birthday.Format(_T("%s(만 %d세)"), patient.birth, CalculateAge(p_birth));

	SetDlgItemText(SUB_STATIC_TEXT, m_date + _T("일 진료"));

	//데이터 표시
	SetDlgItemText(SUB_BIRTH, birthday);
	SetDlgItemText(SUB_VISITED, patientInfo.visited);
	SetDlgItemText(SUB_NAME, patientInfo.name);
	SetDlgItemText(SUB_GENDER, patientInfo.gender);
	SetDlgItemText(SUB_BLOOD, patientInfo.bloodType);
	SetDlgItemText(EDIT_TEXT, patientInfo.detail);

	//과거 진료 기록 불러오기
	SetDlgItemText(EDIT_PAST, Past_Data(patientInfo));

	
}

//만나이 계산
int CDetailDialog::CalculateAge(const CTime& birthDate)
{
	// 현재 시간
	CTime currentTime = CTime::GetCurrentTime();
	int currentYear = currentTime.GetYear();
	int currentMonth = currentTime.GetMonth();
	int currentDay = currentTime.GetDay();

	// 받아온 생일
	int birthYear = birthDate.GetYear();
	int birthMonth = birthDate.GetMonth();
	int birthDay = birthDate.GetDay();

	int age = currentYear - birthYear;

	//나이 계산 : 생일 안지났으면 age - 1
	if(currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)){
		age --;
	}

	return age;
}


//과거 진료 목록 불러오기
CString CDetailDialog::Past_Data(const PatientInfo& patient){
	CString past_data;

	CString path;
	path.Format(_T("%s/*.ini"), INS_PARA_PATH);
	CFileFind finder;
    BOOL bWorking = finder.FindFile(path);
	PatientInfo p;
       
	while (bWorking)
	{
			//다음 파일 or 폴더 가 존재하면 TRUE 반환
			bWorking = finder.FindNextFile();
			// 폴더일 경우 continue
			if (finder.IsDirectory())
				continue;
        
			//기능 추가 할 것
			//환자 정보(이름, 성별, 생년월일, 혈액형)이 현재 환자와 일치하는 정보를 끌어와 파일명에서 날짜 정보 가져오고 해당 파일에 있는 진료 기록을 가져오는 로직.
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
						else if (key == _T("상세기록")) {
							if (patient.name == p.name && patient.gender == p.gender && patient.birth == p.birth && patient.bloodType == p.bloodType) {
								CString formattedString;
								CString date;
								date = fileName.Left(8);
								if(value.IsEmpty()){	//진료는 봤지만, 진료 기록이 없을 경우
									formattedString.Format(_T("[%s 진료기록]\r\n 진료기록없음%s\r\n"), date, value);
									past_data += formattedString;
								}else{
									value.Replace(_T("<br>"), _T("\n"));
									formattedString.Format(_T("[%s 진료기록]\r\n %s\r\n"), date, value); //윈도우 어플리케이션에서 \n는 개행문자로 취급 x \r\n
									past_data += formattedString;
								}
							}
						}
				}
				file.Close();

			}else{
				e.ReportError();
			}
	}
	return past_data;
}

void CDetailDialog::LoadAndDisplayImage(CStatic& picCtrl, const PatientInfo& patient) {
	CImage image;
	patientInfo = patient;
	CString path;
	path.Format(_T("%s\\%s.jpg"),PICTURE_PATH, patientInfo.picPath);

	if (image.Load(path) == S_OK) {
		
		// 이미지를 표시할 크기를 조정합니다.
		CRect rect;
		picCtrl.GetWindowRect(&rect);
		int width = rect.Width();
		int height = rect.Height();

		CDC* pDC = picCtrl.GetDC();
		pDC->SetStretchBltMode(COLORONCOLOR); 
		image.Draw(pDC->m_hDC, 0, 0, width, height);

		// DC를 해제합니다.
		picCtrl.ReleaseDC(pDC);
	}
}
/* METHOD PART END*/
/////////////////////////////





void CDetailDialog::OnBnClickedButton1()
{

	if(!pic_state){
		pic_state = TRUE;
		SetDlgItemText(BUTTON_SHOWPIC, _T("접기"));


		//LoadAndDisplayImage( m_picCtrl, patientInfo);
		m_picCtrl.ShowWindow(SW_SHOW);
	}else{
		pic_state = FALSE;
		SetDlgItemText(BUTTON_SHOWPIC, _T("사진보기"));
		m_picCtrl.ShowWindow(SW_HIDE);
	}
}
