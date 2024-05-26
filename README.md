================================================================================
    MFC 라이브러리 : HospitalApp 프로젝트 개요
================================================================================

응용 프로그램 마법사에서 이 HospitalApp 응용 프로그램을 
만들었습니다. 이 응용 프로그램은 MFC의 기본 사용법을 보여 줄 뿐만 아니라 응용 
프로그램작성을 위한 기본 구조를 제공합니다.

이 파일에는 HospitalApp 응용 프로그램을 구성하는 각 파일에 대한
요약 설명이 포함되어 있습니다.

HospitalApp.vcxproj
    응용 프로그램 마법사를 사용하여 생성된 VC++ 프로젝트의 주 프로젝트 파일입니다. 
    파일을 생성한 Visual C++ 버전에 대한 정보와 응용 프로그램 마법사를 사용하여 선택한 
    플랫폼, 구성 및 프로젝트 기능에 대한 정보가 들어 있습니다.

HospitalApp.vcxproj.filters
    응용 프로그램 마법사를 사용하여 생성된 VC++ 프로젝트의 필터 파일입니다. 
    이 파일에는 프로젝트의 파일과 필터 간의 연결 정보가 들어 있습니다. 이러한 
    연결은 특정 노드에서 유사한 확장명으로 그룹화된 파일을 표시하기 위해 
    IDE에서 사용됩니다. 예를 들어 ".cpp" 파일은 "소스 파일" 필터와 연결되어 
    있습니다.


HospitalApp.h
    응용 프로그램의 기본 헤더 파일입니다. 여기에는 다른 프로젝트 관련
    헤더(Resource.h 포함)가 들어 있고 CHospitalAppApp 응용 프로그램
    클래스를 선언합니다.

HospitalApp.cpp
    응용 프로그램 클래스 CHospitalAppApp이(가) 들어 있는 기본 응용 프로그램
    소스 파일입니다.

HospitalApp.rc
    프로그램에서 사용하는 모든 Microsoft Windows 리소스의 목록입니다.
 여기에는 RES 하위 디렉터리에 저장된 아이콘, 비트맵 및 커서가
    포함됩니다. 이 파일은 Microsoft Visual C++에서 직접
    편집할 수 있습니다. 프로젝트 리소스는 1042에 있습니다.

res\HospitalApp.ico
    응용 프로그램의 아이콘으로 사용되는 아이콘 파일입니다. 이 아이콘은
    주 리소스 파일인 HospitalApp.rc에 의해 포함됩니다.

res\HospitalApp.rc2
    이 파일에는 Microsoft Visual C++ 이외의 다른 도구에서 편집한 리소스가 
    들어 있습니다. 리소스 편집기로 편집할 수 없는 모든 리소스는
    이 파일에 넣어야 합니다.


/////////////////////////////////////////////////////////////////////////////

응용 프로그램 마법사에서 하나의 대화 상자 클래스가 만들어집니다.

HospitalAppDlg.h, HospitalAppDlg.cpp - 대화 상자
    이 파일에는 CHospitalAppDlg 클래스가 들어 있습니다. 이 클래스는
    응용 프로그램의 주 대화 상자 동작을 정의합니다. 대화 상자의 템플릿은
    Microsoft Visual C++에서 편집할 수 있는 HospitalApp.rc에 있습니다.


/////////////////////////////////////////////////////////////////////////////

기타 기능:

ActiveX 컨트롤
    응용 프로그램에서 ActiveX 컨트롤을 사용할 수 있도록 지원합니다.

/////////////////////////////////////////////////////////////////////////////

기타 표준 파일:

StdAfx.h, StdAfx.cpp
    이 파일은 미리 컴파일된 헤더 파일(PCH)인 HospitalApp.pch와
    미리 컴파일된 형식 파일인 StdAfx.obj를 빌드하는 데 사용됩니다.

Resource.h
    새 리소스 ID를 정의하는 표준 헤더 파일입니다.
    Microsoft Visual C++에서 이 파일을 읽고 업데이트합니다.

HospitalApp.manifest
	응용 프로그램 매니페스트 파일은 Windows XP에서 특정 버전의 Side-by-Side 
	어셈블리에 대한 응용 프로그램 종속성을 설명하는 데 사용됩니다. 로더는 이 정보를 
	사용하여 어셈블리 캐시에서 적절한 어셈블리를 로드하거나 응용 프로그램에서 전용 
	어셈블리를 로드합니다. 응용 프로그램 매니페스트는 응용 프로그램 실행 파일과 같은 
	폴더에 설치된 외부 .manifest 파일로 재배포를 위해 포함되거나 리소스의 형태로 
	실행 파일에 포함될 수 있습니다. 
/////////////////////////////////////////////////////////////////////////////

기타 참고:

응용 프로그램 마법사는 "TODO:"를 사용하여 추가하거나 사용자 지정해야 하는
소스 코드 부분을 나타냅니다.

응용 프로그램이 공유 DLL에서 MFC를 사용하는 경우 해당 MFC DLL을 
재배포해야 합니다. 그리고 응용 프로그램이 운영 체제의 로캘과 
다른 언어를 사용하는 경우 해당 지역화된 리소스인 MFC100XXX.DLL을 
재배포해야 합니다. 이 두가지 항목에 대한 자세한 내용은 
MSDN 설명서의 Visual C++ 응용 프로그램 재배포 항목을 
참조하십시오.

/////////////////////////////////////////////////////////////////////////////
![그림1](https://github.com/kwonjuyeong/CPlus_Hospital/assets/57522230/7b76aa10-dd73-41a3-873d-31420c35ab34)

![그림2](https://github.com/kwonjuyeong/CPlus_Hospital/assets/57522230/ec94d389-9daf-44a7-adba-b06de07c930a)

![그림3](https://github.com/kwonjuyeong/CPlus_Hospital/assets/57522230/5c935a7d-a003-4197-b8d7-558daf8b40a2)

![그림4](https://github.com/kwonjuyeong/CPlus_Hospital/assets/57522230/ed3ce54b-b743-48b3-b22a-69dfdc73b329)

![그림5](https://github.com/kwonjuyeong/CPlus_Hospital/assets/57522230/ce5c6025-8527-4ab2-86c1-38f99324521c)

![그림6](https://github.com/kwonjuyeong/CPlus_Hospital/assets/57522230/c87eb52f-02ed-4d56-9865-f93e29e0e273)

![그림7](https://github.com/kwonjuyeong/CPlus_Hospital/assets/57522230/c70c9dea-30db-4f38-b491-aac3f54e4399)

![그림8](https://github.com/kwonjuyeong/CPlus_Hospital/assets/57522230/e90a5f18-755c-491a-ae2b-fa07f8d95e12)

![그림9](https://github.com/kwonjuyeong/CPlus_Hospital/assets/57522230/a72eeb87-bc0f-4b2b-9881-9d4f641a6eea)

![그림10](https://github.com/kwonjuyeong/CPlus_Hospital/assets/57522230/1e0065a1-073e-4803-8cd5-3170a8935967)









