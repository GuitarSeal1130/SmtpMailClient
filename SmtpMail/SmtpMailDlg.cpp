
// SmtpMailDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SmtpMail.h"
#include "SmtpMailDlg.h"
#include "afxdialogex.h"
#include "Sending-Email.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSmtpMailDlg 对话框




CSmtpMailDlg::CSmtpMailDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSmtpMailDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSmtpMailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSmtpMailDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Send, &CSmtpMailDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_Exit, &CSmtpMailDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSmtpMailDlg 消息处理程序

BOOL CSmtpMailDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MAXIMIZE);

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_ServerAddress)->SetWindowText("smtp.sina.cn");
	GetDlgItem(IDC_Port)->SetWindowText("25"); 
	GetDlgItem(IDC_UserName)->SetWindowText("terencerichtofen@sina.cn"); 
	GetDlgItem(IDC_Password)->EnableWindow(true);
	GetDlgItem(IDC_From)->SetWindowText("terencerichtofen@sina.cn");
	GetDlgItem(IDC_To)->EnableWindow(true);
	GetDlgItem(IDC_Subject)->SetWindowText("Hello! "); 
	GetDlgItem(IDC_Message)->EnableWindow(true);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSmtpMailDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSmtpMailDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSmtpMailDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString a,b,c,d,e,f,g,h;
	GetDlgItem(IDC_ServerAddress)->GetWindowText(a); 
	GetDlgItem(IDC_Port)->GetWindowText(b); 
	GetDlgItem(IDC_UserName)->GetWindowText(c); 
	GetDlgItem(IDC_Password)->GetWindowText(d); 
	GetDlgItem(IDC_From)->GetWindowText(e); 
	GetDlgItem(IDC_To)->GetWindowText(f); 
	GetDlgItem(IDC_Subject)->GetWindowText(g); 
	GetDlgItem(IDC_Message)->GetWindowText(h);
	
	char *address=new char[strlen(a)];
	strcpy(address,a);
	char *port=new char[strlen(b)];
	strcpy(port,b);
	char *username=new char[strlen(c)];
	strcpy(username,c);
	char *password=new char[strlen(d)];
	strcpy(password,d);
	char *from=new char[strlen(e)];
	strcpy(from,e);
	char *to=new char[strlen(f)];
	strcpy(to,f);
	char *subject=new char[strlen(g)];
	strcpy(subject,g);
	char *message=new char[strlen(h)];
	strcpy(message,h);
	
	SmtpMail mail(address,port,username,password,from,to,subject,message);
	mail.SendMail();
	
	/*
	delete address;
	delete port;
	delete username;
	delete password;
	delete from;
	delete to;
	delete subject;
	delete message;
	*/
}

void CSmtpMailDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

