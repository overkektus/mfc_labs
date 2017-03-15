#pragma once
#include "resource.h"
#include "CChildView.h"

void PrintMatrix(CDC&, int, int, CMatrix&);
CMatrix VectorMult(CMatrix&, CMatrix&);
double ScalarMult(CMatrix&, CMatrix&);
double ModVec(CMatrix&);
double CosV1V2(CMatrix&, CMatrix&);
CMatrix SphereToCart(CMatrix&);

bool key[10];

CChildView matrix;

class CMainWnd : public CFrameWnd {
private:
	CMenu menu;
	DECLARE_MESSAGE_MAP()

public:
	CMainWnd::CMainWnd() {
		Create(NULL, L"Lab1", WS_OVERLAPPEDWINDOW, CRect(33, 200, 1333, 600), NULL, NULL);
	}
	
	int OnCreate(LPCREATESTRUCT);
	
	void OnMatrixC1();
	void OnMatrixC2();
	void OnMatrixD();
	void OnMatrixQ();
	void OnMatrixP();
	
	void MenuTestFunctionVectorMult();
	void MenuTestFunctionScalarMult();
	void MenuTestFunctionModVec();
	void MenuTestFunctionCosV1V2();
	void MenuTestFunctionSphereToCart();
	void ClearSheet();

	afx_msg void OnPaint() {
		if (key[0]) {
			CDC *pDC = this->GetDC();
			TextOut(*pDC, 10, 80, L"A", 1);
			PrintMatrix(*pDC, 10, 100, matrix.A);
			TextOut(*pDC, 90, 80, L"B", 1);
			PrintMatrix(*pDC, 90, 100, matrix.B);
			TextOut(*pDC, 170, 80, L"A + B", 5);
			PrintMatrix(*pDC, 170, 100, matrix.A + matrix.B);
		}

		if (key[1]) {
			CDC *pDC = this->GetDC();
			TextOut(*pDC, 250, 80, L"A", 1);
			PrintMatrix(*pDC, 250, 100, matrix.A);
			TextOut(*pDC, 330, 80, L"B", 1);
			PrintMatrix(*pDC, 330, 100, matrix.B);
			TextOut(*pDC, 400, 80, L"A * B", 5);
			PrintMatrix(*pDC, 400, 100, matrix.A * matrix.B);
		}

		if (key[2]) {
			CDC *pDC = this->GetDC();
			TextOut(*pDC, 470, 80, L"A", 1);
			PrintMatrix(*pDC, 470, 100, matrix.A);
			TextOut(*pDC, 540, 80, L"v1", 2);
			PrintMatrix(*pDC, 540, 100, matrix.V1);
			TextOut(*pDC, 610, 80, L"A * v1", 6);
			PrintMatrix(*pDC, 610, 100, matrix.A * matrix.V1);
		}

		if (key[3]) {
			CDC *pDC = this->GetDC();
			TextOut(*pDC, 670, 80, L"v1", 2);
			PrintMatrix(*pDC, 670, 100, matrix.V1);
			TextOut(*pDC, 740, 80, L"v2", 2);
			PrintMatrix(*pDC, 740, 100, matrix.V2);
			TextOut(*pDC, 820, 80, L"(v1^t) * v2", 11);
			PrintMatrix(*pDC, 820, 100, matrix.V1.Transp() * matrix.V2);
		}

		if (key[4]) {
			CDC *pDC = this->GetDC();
			TextOut(*pDC, 900, 80, L"v1", 2);
			PrintMatrix(*pDC, 900, 100, matrix.V1);
			TextOut(*pDC, 980, 80, L"A", 1);
			PrintMatrix(*pDC, 980, 100, matrix.A);
			TextOut(*pDC, 1060, 80, L"v2", 2);
			PrintMatrix(*pDC, 1060, 100, matrix.V2);
			TextOut(*pDC, 1140, 80, L"(v1^T) * A * v2", 15);
			PrintMatrix(*pDC, 1140, 100, matrix.V1.Transp() * matrix.A * matrix.V2);
		}

		if (key[5]) {
			CDC *pDC = this->GetDC();
			TextOut(*pDC, 10, 210, L"v1", 2);
			PrintMatrix(*pDC, 10, 230, matrix.V1);
			TextOut(*pDC, 90, 210, L"v2", 2);
			PrintMatrix(*pDC, 90, 230, matrix.V2);
			TextOut(*pDC, 170, 210, L"(v1 * vectMult * v2)", 24);
			PrintMatrix(*pDC, 170, 230, VectorMult(matrix.V1, matrix.V2));
		}

		if (key[6]) {
			WCHAR buf[5];
			double result = ScalarMult(matrix.V1, matrix.V2);
			_itow(result, buf, 10);
			CDC *pDC = this->GetDC();
			TextOut(*pDC, 320, 210, L"v1", 2);
			PrintMatrix(*pDC, 320, 230, matrix.V1);
			TextOut(*pDC, 400, 210, L"v2", 2);
			PrintMatrix(*pDC, 400, 230, matrix.V2);
			TextOut(*pDC, 480, 210, L"(v1 * scalMult * v2)", 24);
			TextOut(*pDC, 525, 230, buf, 2);
		}

		if (key[7]) {
			WCHAR buf[5];
			double result = ModVec(matrix.V1);
			_itow(result, buf, 10);
			CDC *pDC = this->GetDC();
			TextOut(*pDC, 600, 210, L"v1", 2);
			PrintMatrix(*pDC, 600, 230, matrix.V1);
			TextOut(*pDC, 680, 210, L"|v1|", 4);
			TextOut(*pDC, 680, 230, buf, 2);
		}

		if (key[8]) {
			WCHAR buf[5];
			double result = CosV1V2(matrix.V1, matrix.V2);
			_itow(result, buf, 10);
			CDC *pDC = this->GetDC();
			TextOut(*pDC, 800, 210, L"V1", 2);
			PrintMatrix(*pDC, 800, 230, matrix.V1);
			TextOut(*pDC, 880, 210, L"V2", 2);
			PrintMatrix(*pDC, 880, 230, matrix.V2);
			TextOut(*pDC, 960, 210, L"Cos V1 V2", 9);
			TextOut(*pDC, 960, 230, buf, 2);
		}

		if (key[9]) {
			CDC *pDC = this->GetDC();
			TextOut(*pDC, 1050, 210, L"V1", 2);
			PrintMatrix(*pDC, 1050, 230, matrix.V1);
			TextOut(*pDC, 1130, 210, L"SphereToCart V1", 15);
			PrintMatrix(*pDC, 1130, 230, SphereToCart(matrix.V1));
		}
	}
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
	ON_WM_CREATE() /* Событие создания окна */
	ON_COMMAND(ID_MATRIX_C1, &CMainWnd::OnMatrixC1)
	ON_COMMAND(ID_MATRIX_C2, &CMainWnd::OnMatrixC2)
	ON_COMMAND(ID_MATRIX_D, &CMainWnd::OnMatrixD)
	ON_COMMAND(ID_MATRIX_Q, &CMainWnd::OnMatrixQ)
	ON_COMMAND(ID_MATRIX_P, &CMainWnd::OnMatrixP)
	ON_COMMAND(ID_CLEAR, &CMainWnd::ClearSheet)
	ON_COMMAND(ID_VECTOR_MULT, &CMainWnd::MenuTestFunctionVectorMult)
	ON_COMMAND(ID_SCALAR_MULT, &CMainWnd::MenuTestFunctionScalarMult)
	ON_COMMAND(ID_MOD_VEC, &CMainWnd::MenuTestFunctionModVec)
	ON_COMMAND(ID_COS_V1V2, &CMainWnd::MenuTestFunctionCosV1V2)
	ON_COMMAND(ID_SPHERE_TO_CART, &CMainWnd::MenuTestFunctionSphereToCart)
	ON_WM_PAINT()
END_MESSAGE_MAP()


int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	menu.LoadMenu(IDR_MENU1);
	SetMenu(&menu);
	return 0;
}

void CMainWnd::OnMatrixC1() {
	ClearSheet();
	key[0] = true;
	this->Invalidate();
	//this->InvalidateRect(0);
}

void CMainWnd::OnMatrixC2() {
	ClearSheet();
	key[1] = true;
	this->InvalidateRect(0);
}

void CMainWnd::OnMatrixD() {
	ClearSheet();
	key[2] = true;
	this->InvalidateRect(0);
}

void CMainWnd::OnMatrixQ() {
	ClearSheet();
	key[3] = true;
	this->InvalidateRect(0);
}

void CMainWnd::OnMatrixP() {
	ClearSheet();
	key[4] = true;
	this->InvalidateRect(0);
}

void CMainWnd::MenuTestFunctionVectorMult() {
	ClearSheet();
	key[5] = true;
	this->InvalidateRect(0);
}

void CMainWnd::MenuTestFunctionScalarMult() {
	ClearSheet();
	key[6] = true;
	this->InvalidateRect(0);
}

void CMainWnd::MenuTestFunctionModVec() {
	ClearSheet();
	key[7] = true;
	this->InvalidateRect(0);
}

void CMainWnd::MenuTestFunctionCosV1V2() {
	ClearSheet();
	key[8] = true;
	this->InvalidateRect(0);
}

void CMainWnd::MenuTestFunctionSphereToCart() {
	ClearSheet();
	key[9] = true;
	this->InvalidateRect(0);
}

void CMainWnd::ClearSheet() {
	for (int i = 0; i < 10; i++)
		key[i] = false;
	this->InvalidateRect(0);
}