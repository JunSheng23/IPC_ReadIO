#pragma once
#include "windows.h"
#include "stdio.h"
#include <iostream>  
#include <vector>
#include <bitset>
#include <typeinfo>
#include <iostream>
#define index_port	0x4E //SIO R/W INDEX PORT ADDRESS
#define data_port	0x4F //SIO R/W DADT PORT ADDRESS
typedef void(__stdcall* lpOut32)(short, short);
typedef short(__stdcall* lpInp32)(short);
typedef BOOL(__stdcall* lpIsInpOutDriverOpen)(void);
typedef BOOL(__stdcall* lpIsXP64Bit)(void);

using namespace std;

class IoState
{
public:
	enum class InputPin {
		GP74 = 0,
		GP75,
		GP76,
		GP77,
	};
	enum class OutputPin {
		GP80 = 0,
		GP81,
		GP82,
		GP83,
	};
	IoState();
	~IoState();
	bool getDIState(InputPin pin);
	bool getDOState(OutputPin pin);
	void setDOState(OutputPin pin,bool state);
	bool initialize(string file_name);

private:
	//Some global function pointers (messy but fine for an example)
	lpOut32 gfpOut32;
	lpInp32 gfpInp32;
	lpIsInpOutDriverOpen gfpIsInpOutDriverOpen;
	lpIsXP64Bit gfpIsXP64Bit;
	short  uIO;
	void Enter_SIO();
	void Exit_SIO();
	bool DriverLoad;
	bool CheckDriverOpen(string file_name);
	HINSTANCE hInpOutDll;
};
