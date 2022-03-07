#pragma once
#include "windows.h"
#include "stdio.h"
#include <iostream>  
#include <vector>
#include <bitset>
#include <typeinfo>
#define index_port	0x4E //SIO R/W INDEX PORT ADDRESS
#define data_port	0x4F //SIO R/W DADT PORT ADDRESS
typedef void(__stdcall* lpOut32)(short, short);
typedef short(__stdcall* lpInp32)(short);
typedef BOOL(__stdcall* lpIsInpOutDriverOpen)(void);
typedef BOOL(__stdcall* lpIsXP64Bit)(void);

using namespace std;

class IOState
{
public:
	IOState();
	~IOState();
	void Check_DI_State(int io_name);
	void Check_DO_State(int io_name);
	void Enter_SIO();
	void Exit_SIO();
private:
	//Some global function pointers (messy but fine for an example)
	lpOut32 gfpOut32;
	lpInp32 gfpInp32;
	lpIsInpOutDriverOpen gfpIsInpOutDriverOpen;
	lpIsXP64Bit gfpIsXP64Bit;
	short  uIO;

	bool DriverLoad;
	bool CheckDriverOpen();
	HINSTANCE hInpOutDll;

};

IOState::IOState()
{
	DriverLoad=CheckDriverOpen();
	cout << "Driver load: " << DriverLoad << endl;
	
}

IOState::~IOState()
{
	Exit_SIO();
	FreeLibrary(hInpOutDll);
}

void IOState::Check_DI_State(int io_name)
{
	Enter_SIO();
	int data_rw8;
	gfpOut32(index_port, 0x82); // set DI register
	data_rw8 = gfpInp32(data_port); // get DI state
	bitset<8> In_state(data_rw8);
	cout << "Input_bin= " << In_state << endl;
	switch (io_name)
	{
	case 1:
		if ((data_rw8 & 0x10) == 0x10) {
			//GP74=high
			cout << "GP74 Status ON" << endl;
		}
		else if ((data_rw8 & 0x10) != 0x10)
		{
			cout << "GP74 Status OFF" << endl;
		}
		
		break;
	case 2:
		if ((data_rw8 & 0x20) == 0x20) {
			//GP75=high
			cout << "GP75 Status ON" << endl;
		}
		else if ((data_rw8 & 0x20) != 0x20)
		{
			cout << "GP75 Status OFF" << endl;
		}
		break;
	case 3:
		if ((data_rw8 & 0x40) == 0x40) {
			//GP76=high
			cout << "GP76 Status ON" << endl;
		}
		else if ((data_rw8 & 0x40) != 0x40)
		{
			cout << "GP76 Status OFF" << endl;
		}
		break;
	case 4:
		if ((data_rw8 & 0x80) == 0x80) {
			//GP77=high
			cout << "GP77 Status ON" << endl;
		}
		else if ((data_rw8 & 0x80) != 0x80)
		{
			cout << "GP77 Status OFF" << endl;
		}
		break;
	default:
		break;
	}
	Exit_SIO();
}

void IOState::Check_DO_State(int io_name)
{
	Enter_SIO();
	int data_rw8;
	gfpOut32(index_port, 0x89); //set DO register
	data_rw8 = gfpInp32(data_port); // get DO state
	bitset<8> On_state(data_rw8);
	cout << "Output_bin= " << On_state << endl;
	switch (io_name)
	{
	case 1:
		if ((data_rw8 & 0x01) == 0x01) {
			//GP74=high
			cout << "GP80 Status ON" << endl;
		}
		else if ((data_rw8 & 0x01) != 0x01)
		{
			cout << "GP80 Status OFF" << endl;
		}
		break;
	case 2:
		if ((data_rw8 & 0x02) == 0x02) {
			//GP75=high
			cout << "GP81 Status ON" << endl;
		}
		else if ((data_rw8 & 0x02) != 0x02)
		{
			cout << "GP81 Status OFF" << endl;
		}
		break;
	case 3:
		if ((data_rw8 & 0x04) == 0x04) {
			//GP76=high
			cout << "GP82 Status ON" << endl;
		}
		else if ((data_rw8 & 0x04) != 0x04)
		{
			cout << "GP82 Status OFF" << endl;
		}
		break;
	case 4:
		if ((data_rw8 & 0x08) == 0x08) {
			//GP77=high
			cout << "GP83 Status ON" << endl;
		}
		else if ((data_rw8 & 0x08) != 0x08)
		{
			cout << "GP83 Status OFF" << endl;
		}
		break;
	default:
		break;
	}
	Exit_SIO();
}

inline void IOState::Enter_SIO()
{
	//enable configutation entry key 0x87 tone index port(0x4E)
	gfpOut32(index_port, 0x87);//Enter SIO entry key
	Sleep(1);
	gfpOut32(index_port, 0x87);//Enter SIO entry key
	gfpOut32(index_port, 0x07);//Select Logic Device Number Register (LDN7)
	gfpOut32(data_port, 0x06);//Select GPIO device configuration registers.
}

inline void IOState::Exit_SIO()
{
	gfpOut32(index_port, 0xAA);//EXIT SIO exit key
}

bool IOState::CheckDriverOpen()
{
	hInpOutDll = LoadLibrary("InpOut32.DLL");	//The 32bit DLL. If we are building x64 C++ 
	if (hInpOutDll != NULL)
	{
		gfpOut32 = (lpOut32)GetProcAddress(hInpOutDll, "Out32");
		gfpInp32 = (lpInp32)GetProcAddress(hInpOutDll, "Inp32");
		gfpIsInpOutDriverOpen = (lpIsInpOutDriverOpen)GetProcAddress(hInpOutDll, "IsInpOutDriverOpen");
		gfpIsXP64Bit = (lpIsXP64Bit)GetProcAddress(hInpOutDll, "IsXP64Bit");
		if (gfpIsInpOutDriverOpen)
		{
			printf("The InpOut32 DLL is loaded!\n");
			return true;
		}
	}
	else
	{
		printf("Unable to load InpOut32 DLL!\n");
		return false;
	}

}
