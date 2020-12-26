#pragma once


// CABOUTKEY 对话框

class CABOUTKEY : public CDialogEx
{
	DECLARE_DYNAMIC(CABOUTKEY)

public:
	CABOUTKEY(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CABOUTKEY();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTKEY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit n_about_public;
	CEdit n_about_private;
};
