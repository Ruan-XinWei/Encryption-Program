
// RSADlg.h: 头文件
//

#pragma once
#include "TabSheet.h"
#include "CDecryption.h"
#include "CEncryption.h"
#include "CABOUTKEY.h"
#include "RSA_Algorithm.h"
#include "extern.h"

// CRSADlg 对话框
class CRSADlg : public CDialogEx
{
// 构造
public:
	CRSADlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RSA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTcnSelchangeTab2(NMHDR* pNMHDR, LRESULT* pResult);
private:
	CTabSheet m_tab;

	CDecryption cdecryption;
	CEncryption cencryption;
	CABOUTKEY caboutkey;

	RSA Rsa;
};
