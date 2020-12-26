// CEncryption.cpp: 实现文件
//

#include "pch.h"
#include "RSA_Algorithm.h"
#include "RSA.h"
#include "CEncryption.h"
#include "afxdialogex.h"
#include "extern.h"


// CEncryption 对话框

IMPLEMENT_DYNAMIC(CEncryption, CDialogEx)

CEncryption::CEncryption(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Encryption, pParent)
{

}

CEncryption::~CEncryption()
{
}

void CEncryption::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, n_publicKey);
	DDX_Control(pDX, IDC_EDIT1, n_en_old);
	DDX_Control(pDX, IDC_EDIT4, n_en_new);
}


BEGIN_MESSAGE_MAP(CEncryption, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CEncryption::OnBnClickedButton1)
END_MESSAGE_MAP()


// CEncryption 消息处理程序


void CEncryption::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CString old, message;
	string sold, smessage;
	//RSA r;

	n_en_old.GetWindowTextW(old);
	//n_publicKey.GetWindowTextW(pub);

	USES_CONVERSION;
	sold = T2A(old);

	smessage = r.encrypt(sold, g_public);

	message = smessage.c_str();
	n_en_new.SetWindowTextW(message);
}
