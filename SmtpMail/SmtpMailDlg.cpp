
// SmtpMailDlg.cpp : ʵ���ļ�
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


// CSmtpMailDlg �Ի���




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


// CSmtpMailDlg ��Ϣ�������

BOOL CSmtpMailDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MAXIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetDlgItem(IDC_ServerAddress)->SetWindowText("smtp.sina.cn");
	GetDlgItem(IDC_Port)->SetWindowText("25"); 
	GetDlgItem(IDC_UserName)->SetWindowText("terencerichtofen@sina.cn"); 
	GetDlgItem(IDC_Password)->EnableWindow(true);
	GetDlgItem(IDC_From)->SetWindowText("terencerichtofen@sina.cn");
	GetDlgItem(IDC_To)->EnableWindow(true);
	GetDlgItem(IDC_Subject)->SetWindowText("Hello! "); 
	GetDlgItem(IDC_Message)->EnableWindow(true);



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSmtpMailDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSmtpMailDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSmtpMailDlg::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}

