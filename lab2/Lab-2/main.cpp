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
	menu.LoadMenu(IDR_MENU1); // Загрузить меню из файла ресурса
	SetMenu(&menu);			  // Установить меню
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
	GetWindowRect(&lpRect); //извлекает размеры рамки ограничивающей прямоугольник заданного окна.
							//Размеры даются в экранных координатах, которые отсчитываются относительно левого верхнего угла экрана.
	GetCursorPos(&ptLeftButtonDown); //извлекает позицию курсора, в экранных координатах.
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
	CFileDialog dlg(TRUE); // Панель выбора файлов
	dlg.m_ofn.lpstrInitialDir = L"E:\\учеба2курс\\2сем\\КГиГ\\lab2\\Lab-2\\img";
	dlg.m_ofn.lpstrTitle = L"Открыть файл";
	int result = dlg.DoModal(); // Отображаем диалоговое окно
	LPCWSTR fileName = dlg.m_ofn.lpstrFile;
	Bit = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	key = 2;
	Invalidate(FALSE);
}

int CMainWnd::ShowBitMap(HWND hWnd, HBITMAP hBit, int x, int y) {
	BITMAP BitMap; //объект, используемый для работы с изображениями, определяемых данными о пикселях.
	GetObject(hBit, sizeof(BITMAP), &BitMap);
	HDC hdc = ::GetDC(hWnd);
	HDC hdcMem = CreateCompatibleDC(hdc); // Создаём контекст устройства
	HBITMAP OldBitMap = (HBITMAP)SelectObject(hdcMem, hBit);
	BitBlt(hdc, x, y, BitMap.bmWidth, BitMap.bmHeight, hdcMem, 0, 0, SRCCOPY); // Выполняем передачу битовых блоков данных о цвете
	SelectObject(hdcMem, OldBitMap);
	::ReleaseDC(hWnd, hdc); // Освобождаем конекст устройства
	DeleteDC(hdcMem);
	return 0;
}

int CMainWnd::ClientToBmp(HWND hWnd, RECT rect, LPCWSTR Name) {
	BITMAPFILEHEADER bmfHdr; // Тип, размер и макет файла в формате DIB
	BITMAPINFOHEADER bi;
	int BitToPixel = 16; //Устанавливаем цветовую глубину 16 бит
	HDC hdc = ::GetDC(hWnd); //Идентифицирует контекст устройства для CWnd клиентской области если успешно иначе, возвращаемое значение NULL
	HDC hdcMem = CreateCompatibleDC(hdc); //Дескриптор существующего контекста устройства (DC).
							//Если этот дескриптор равен NULL, функция создает контекст устройства в памяти, совместимый с текущим экраном приложения.

	HBITMAP BitMap = CreateCompatibleBitmap( //создает точечный рисунок, совместимый с устройством, которое связано с заданным контекстом устройства
		hdc,		// дескриптор DC
		rect.right, // ширина рисунка, в пикселях
		rect.bottom // высота рисунка, в пикселях
	);

	HBITMAP OldBitmap = (HBITMAP)SelectObject( //выбирает объект в заданный контекст устройства(DC).
		hdcMem,  // дескриптор контекста устройства (DC)
		BitMap); // дескриптор объекта

	BitBlt( //выполняет передачу битовых блоков данных о цвете, соответствующих прямоугольнику
			//пикселей из заданного исходного контекста устройства в целевой контекст устройства.						
		hdcMem, // дескриптор целевого DC
		0, // x-коорд. левого верхнего угла целевого прямоугольника
		0, // y-коорд. левого верхнего угла целевого прямоугольника
		rect.right - rect.left, // ширина целевого прямоугольника
		rect.bottom - rect.top, // высота целевого прямоугольника
		hdc,		// дескриптор исходного DC
		rect.left, // x-коорд. левого верхнего угла исходного прямоугольника
		rect.top, // y-коорд. левого верхнего угла исходного прямоугольника
		SRCCOPY); // код растровой операции
	BitMap = (HBITMAP)SelectObject(hdcMem, OldBitmap);

	ZeroMemory(&bi, sizeof(BITMAPINFOHEADER)); //заполняет блок памяти нулями.
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = rect.right - rect.left;
	bi.biHeight = rect.bottom - rect.top;
	bi.biPlanes = 1;
	bi.biBitCount = BitToPixel;
	bi.biSizeImage = (rect.right * BitToPixel + 31) / 32 * 4 * rect.bottom;
	DWORD dwWritten; //Количество записанных файлов
					 //Открываем файл
	HANDLE fh = CreateFile((LPCWSTR)Name, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL |
		FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh == INVALID_HANDLE_VALUE)
		return 2;
	bmfHdr.bfType = ('M' << 8) | 'B'; //Заполняем дисковый заголовок
	bmfHdr.bfSize = bi.biSizeImage + sizeof(bmfHdr) + bi.biSize; //Размер файла
	bmfHdr.bfReserved1 = bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = sizeof(bmfHdr) + bi.biSize; // Смещение до начала данных
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(bmfHdr), &dwWritten, NULL); //Запись заголовка в файл
	// Запись в файл загружаемого заголовка
	WriteFile(fh, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
	//Выделяем место в памяти для того,чтобы функция GetDIBits()перенесла
	//туда коды цвета в DIB-формате.
	char *lp = (char *)GlobalAlloc(GMEM_FIXED, bi.biSizeImage);
	// Из карты BitMap строки с нулевой по bi.biHeight функция пересылает
	// в массив lp по формату bi ( беспалитровый формат)
	int err = GetDIBits(hdc, BitMap, 0, (UINT)rect.bottom, lp, (LPBITMAPINFO)&bi, DIB_RGB_COLORS);
	//Запись изображения на диск
	WriteFile(fh, lp, bi.biSizeImage, &dwWritten, NULL);
	//Освобождение памяти и закрытие файла
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