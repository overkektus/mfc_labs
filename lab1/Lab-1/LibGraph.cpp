
#include "CMatrix.h"
#include "resource.h"
#include<afxwin.h>
#include "LibGraph.h"


void printUm(CPaintDC &dc, int x, int y)
{
	dc.TextOut(x, y , L"*");
	
}

void printCos(CPaintDC &dc, int x, int y)
{
	dc.TextOut(x, y, L"Cos=");
	
}

void printEq(CPaintDC &dc, int x, int y)
{
	dc.TextOut(x, y, L"=");
	
}

void printPlus(CPaintDC &dc, int x, int y)
{
	dc.TextOut(x + 3, y -1, L"+");
	
}

void printTrans(CPaintDC &dc, int x, int y)
{
	dc.TextOut(x + 3, y - 1, L" ");
}

void printSymbol(CPaintDC &dc, int x, int y, double ch)
{
	CString str;
	str.Format(L"%.1f", ch);
	dc.TextOut(x, y, str);
}

void printMatrix(CPaintDC &dc, int x, int y, int offset, CMatrix&mat, CString name, UINT symwol, bool trans)
{
	CString str;
	int hei = y;
	for (int i = 0; i < mat.rows(); i++)
	{
		dc.TextOut(x - 5, hei," ");
		for (int j = 0; j < mat.cols(); j++)
		{
			str.Format(L"%.1f", mat(i, j));
			dc.TextOut(x + j * offset, hei, str);
		}
		dc.TextOut(x + (mat.cols())*(offset), hei, " ");
		if (trans)
		{
			printTrans(dc, x + 6 + mat.cols()*offset, hei);
			trans = false;
		}
		hei += 20;
	}
	dc.TextOutW(x + (mat.cols() / 2)*offset, hei, name);
	if (symwol == PLUS)
		printPlus(dc, x + (mat.cols() + 1)*offset, y + (mat.rows() / 2) * 20);
	else if (symwol == UM)
		printUm(dc, x + (mat.cols() + 1)*offset, y + (mat.rows() / 2) * 20);
	else if (symwol == EQ)
		printEq(dc, x + (mat.cols() + 1)*offset, y + (mat.rows() / 2) * 20);



}

double opred2X2(CMatrix &mat)
{
	return mat(0, 0)*mat(1, 1) - mat(0, 1)*mat(1, 0);
}

CMatrix VectorMult(CMatrix& V1, CMatrix& V2)  //Done
{
	if (V1.cols() != V2.cols() || V1.rows() != V2.rows())
	{
		return 0;

	}
	CMatrix V3(V1);
	CMatrix ret(3);
	int cur_col = 0;
	int elem = 0;
	int  symwol= 1;
	CMatrix temp(2, 2);
	for (int i = 0; i < V1.rows(); i++)
	{
		for (int j = 1; j < V1.rows(); j++)
		{
			elem = 0;
			for (int k = 0; k < V1.rows(); k++)
			{
				if (k != cur_col)
				{
					temp.setMatrixElem(j - 1, elem, V3(k));
					elem++;
				}
			}
			V3 = V2;
		}
		V3 = V1;
		ret.setMatrixElem(i, 0, symwol* opred2X2(temp));
		cur_col++;
		symwol *= -1;
	}
	return ret;
}

double ScalarMult(CMatrix& V1, CMatrix& V2) // Done
{
	double buf = 0;
	if (V1.cols() != V2.cols() || V1.rows() != V2.rows())
	{
	
		return 0;
	}
	for (int i = 0; i < V1.rows(); i++)
	for (int j = 0; j < V1.cols(); j++)
		buf += V1(i, j) * V2(i, j);
	return buf;
}

double ModVec(CMatrix& V)
{
	double mod = 0;
	for (int i = 0; i < V.rows(); i++)
	for (int j = 0; j < V.cols(); j++)
		mod += pow(V(i, j), 2);
	return sqrt(mod);
}

double CosV1V2(CMatrix& V1, CMatrix& V2)
{
	
	return  ScalarMult(V1, V2) / (ModVec(V1)*ModVec(V2));
}

CMatrix SphereToCart(CMatrix& PView)
{
	CMatrix R(PView.rows());
	R(0) = PView(0)*sin(PView(1)*cos(PView(2)));
	R(1) = PView(0)*sin(PView(1)*sin(PView(2)));
	R(2) = PView(0)*cos(PView(1));
	return R;
}