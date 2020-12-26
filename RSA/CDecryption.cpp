// CDecryption.cpp: 实现文件
//

#include "pch.h"
#include "RSA.h"
#include "CDecryption.h"
#include "afxdialogex.h"
#include "extern.h"
//#include "RSA_Algorithm.h"

// CDecryption 对话框

IMPLEMENT_DYNAMIC(CDecryption, CDialogEx)

CDecryption::CDecryption(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Decryption, pParent)
{
}

CDecryption::~CDecryption()
{
}

void CDecryption::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, n_de_private);
	DDX_Control(pDX, IDC_EDIT1, n_de_old);
	DDX_Control(pDX, IDC_EDIT4, n_de_new);
}


BEGIN_MESSAGE_MAP(CDecryption, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CDecryption::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDecryption 消息处理程序


void CDecryption::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	RSA r;
	CString old, message;
	string sold, smessage;

	n_de_old.GetWindowTextW(old);

	USES_CONVERSION;
	
	sold= T2A(old);
	
	smessage = r.decrypt(sold, g_private);
	message = smessage.c_str();
	//CString message = (r.encrypt(old.GetBuffer(0), privateKey.GetBuffer(0)).c_str();
	n_de_new.SetWindowTextW(message);
}
