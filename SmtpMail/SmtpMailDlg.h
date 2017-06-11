
// SmtpMailDlg.h : Í·ÎÄ¼þ
//

#pragma once



class CSmtpMailDlg : public CDialogEx
{

public:
	CSmtpMailDlg(CWnd* pParent = NULL);


	enum { IDD = IDD_SMTPMAIL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);



protected:
	HICON m_hIcon;


	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	void OnBnClickedSend();
	void OnBnClickedCancel();
};
