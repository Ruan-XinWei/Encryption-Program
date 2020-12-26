#pragma once
#include <string>

// CEncryption 对话框

class CEncryption : public CDialogEx
{
	DECLARE_DYNAMIC(CEncryption)

public:
	CEncryption(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEncryption();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Encryption };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit n_publicKey;
	CEdit n_en_old;
	CEdit n_en_new;
	afx_msg void OnBnClickedButton1();
};
