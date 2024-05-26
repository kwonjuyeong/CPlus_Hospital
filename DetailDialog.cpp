// DetailDialog.cpp : ���� �����Դϴ�.
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

//�� ���� ���� Btn
void CDetailDialog::OnBnClickedButtonSave()
{
	//���� �����͸� ������Ʈ
	GetDlgItemText(EDIT_TEXT, patientInfo.detail); 
	CHospitalAppDlg* pMainDlg = (CHospitalAppDlg*)GetParent();
	pMainDlg->UpdatePatientDetail(patientInfo);

	this->EndDialog(IDOK);
}


//���� Btn
void CDetailDialog::OnBnClickedButtonClose()
{	
	LoadAndDisplayImage( m_picCtrl, patientInfo);

	//this->EndDialog(IDCANCEL);
}
/*EVENT PART END*/
/////////////////////////////




/////////////////////////////
/* METHOD PART */

//�ʱ� �� ���� ǥ��
void CDetailDialog::SetPatientInfo(const PatientInfo& patient)
{
	patientInfo = patient;

	int year, month, day;
	swscanf_s(patient.birth, _T("%d-%d-%d"), &year, &month, &day); //patient.birth(0000-00-00) ��¥ ���Ŀ��� year, month, day �о����
	CTime p_birth(year, month, day, 0, 0, 0); // ������ CTime ��ü�� ��ȯ

	CString birthday;
	birthday.Format(_T("%s(�� %d��)"), patient.birth, CalculateAge(p_birth));

	SetDlgItemText(SUB_STATIC_TEXT, m_date + _T("�� ����"));

	//������ ǥ��
	SetDlgItemText(SUB_BIRTH, birthday);
	SetDlgItemText(SUB_VISITED, patientInfo.visited);
	SetDlgItemText(SUB_NAME, patientInfo.name);
	SetDlgItemText(SUB_GENDER, patientInfo.gender);
	SetDlgItemText(SUB_BLOOD, patientInfo.bloodType);
	SetDlgItemText(EDIT_TEXT, patientInfo.detail);

	//���� ���� ��� �ҷ�����
	SetDlgItemText(EDIT_PAST, Past_Data(patientInfo));

	
}

//������ ���
int CDetailDialog::CalculateAge(const CTime& birthDate)
{
	// ���� �ð�
	CTime currentTime = CTime::GetCurrentTime();
	int currentYear = currentTime.GetYear();
	int currentMonth = currentTime.GetMonth();
	int currentDay = currentTime.GetDay();

	// �޾ƿ� ����
	int birthYear = birthDate.GetYear();
	int birthMonth = birthDate.GetMonth();
	int birthDay = birthDate.GetDay();

	int age = currentYear - birthYear;

	//���� ��� : ���� ���������� age - 1
	if(currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)){
		age --;
	}

	return age;
}


//���� ���� ��� �ҷ�����
CString CDetailDialog::Past_Data(const PatientInfo& patient){
	CString past_data;

	CString path;
	path.Format(_T("%s/*.ini"), INS_PARA_PATH);
	CFileFind finder;
    BOOL bWorking = finder.FindFile(path);
	PatientInfo p;
       
	while (bWorking)
	{
			//���� ���� or ���� �� �����ϸ� TRUE ��ȯ
			bWorking = finder.FindNextFile();
			// ������ ��� continue
			if (finder.IsDirectory())
				continue;
        
			//��� �߰� �� ��
			//ȯ�� ����(�̸�, ����, �������, ������)�� ���� ȯ�ڿ� ��ġ�ϴ� ������ ����� ���ϸ��� ��¥ ���� �������� �ش� ���Ͽ� �ִ� ���� ����� �������� ����.
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
						else if (key == _T("�󼼱��")) {
							if (patient.name == p.name && patient.gender == p.gender && patient.birth == p.birth && patient.bloodType == p.bloodType) {
								CString formattedString;
								CString date;
								date = fileName.Left(8);
								if(value.IsEmpty()){	//����� ������, ���� ����� ���� ���
									formattedString.Format(_T("[%s ������]\r\n �����Ͼ���%s\r\n"), date, value);
									past_data += formattedString;
								}else{
									value.Replace(_T("<br>"), _T("\n"));
									formattedString.Format(_T("[%s ������]\r\n %s\r\n"), date, value); //������ ���ø����̼ǿ��� \n�� ���๮�ڷ� ��� x \r\n
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
		
		// �̹����� ǥ���� ũ�⸦ �����մϴ�.
		CRect rect;
		picCtrl.GetWindowRect(&rect);
		int width = rect.Width();
		int height = rect.Height();

		CDC* pDC = picCtrl.GetDC();
		pDC->SetStretchBltMode(COLORONCOLOR); 
		image.Draw(pDC->m_hDC, 0, 0, width, height);

		// DC�� �����մϴ�.
		picCtrl.ReleaseDC(pDC);
	}
}
/* METHOD PART END*/
/////////////////////////////





void CDetailDialog::OnBnClickedButton1()
{

	if(!pic_state){
		pic_state = TRUE;
		SetDlgItemText(BUTTON_SHOWPIC, _T("����"));


		//LoadAndDisplayImage( m_picCtrl, patientInfo);
		m_picCtrl.ShowWindow(SW_SHOW);
	}else{
		pic_state = FALSE;
		SetDlgItemText(BUTTON_SHOWPIC, _T("��������"));
		m_picCtrl.ShowWindow(SW_HIDE);
	}
}
