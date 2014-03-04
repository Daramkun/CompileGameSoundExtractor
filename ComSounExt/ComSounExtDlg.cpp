
// ComSounExtDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ComSounExt.h"
#include "ComSounExtDlg.h"
#include "afxdialogex.h"
#include "type.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CComSounExtDlg ��ȭ ����




CComSounExtDlg::CComSounExtDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComSounExtDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComSounExtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PACKEDFILES, m_lstFiles);
	DDX_Control(pDX, IDC_SOURCEFILE, m_txtFilename);
	DDX_Control(pDX, IDC_OUTPUTDIR, m_outDir);
	DDX_Control(pDX, IDC_OUTPUTNAME, m_outName);
	DDX_Control(pDX, IDC_PROCESSING, m_outProc);
}

BEGIN_MESSAGE_MAP(CComSounExtDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_EXIT, &CComSounExtDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_OPEN, &CComSounExtDlg::OnBnClickedOpen)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_OUTOPEN, &CComSounExtDlg::OnBnClickedOutopen)
	ON_BN_CLICKED(IDC_CONVERT, &CComSounExtDlg::OnBnClickedConvert)
END_MESSAGE_MAP()


// CComSounExtDlg �޽��� ó����

BOOL CComSounExtDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CComSounExtDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CComSounExtDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CComSounExtDlg::DestroyLKFiles()
{
	int index = 0;

	m_lstFiles.DeleteAllItems();
	m_txtFilename.SetWindowTextW(L"");

	while(musicDatas[index])
	{
		delete musicDatas[index];
		musicDatas[index] = NULL;
		index++;
	}

	ZeroMemory(musicDatas, sizeof(musicDatas));

	switch(openedFormat)
	{
	case WLK:
		ZeroMemory(&wlk2hd, sizeof(wlk2hd));
		ZeroMemory(WavBR, sizeof(WavBR));
		ZeroMemory(WavSP, sizeof(WavSP));
		ZeroMemory(WavSZ, sizeof(WavSZ));
		ZeroMemory(WavSR, sizeof(WavSR));
		ZeroMemory(TAG, sizeof(TAG));
		ZeroMemory(wlk2body, sizeof(wlk2body));
		break;
	case MLK:
		ZeroMemory(MusicSP, sizeof(MusicSP));
		ZeroMemory(MusicEP, sizeof(MusicEP));
		break;
	}
}

int CComSounExtDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	ZeroMemory(musicDatas, sizeof(musicDatas));

	ZeroMemory(&wlk2hd, sizeof(wlk2hd));
	ZeroMemory(WavBR, sizeof(WavBR));
	ZeroMemory(WavSP, sizeof(WavSP));
	ZeroMemory(WavSZ, sizeof(WavSZ));
	ZeroMemory(WavSR, sizeof(WavSR));
	ZeroMemory(TAG, sizeof(TAG));
	ZeroMemory(wlk2body, sizeof(wlk2body));

	ZeroMemory(MusicSP, sizeof(MusicSP));
	ZeroMemory(MusicEP, sizeof(MusicEP));

	return 0;
}


void CComSounExtDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	m_lstFiles.InsertColumn(0, L"No", LVCFMT_LEFT | LVCFMT_FIXED_WIDTH, 50);
	m_lstFiles.InsertColumn(1, L"Filename", LVCFMT_LEFT | LVCFMT_FIXED_WIDTH, 220);
	m_lstFiles.InsertColumn(2, L"Size", LVCFMT_LEFT | LVCFMT_FIXED_WIDTH, 140);
}

void CComSounExtDlg::OnBnClickedExit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	PostQuitMessage(0);
}

bool CComSounExtDlg::LoadMLK(CFile &file)
{
	int nRead;
	BYTE chr;

	int SeekP=0;
	int MusicNo = 0;

	int writeOn = 0;
	int writePP = 0;

	while(nRead = file.Read(&chr, sizeof(char)))
	{
		SeekP++;
		if(chr=='M')
		{
			nRead = file.Read(&chr, sizeof(char)); SeekP++;
			if(chr=='T')
			{
				nRead = file.Read(&chr, sizeof(char)); SeekP++;
				if(chr=='h')
				{
					nRead = file.Read(&chr, sizeof(char)); SeekP++;
					if(chr=='d')
					{
						MusicNo++; if(MusicNo>0) MusicEP[MusicNo-1] = SeekP-4;
						MusicSP[MusicNo] = SeekP-3;
					}
				}
			}
		}
	}

	MusicEP[MusicNo] = SeekP;

	musicCount = MusicNo - 1;

	for(int i = 0; i < MusicNo - 1; i++)
	{
		wchar_t temp[64] = {0, };
		swprintf(temp, L"%d", i + 1);
		m_lstFiles.InsertItem(i, temp);
		swprintf(temp, L"%d.mid", i);
		m_lstFiles.SetItemText(i, 1, temp);
		swprintf(temp, L"%.2fKB", (MusicEP[i + 1] - MusicSP[i + 1]) / 1024.0f);
		m_lstFiles.SetItemText(i, 2, temp);

		musicDatas[i] = new BYTE[MusicEP[i + 1] - MusicSP[i + 1] + 1];
		musicSize[i] = MusicEP[i + 1] - MusicSP[i + 1] + 1;
	}

	file.Seek(0L, 0);
	int k = 1, j = 0;
	SeekP = 0;

	while(nRead = file.Read(&chr, sizeof(char)))
	{
		SeekP++;
		if(SeekP == MusicSP[k])
		{
			j = 0; writeOn = 1;
		}

		if(writeOn == 1)
		{
			musicDatas[k - 1][j] = chr;
			j++;
		}

		if(SeekP == MusicEP[k])
		{
			j = 0; k++; writeOn = 0;
		}

		if(k == MusicNo)
			break;
	}

	openedFormat = MLK;

	return true;
}

bool CComSounExtDlg::LoadWLK(CFile &file)
{
	int nRead;
	BYTE chr;
	nRead = file.Read(&wlk2hd, sizeof(WLK2HD));
	if (!(wlk2hd.STR[0] == 'W' && wlk2hd.STR[1] == 'L' && wlk2hd.STR[2] == 'K' &&
		wlk2hd.STR[3] == 'F' && wlk2hd.STR[4] == '0' && wlk2hd.STR[5] == '2' &&
		wlk2hd.STR[6] == '0' && wlk2hd.STR[7] == '0'))
	{
		MessageBox(L"This file is not wlk 2 file.\n");
		file.Close();
		return false;
	}

	MaxWav = (short)wlk2hd.MaxWav++;
	musicCount = MaxWav;

	for(int i = 0; i < MaxWav; i++)
	{
		nRead = file.Read(&chr, sizeof(BYTE));
		nRead = file.Read(&TAG[i], sizeof(BYTE));
		nRead = file.Read(&wlk2body[i], sizeof(WLK2BODY));

		WavSP[i] = wlk2body[i].SP;
		WavSR[i] = wlk2body[i].SR;
		WavSZ[i] = wlk2body[i].SZ;

		wchar_t temp[64] = {0, };
		swprintf(temp, L"%d", i + 1);
		m_lstFiles.InsertItem(i, temp);
		swprintf(temp, L"%d.wav", i);
		m_lstFiles.SetItemText(i, 1, temp);
		swprintf(temp, L"%.2fKB", wlk2body[i].SZ / 1024.0f);
		m_lstFiles.SetItemText(i, 2, temp);
	}

	for(int i = 0; i < MaxWav; i++)
	{
		file.Seek(WavSP[i], 0);
		musicDatas[i] = new BYTE[WavSZ[i] + 1];
		musicSize[i] = WavSZ[i];
		file.Read(musicDatas[i], WavSZ[i]);
	}

	openedFormat = WLK;

	return true;
}

void CComSounExtDlg::OnBnClickedOpen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog fileDialog(TRUE);
	fileDialog.m_ofn.lpstrFilter = 
		L"Compile Corp., Packing Files(*.wlk;*.mlk)\0*.wlk;*.mlk\0WLK File(*.wlk)\0*.wlk\0MLK File(*.mlk)\0*.mlk";

	if(fileDialog.DoModal() == IDOK)
	{
		DestroyLKFiles();

		CFile file(fileDialog.GetPathName(), 0);

		if(fileDialog.GetFileExt().MakeLower() == L"mlk")
		{
			LoadMLK(file);
		}
		else
		{
			LoadWLK(file);
		}

		file.Close();

		m_txtFilename.SetWindowTextW(fileDialog.GetPathName());
	}
}

void CComSounExtDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	DestroyLKFiles();

	CDialogEx::OnClose();
}


void CComSounExtDlg::OnBnClickedOutopen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFolderPickerDialog fpd;
	if(fpd.DoModal() == IDOK)
	{
		m_outDir.SetWindowTextW(fpd.GetPathName());
	}
}


void CComSounExtDlg::OnBnClickedConvert()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int i = 0;
	CString myfile, dir, pre;

	m_txtFilename.GetWindowTextW(myfile);

	if(myfile.GetLength() == 0)
	{
		MessageBox(L"Please open any WLK/MLK file.");
		return;
	}

	m_outDir.GetWindowTextW(dir);

	if(dir.GetLength() == 0)
	{
		MessageBox(L"Please set destination directory.");
		return;
	}

	m_outName.GetWindowTextW(pre);

	WAVEFILEHDR waveheader =  { {'R','I','F','F'}, 0L, {'W','A','V','E'},
								{'f','m','t',' '}, 16L, 1, 1, 0L, 0L, 2, 16, {'d','a','t','a'}, 0L };

	m_outProc.SetRange(0, musicCount);

	while(musicDatas[i])
	{
		wchar_t filename[256] = {0, };
		swprintf(filename, L"%s\\%s%d.%s", dir.GetString(), pre.GetString(), i, 
			(openedFormat == MLK) ? L"mid" : L"wav");

		CFile file(filename, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
		if(openedFormat == WLK)
		{
			waveheader.samples_per_sec = WavSR[i];

			if(TAG[i] == 0x00)
			{
				waveheader.avg_bytes_per_sec = WavSR[i];
				waveheader.bits_per_sample = 8;
			}
			else if(TAG[i] == 0x20)
			{
				if(wlk2body[i].A[0] == 0xF8)
				{
					waveheader.avg_bytes_per_sec = WavSR[i];
					waveheader.bits_per_sample = 8;
				}else{
					waveheader.avg_bytes_per_sec = WavSR[i];
					waveheader.bits_per_sample = 8;
				}
			}
			else if(TAG[i] == 0x80)
			{
				if(wlk2body[i].A[0] == 0x0C)
				{
					waveheader.avg_bytes_per_sec = WavSR[i];
					waveheader.bits_per_sample = 16;
				}else{
					waveheader.avg_bytes_per_sec = WavSR[i];
					waveheader.bits_per_sample = 8;
				}
			}

			file.Write(&waveheader, sizeof(waveheader));
		}

		file.Write(musicDatas[i], musicSize[i]);
		file.Close();

		m_outProc.SetPos(m_outProc.GetPos() + 1);
		i++;
	}

	MessageBox(L"Converting Succeed");
}
