#pragma once
#include <ctime>
#include "CMatrix.h"

class CChildView {
public:
	CMatrix A, B, V1, V2;
	CChildView();
};

CChildView::CChildView() {
	A.RedimMatrix(3, 3);
	B.RedimMatrix(3, 3);
	V1.RedimMatrix(3, 1);
	V2.RedimMatrix(3, 1);
	A.setMatrixRow(0, 3, 1, 9, 7);
	A.setMatrixRow(1, 3, 4, 5, 6);
	A.setMatrixRow(2, 3, 7, 8, 9);
	B.setMatrixRow(0, 3, 2, 4, 6);
	B.setMatrixRow(1, 3, 8, 7, 5);
	B.setMatrixRow(2, 3, 6, 1, 4);
	V1.setMatrixCol(0, 3, 5, 7, 3);
	V2.setMatrixCol(0, 3, 1, 8, 6);
}