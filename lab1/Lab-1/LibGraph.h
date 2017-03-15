#include <afxwin.h>
#include "CMatrix.h"
#include "resource.h"
#include <math.h>

#define PLUS 1
#define UM 2
#define EQ 3
#define NUMBER_OF_OPERATIONS 10


void printUm(CPaintDC &dc, int x, int y);

void printEq(CPaintDC &dc, int x, int y);

void printPlus(CPaintDC &dc, int x, int y);

void printTrans(CPaintDC &dc, int x, int y);

void printSymbol(CPaintDC &dc, int x, int y, double ch);

void printMatrix(CPaintDC &dc, int x, int y, int offset, CMatrix&mat, CString name = "", UINT znak = 0, bool trans = false);

CMatrix VectorMult(CMatrix& V1, CMatrix& V2);  //Done


double ScalarMult(CMatrix& V1, CMatrix& V2); // Done

double ModVec(CMatrix& V);


double CosV1V2(CMatrix& V1, CMatrix& V2);

CMatrix SphereToCart(CMatrix& PView);
