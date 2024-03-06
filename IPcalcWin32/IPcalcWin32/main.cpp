#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <CommCtrl.h>
#include <cstdio>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInts, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{

		HWND hIPaddress = GetDlgItem(hwnd, IDC_IPADDRESS);
		SetFocus(hIPaddress);
	}
		break;
		
	case WM_KILLFOCUS:
	{
		//HWND hIPaddress = GetDlgItem(hwnd, IDC_IPADDRESS);
		//HWND hStaticInfo = GetDlgItem(hwnd, IDC_STATIC_INFO);
		//if ((HWND)wParam == hIPaddress)
		//{
		//	DWORD dwIPaddress = 0;
		//	SendMessage(hIPaddress, IPM_GETADDRESS, 0, (LPARAM)&dwIPaddress);
		//	DWORD first = FIRST_IPADDRESS(dwIPaddress);
		//	CHAR info[256]{};
		//	sprintf(info, "%i", first);
		//	SendMessage(hStaticInfo, WM_SETTEXT, 0, (LPARAM)info);
		//}
	}
		break;

	case WM_NOTIFY:
	{
			HWND hIPaddress = GetDlgItem(hwnd, IDC_IPADDRESS);
			HWND hIPmask = GetDlgItem(hwnd, IDC_IPMASK);
			HWND hEditPrefix = GetDlgItem(hwnd, IDC_EDIT_PREFIX);
			HWND hStaticInfo = GetDlgItem(hwnd, IDC_STATIC_INFO);
		switch (wParam)
		{
		case IDC_IPADDRESS:
		{

			DWORD dwIPaddress = 0;
			SendMessage(hIPaddress, IPM_GETADDRESS, 0, (LPARAM)&dwIPaddress);
			DWORD first = FIRST_IPADDRESS(dwIPaddress);
			DWORD dwMask = 0;
			if (first > 0 && first < 128) dwMask = 0xFF000000;
			else if (first >= 128 && first < 192) dwMask = 0xFFFF0000;
			else if (first >= 192 && first < 224) dwMask = 0xFFFFFF00;
			SendMessage(hIPmask, IPM_SETADDRESS, 0, (LPARAM)dwMask);

			CHAR info[256]{};
			sprintf(info, "%i", first);
			SendMessage(hStaticInfo, WM_SETTEXT, 0, (LPARAM)info);
		}
			

		case IDC_IPMASK:
		{
			DWORD dwIPmask = 0;
			SendMessage(hIPmask, IPM_GETADDRESS, 0, (LPARAM)&dwIPmask);
			int i = 32;
			for (; dwIPmask & 0x01 ^ 1; i--) dwIPmask >>= 1;
			CHAR prefix[5];
			sprintf(prefix, "%i", i);
			SendMessage(hEditPrefix, WM_SETTEXT, 0, (LPARAM)prefix);

		}
			break;
		}
	}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_IPADDRESS:

			break;

		case IDOK: 
		{
			HWND hIPaddress = GetDlgItem(hwnd, IDC_IPADDRESS);
			HWND hIPmask = GetDlgItem(hwnd, IDC_IPMASK);
			HWND hStaticInfo = GetDlgItem(hwnd, IDC_STATIC_INFO);
			//if ((HWND)wParam == hIPaddress)
			{
				DWORD dwIPaddress = 0;
				SendMessage(hIPaddress, IPM_GETADDRESS, 0, (LPARAM)&dwIPaddress);
				DWORD first = FIRST_IPADDRESS(dwIPaddress);
				DWORD dwMask = 0;
				if (first > 0 && first < 128) dwMask = 0xFF000000;
				else if (first >= 128 && first < 192) dwMask = 0xFFFF0000;
				else if (first >= 192 && first < 224) dwMask = 0xFFFFFF00;
				SendMessage(hIPmask, IPM_SETADDRESS, 0, (LPARAM)dwMask);

				CHAR info[256]{};
				sprintf(info, "%i", first);
				SendMessage(hStaticInfo, WM_SETTEXT, 0, (LPARAM)info);
			}
		}
			break;

		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;

	case WM_CLOSE: EndDialog(hwnd, 0); break;
	}

	return FALSE;
}