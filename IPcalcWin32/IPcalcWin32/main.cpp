#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <CommCtrl.h>
#include <cstdio>
#include <cmath>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID GetInfo(HWND hwnd);
VOID GetIPBytes(DWORD dwIPaddress, CHAR* szIPaddress);


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

		HWND hSpinPrefix = GetDlgItem(hwnd, IDC_SPIN_PREFIX);
		SendMessage(hSpinPrefix, UDM_SETRANGE, 0, MAKELPARAM(32, 0));	//UDM - Up/Down Message
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
			if (dwIPmask == 0) break;
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
		case IDC_EDIT_PREFIX:
		{
			if (HIWORD(wParam) == EN_UPDATE)
			{
				HWND hEditPrefix = GetDlgItem(hwnd, IDC_EDIT_PREFIX);
				CONST INT SIZE = 5;
				CHAR sz_prefix[SIZE] = {};
				SendMessage(hEditPrefix, WM_GETTEXT, SIZE, (LPARAM)sz_prefix);
				DWORD dwPrefix = atoi(sz_prefix);
				DWORD dwIPmask = UINT_MAX;
				dwIPmask >>= (32 - dwPrefix);
				dwIPmask <<= (32 - dwPrefix);
				SendMessage(GetDlgItem(hwnd, IDC_IPMASK), IPM_SETADDRESS, 0, (LPARAM)dwIPmask);
				GetInfo(hwnd);
			}
		}
			break;

		case IDOK: 
		{
			//HWND hIPaddress = GetDlgItem(hwnd, IDC_IPADDRESS);
			//HWND hIPmask = GetDlgItem(hwnd, IDC_IPMASK);
			//HWND hStaticInfo = GetDlgItem(hwnd, IDC_STATIC_INFO);
			////if ((HWND)wParam == hIPaddress)
			//{
			//	DWORD dwIPaddress = 0;
			//	SendMessage(hIPaddress, IPM_GETADDRESS, 0, (LPARAM)&dwIPaddress);
			//	DWORD first = FIRST_IPADDRESS(dwIPaddress);
			//	DWORD dwMask = 0;
			//	if (first > 0 && first < 128) dwMask = 0xFF000000;
			//	else if (first >= 128 && first < 192) dwMask = 0xFFFF0000;
			//	else if (first >= 192 && first < 224) dwMask = 0xFFFFFF00;
			//	SendMessage(hIPmask, IPM_SETADDRESS, 0, (LPARAM)dwMask);

			//	CHAR info[256]{};
			//	sprintf(info, "%i", first);
			//	SendMessage(hStaticInfo, WM_SETTEXT, 0, (LPARAM)info);
			//}
		}
			break;

		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;

	case WM_CLOSE: EndDialog(hwnd, 0); break;
	}

	return FALSE;
}

VOID GetInfo(HWND hwnd)
{
	HWND hIPaddress = GetDlgItem(hwnd, IDC_IPADDRESS);
	HWND hIPmask = GetDlgItem(hwnd, IDC_IPMASK);
	HWND hStaticInfo = GetDlgItem(hwnd, IDC_STATIC_INFO);
	
	DWORD dwIPaddress = 0;
	DWORD dwIPmask = 0;
	SendMessage(hIPaddress, IPM_GETADDRESS, 0, (LPARAM)&dwIPaddress);
	SendMessage(hIPmask, IPM_GETADDRESS, 0, (LPARAM)&dwIPmask);

	CONST INT SIZE = 256;
	CHAR szAllInfo[SIZE]{};
	CHAR szInfo[SIZE]{};

	DWORD dwNET_IPaddress = dwIPaddress & dwIPmask;
	CHAR szNET_IPaddress[17]{};
	GetIPBytes(dwNET_IPaddress, szNET_IPaddress);
	sprintf(szInfo, "Network address:\t%s\n", szNET_IPaddress);
	strcat(szAllInfo, szInfo);

	DWORD dwBroadcast = dwIPaddress | ~dwIPmask;
	CHAR szBroadcastAddress[17]{};
	GetIPBytes(dwBroadcast, szBroadcastAddress);
	sprintf(szInfo, "Broadcast address:\t%s\n", szBroadcastAddress);
	strcat(szAllInfo, szInfo);

	HWND hEditPrefix = GetDlgItem(hwnd, IDC_EDIT_PREFIX);
	CONST INT SIZE_PREFIX = 5;
	CHAR sz_prefix[SIZE_PREFIX] = {};
	SendMessage(hEditPrefix, WM_GETTEXT, SIZE_PREFIX, (LPARAM)sz_prefix);
	DWORD dwPrefix = atoi(sz_prefix);
	DWORD dwMaxCountIPaddress = pow(2, (32 - dwPrefix)) - 2;
	if (dwPrefix == 0 || dwPrefix == 32) dwMaxCountIPaddress = 0;
	sprintf(szInfo, "Maximum number IP-addresses:\t%i\n", dwMaxCountIPaddress);
	strcat(szAllInfo, szInfo);

	SendMessage(hStaticInfo, WM_SETTEXT, 0, (LPARAM)szAllInfo);
}

VOID GetIPBytes(DWORD dwIPaddress, CHAR* szIPaddress)
{
	UCHAR bytes[5] = {};
	for (int i = 4 - 1; i >= 0; i--)
	{
		bytes[i] = dwIPaddress & 0xFF;
		dwIPaddress >>= 8;
	}

	//CHAR string[16] = {};
	for (int i = 0; i < 4; i++)
	{
		CHAR byte[4];
		sprintf(byte, "%i", bytes[i]);
		strcat(szIPaddress, byte);
		strcat(szIPaddress, ".");
	}
	*strrchr(szIPaddress, '.') = 0;
}
