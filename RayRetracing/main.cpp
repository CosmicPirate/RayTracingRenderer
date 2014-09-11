
#include "Structures.h"
#include "Camera.h"
#include "Scene.h"
#include "Geometry.h"

#include <Windows.h>
#include <ctime>
#include <gdiplus.h>

#define CLASS_NAME "RayTracerWindow"

using namespace RayTracingEngine;

DWORD gLastError;
HINSTANCE gHIntance;

// The WinProc
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;

	} // switch(message)

	return DefWindowProc(hwnd, message, wparam, lparam);
}

HWND CreateMyWindow(HINSTANCE hInstance, int width, int height, bool isFullScreen)
{
	HWND hWnd;
	WNDCLASS wndclass;

	memset(&wndclass, 0, sizeof(WNDCLASS));
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WinProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszClassName = "RayTracingClass";

	RegisterClass(&wndclass);

	//if (isFullScreen)
	//{
	//	dwStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	//	ChangeToFullScreen();
	//	ShowCursor(FALSE);
	//}
	//else if (!dwStyle)
	DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	RECT rWindow;
	rWindow.left = 0;
	rWindow.right = width;
	rWindow.top = 0;
	rWindow.bottom = height;

	AdjustWindowRect(&rWindow, dwStyle, false);

	// Create the window
	hWnd = CreateWindow("RayTracingClass", "Ray Tracing", dwStyle, 0, 0,
		rWindow.right - rWindow.left, rWindow.bottom - rWindow.top,
		NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		gLastError = GetLastError();
		return NULL;
	}

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	SetFocus(hWnd);

	return hWnd;
}

WPARAM MainLoop()
{
	MSG msg;

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}

	return(msg.wParam);
}


HBITMAP BitmapFromByteBuffer(HDC hdc, byte*& bufferPtr, int width, int height)
{
	BITMAPINFO bmp_info = { 0 };

	// Initialize the parameters that we care about
	bmp_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmp_info.bmiHeader.biWidth = width;
	bmp_info.bmiHeader.biHeight = height;
	bmp_info.bmiHeader.biPlanes = 1; // Must be set to one
	bmp_info.bmiHeader.biBitCount = 24;
	bmp_info.bmiHeader.biCompression = BI_RGB; // Bitmap is NOT compressed

	HBITMAP hBitmap = CreateDIBSection(NULL, &bmp_info, DIB_RGB_COLORS, (void**)&bufferPtr, NULL, NULL);

	return hBitmap;
}

byte* CreateBuffer(HDC& imgDC, int width, int height)
{
	byte* bitmapBuffer;

	HBITMAP hBitmap = BitmapFromByteBuffer(NULL, bitmapBuffer, width, height);

	if (hBitmap == NULL)
		return 0;

	imgDC = CreateCompatibleDC(NULL);

	if (imgDC == NULL)
		return 0;

	HBITMAP old_bitmap = (HBITMAP)SelectObject(imgDC, hBitmap);

	if (old_bitmap == NULL)
		return 0;

	return bitmapBuffer;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprev, PSTR cmdline, int ishow)
{
	gmtl::Math::seedRandom(time(0));

	gHIntance = hInstance;

	CCamera cam(600, 600,
				CPoint3(0, 0, 0), CVector3(0, 0, -1), CVector3(0, 0.6, 0.5),
				100, 100, 100);

	HWND hWindow = CreateMyWindow(hInstance, cam.width, cam.height, false);

	HDC imgDC;
	byte * imageBuffer = CreateBuffer(imgDC, cam.width, cam.height);

	CModel* world = new CModel();
	world->addSurface(new CSphere(CVector3(0, 0, -5), 2));

	float unit = 0.0039215686274509803921568627451f;

	Ray ray;
	Intersection inters;
	byte* imgBufferPointer = imageBuffer;
	while (cam.getNextRay(ray))
	{
		if (world->intersect(inters, ray))
		{
			RGBColor color = inters.ptrTexture->getColor(CVector2(), inters.pPoint);
			byte r = gmtl::Math::ceil(color.eR / unit);
			byte g = gmtl::Math::ceil(color.eG / unit);
			byte b = gmtl::Math::ceil(color.eB / unit);
			*(imageBuffer++) = r;
			*(imageBuffer++) = g;
			*(imageBuffer++) = b;
		}
		else
		{
			*(imageBuffer++) = 0;
			*(imageBuffer++) = 0;
			*(imageBuffer++) = 0;
		}
	}

	BitBlt(GetDC(hWindow), 0, 0, cam.width, cam.height,
		imgDC, 0, 0, SRCCOPY);

	UpdateWindow(hWindow);

	return (int)MainLoop();
}

