#include <afxwin.h>
#include <afxdlgs.h>
#include "CMainWnd.h"
#include "CApp.h"

void CMainWnd::OnPaint() {
	CPaintDC dc(this);
	switch (key) {
	case 0:
		SetPoint(dc, ptLeftButtonDown.x, ptLeftButtonDown.y, RGB(200, 40, 0));
		break;
	case 1: {
		if (count == 0) {
			SetPoint(dc, ptRightButton0.x, ptRightButton0.y, RGB(200, 0, 200));
			count++;
		}
		else if (count == 1) {
			SetPoint(dc, ptRightButton1.x, ptRightButton1.y, RGB(0, 200, 200));
			ClientToBmp(m_hWnd, Rect, L"img\\screen.bmp");
			count = 0;
		}
	} break;
	case 2:
		ShowBitMap(m_hWnd, Bit, ptLeftButtonDown.x, ptLeftButtonDown.y);
		break;
	case 3:
		Invalidate();
		break;
	}
}

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	menu.LoadMenu(IDR_MENU1); // ��������� ���� �� ����� �������
	SetMenu(&menu);			  // ���������� ����
	return 0;
}

void CMainWnd::SetPoint(CPaintDC &dc, long x, long y, COLORREF color) {
	int size = 5;
	for (int i(-size); i <= size; i++) {
		dc.SetPixel(x, y + i, color);
	}
	for (int j(-size); j <= size; j++) {
		dc.SetPixel(x + j, y, color);
	}
}

void CMainWnd::OnLButtonDown(UINT flags, CPoint Loc) {
	GetWindowRect(&lpRect); //��������� ������� ����� �������������� ������������� ��������� ����.
							//������� ������ � �������� �����������, ������� ������������� ������������ ������ �������� ���� ������.
	GetCursorPos(&ptLeftButtonDown); //��������� ������� �������, � �������� �����������.
	ptLeftButtonDown.x = ptLeftButtonDown.x - lpRect.left - 10;
	ptLeftButtonDown.y = ptLeftButtonDown.y - lpRect.top - 10 - 40 - 3;
	key = 0;
	Invalidate(FALSE);
}

void CMainWnd::OnRButtonDown(UINT, CPoint) {
	GetWindowRect(&lpRect);
	if (count == 0) {
		GetCursorPos(&ptRightButton0);
		ptRightButton0.x = ptRightButton0.x - lpRect.left - 10;
		ptRightButton0.y = ptRightButton0.y - lpRect.top - 10 - 40 - 3;
	}

	else if (count == 1) {
		GetCursorPos(&ptRightButton1);
		ptRightButton1.x = ptRightButton1.x - lpRect.left - 10;
		ptRightButton1.y = ptRightButton1.y - lpRect.top - 10 - 40 - 3;

		Rect.left = ptRightButton0.x;
		Rect.top = ptRightButton0.y;
		Rect.right = ptRightButton1.x;
		Rect.bottom = ptRightButton1.y;
	}
	key = 1;
	Invalidate(FALSE);
}

void CMainWnd::InsertImg() {
	CFileDialog dlg(TRUE); // ������ ������ ������
	dlg.m_ofn.lpstrInitialDir = L"E:\\�����2����\\2���\\����\\lab2\\Lab-2\\img";
	dlg.m_ofn.lpstrTitle = L"������� ����";
	int result = dlg.DoModal(); // ���������� ���������� ����
	LPCWSTR fileName = dlg.m_ofn.lpstrFile;
	Bit = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	key = 2;
	Invalidate(FALSE);
}

int CMainWnd::ShowBitMap(HWND hWnd, HBITMAP hBit, int x, int y) {
	BITMAP BitMap; //������, ������������ ��� ������ � �������������, ������������ ������� � ��������.
	GetObject(hBit, sizeof(BITMAP), &BitMap);
	HDC hdc = ::GetDC(hWnd);
	HDC hdcMem = CreateCompatibleDC(hdc); // ������ �������� ����������
	HBITMAP OldBitMap = (HBITMAP)SelectObject(hdcMem, hBit);
	BitBlt(hdc, x, y, BitMap.bmWidth, BitMap.bmHeight, hdcMem, 0, 0, SRCCOPY); // ��������� �������� ������� ������ ������ � �����
	SelectObject(hdcMem, OldBitMap);
	::ReleaseDC(hWnd, hdc); // ����������� ������� ����������
	DeleteDC(hdcMem);
	return 0;
}

int CMainWnd::ClientToBmp(HWND hWnd, RECT rect, LPCWSTR Name) {
	BITMAPFILEHEADER bmfHdr; // ���, ������ � ����� ����� � ������� DIB
	BITMAPINFOHEADER bi;
	int BitToPixel = 16; //������������� �������� ������� 16 ���
	HDC hdc = ::GetDC(hWnd); //�������������� �������� ���������� ��� CWnd ���������� ������� ���� ������� �����, ������������ �������� NULL
	HDC hdcMem = CreateCompatibleDC(hdc); //���������� ������������� ��������� ���������� (DC).
							//���� ���� ���������� ����� NULL, ������� ������� �������� ���������� � ������, ����������� � ������� ������� ����������.

	HBITMAP BitMap = CreateCompatibleBitmap( //������� �������� �������, ����������� � �����������, ������� ������� � �������� ���������� ����������
		hdc,		// ���������� DC
		rect.right, // ������ �������, � ��������
		rect.bottom // ������ �������, � ��������
	);

	HBITMAP OldBitmap = (HBITMAP)SelectObject( //�������� ������ � �������� �������� ����������(DC).
		hdcMem,  // ���������� ��������� ���������� (DC)
		BitMap); // ���������� �������

	BitBlt( //��������� �������� ������� ������ ������ � �����, ��������������� ��������������
			//�������� �� ��������� ��������� ��������� ���������� � ������� �������� ����������.						
		hdcMem, // ���������� �������� DC
		0, // x-�����. ������ �������� ���� �������� ��������������
		0, // y-�����. ������ �������� ���� �������� ��������������
		rect.right - rect.left, // ������ �������� ��������������
		rect.bottom - rect.top, // ������ �������� ��������������
		hdc,		// ���������� ��������� DC
		rect.left, // x-�����. ������ �������� ���� ��������� ��������������
		rect.top, // y-�����. ������ �������� ���� ��������� ��������������
		SRCCOPY); // ��� ��������� ��������
	BitMap = (HBITMAP)SelectObject(hdcMem, OldBitmap);

	ZeroMemory(&bi, sizeof(BITMAPINFOHEADER)); //��������� ���� ������ ������.
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = rect.right - rect.left;
	bi.biHeight = rect.bottom - rect.top;
	bi.biPlanes = 1;
	bi.biBitCount = BitToPixel;
	bi.biSizeImage = (rect.right * BitToPixel + 31) / 32 * 4 * rect.bottom;
	DWORD dwWritten; //���������� ���������� ������
					 //��������� ����
	HANDLE fh = CreateFile((LPCWSTR)Name, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL |
		FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh == INVALID_HANDLE_VALUE)
		return 2;
	bmfHdr.bfType = ('M' << 8) | 'B'; //��������� �������� ���������
	bmfHdr.bfSize = bi.biSizeImage + sizeof(bmfHdr) + bi.biSize; //������ �����
	bmfHdr.bfReserved1 = bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = sizeof(bmfHdr) + bi.biSize; // �������� �� ������ ������
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(bmfHdr), &dwWritten, NULL); //������ ��������� � ����
	// ������ � ���� ������������ ���������
	WriteFile(fh, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
	//�������� ����� � ������ ��� ����,����� ������� GetDIBits()���������
	//���� ���� ����� � DIB-�������.
	char *lp = (char *)GlobalAlloc(GMEM_FIXED, bi.biSizeImage);
	// �� ����� BitMap ������ � ������� �� bi.biHeight ������� ����������
	// � ������ lp �� ������� bi ( ������������� ������)
	int err = GetDIBits(hdc, BitMap, 0, (UINT)rect.bottom, lp, (LPBITMAPINFO)&bi, DIB_RGB_COLORS);
	//������ ����������� �� ����
	WriteFile(fh, lp, bi.biSizeImage, &dwWritten, NULL);
	//������������ ������ � �������� �����
	GlobalFree(GlobalHandle(lp));
	CloseHandle(fh);
	::ReleaseDC(hWnd, hdc);
	DeleteDC(hdcMem);
	if (dwWritten == 0)
	return 0;
}

void CMainWnd::Clear() {
	key = 3;
	RedrawWindow();
}

void CMainWnd::Exit() {
	DestroyWindow();
}

CApp theApp;