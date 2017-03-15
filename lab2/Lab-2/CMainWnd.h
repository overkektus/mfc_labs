#pragma once
#include "resource.h"

class CMainWnd : public CFrameWnd {
private:
	int key;
	HBITMAP Bit;
	RECT lpRect, Rect;
	POINT ptLeftButtonDown, ptRightButton0, ptRightButton1;
	int count = 0;
	CMenu menu;
	DECLARE_MESSAGE_MAP()
	int OnCreate(LPCREATESTRUCT);
public:
	CMainWnd::CMainWnd() {
		Create(NULL, L"lab2", WS_OVERLAPPEDWINDOW, CRect(33, 50, 1333, 700), NULL, NULL);
	}
	void OnPaint();
	void OnLButtonDown(UINT, CPoint);
	void SetPoint(CPaintDC&, long, long, COLORREF);
	void InsertImg();
	int ShowBitMap(HWND, HBITMAP, int, int);
	void OnRButtonDown(UINT, CPoint);
	int ClientToBmp(HWND, RECT, LPCWSTR);
	void Clear();
	void Exit();
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_INSERTIMG, InsertImg)
	ON_COMMAND(ID_CLEAR, Clear)
	ON_COMMAND(ID_EXIT, Exit)
	ON_WM_PAINT()
END_MESSAGE_MAP()