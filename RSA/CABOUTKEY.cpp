// CABOUTKEY.cpp: 实现文件
//

#include "pch.h"
#include "RSA.h"
#include "CABOUTKEY.h"
#include "afxdialogex.h"


// CABOUTKEY 对话框

IMPLEMENT_DYNAMIC(CABOUTKEY, CDialogEx)

CABOUTKEY::CABOUTKEY(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ABOUTKEY, pParent)
{

}

CABOUTKEY::~CABOUTKEY()
{
}

void CABOUTKEY::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, n_about_public);
	DDX_Control(pDX, IDC_EDIT1, n_about_private);
}


BEGIN_MESSAGE_MAP(CABOUTKEY, CDialogEx)
END_MESSAGE_MAP()


// CABOUTKEY 消息处理程序
