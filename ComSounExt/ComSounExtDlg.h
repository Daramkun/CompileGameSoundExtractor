
// ComSounExtDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "type.h"

enum OPEN
{
	NO_OPEN,
	WLK,
	MLK,
};


// CComSounExtDlg ��ȭ ����
class CComSounExtDlg : public CDialogEx
{
	// �����Դϴ�.
public:
	CComSounExtDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COMSOOUNEXT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


	// �����Դϴ�.
protected:
	HICON m_hIcon;

	OPEN openedFormat;

	// WLK //
	short int MaxWav;
	long WavBR[255], WavSP[255], WavSZ[255], WavSR[255];
	WLK2HD wlk2hd;
	unsigned char TAG[255];
	WLK2BODY wlk2body[255];
	// WLK //

	// MLK //
	int MusicSP[256];
	int MusicEP[256];
	// MLK //

	// COMMON //
	BYTE *musicDatas[255];
	int musicSize[255];
	int musicCount;
	// COMMON //

	void DestroyLKFiles();

	bool LoadMLK(CFile &file);
	bool LoadWLK(CFile &file);

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CListCtrl m_lstFiles;
	CEdit m_txtFilename;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CEdit m_outDir;
	CEdit m_outName;
	CProgressCtrl m_outProc;
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnClose();
	afx_msg void OnBnClickedOutopen();
	afx_msg void OnBnClickedConvert();
};
