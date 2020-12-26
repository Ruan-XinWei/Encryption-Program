#pragma once
#include <string>

// CDecryption 对话框

class CDecryption : public CDialogEx
{
	DECLARE_DYNAMIC(CDecryption)

public:
	CDecryption(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDecryption();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Decryption };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit n_de_private;
	afx_msg void OnBnClickedButton1();
	CEdit n_de_old;
	CEdit n_de_new;
};
