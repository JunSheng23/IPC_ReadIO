#include"IoState.h"

IoState::IoState()
{
}

IoState::~IoState()
{
	Exit_SIO();
	FreeLibrary(hInpOutDll);
}

bool IoState::getDIState(InputPin pin)
{
	Enter_SIO();
	int data_rw8;
	gfpOut32(index_port, 0x82); // set DI register
	data_rw8 = gfpInp32(data_port); // get DI state
	bitset<8> In_state(data_rw8);
	cout << "Input_bin= " << In_state << endl;
	switch (pin)
	{
	case InputPin::GP74:
		if ((data_rw8 & 0x10) == 0x10) {
			//GP74=high
			//cout << "GP74 Status ON" << endl;
			return true;
		}
		else if ((data_rw8 & 0x10) != 0x10)
		{
			//cout << "GP74 Status OFF" << endl;
			return false;
		}

		break;
	case InputPin::GP75:
		if ((data_rw8 & 0x20) == 0x20) {
			//GP75=high
			//cout << "GP75 Status ON" << endl;
			return true;
		}
		else if ((data_rw8 & 0x20) != 0x20)
		{
			//cout << "GP75 Status OFF" << endl;
			return false;
		}
		break;
	case InputPin::GP76:
		if ((data_rw8 & 0x40) == 0x40) {
			//GP76=high
			//cout << "GP76 Status ON" << endl;
			return true;
		}
		else if ((data_rw8 & 0x40) != 0x40)
		{
			//cout << "GP76 Status OFF" << endl;
			return false;
		}
		break;
	case InputPin::GP77:
		if ((data_rw8 & 0x80) == 0x80) {
			//GP77=high
			//cout << "GP77 Status ON" << endl;
			return true;
		}
		else if ((data_rw8 & 0x80) != 0x80)
		{
			//cout << "GP77 Status OFF" << endl;
			return false;
		}
		break;
	default:
		return false;
		break;
	}
	Exit_SIO();
}

bool IoState::getDOState(OutputPin pin)
{
	Enter_SIO();
	int data_rw8;
	gfpOut32(index_port, 0x89); //set DO register
	data_rw8 = gfpInp32(data_port); // get DO state
	bitset<8> On_state(data_rw8);
	cout << "Output_bin= " << On_state << endl;
	switch (pin)
	{
	case OutputPin::GP80:
		if ((data_rw8 & 0x01) == 0x01) {
			//GP80=high
			//cout << "GP80 Status ON" << endl;
			return true;
		}
		else if ((data_rw8 & 0x01) != 0x01)
		{
			//cout << "GP80 Status OFF" << endl;
			return false;
		}
		break;
	case OutputPin::GP81:
		if ((data_rw8 & 0x02) == 0x02) {
			//GP81=high
			//cout << "GP81 Status ON" << endl;
			return true;
		}
		else if ((data_rw8 & 0x02) != 0x02)
		{
			//cout << "GP81 Status OFF" << endl;
			return false;
		}
		break;
	case OutputPin::GP82:
		if ((data_rw8 & 0x04) == 0x04) {
			//GP82=high
			//cout << "GP82 Status ON" << endl;
			return true;
		}
		else if ((data_rw8 & 0x04) != 0x04)
		{
			//cout << "GP82 Status OFF" << endl;
			return false;
		}
		break;
	case OutputPin::GP83:
		if ((data_rw8 & 0x08) == 0x08) {
			//GP83=high
			//cout << "GP83 Status ON" << endl;
			return true;
		}
		else if ((data_rw8 & 0x08) != 0x08)
		{
			//cout << "GP83 Status OFF" << endl;
			return false;
		}
		break;
	default:
		break;
	}
	Exit_SIO();
}

void IoState::setDOState(OutputPin pin, bool state)
{
	Enter_SIO();
	int data_rw8;
	gfpOut32(index_port, 0x89); //set DO register
	data_rw8 = gfpInp32(data_port); // get DO state
	bitset<8> On_state(data_rw8);
	cout << "Output_bin= " << On_state << endl;
	switch (pin)
	{
	case OutputPin::GP80:
		if (state == true){
			data_rw8 = data_rw8 | 0x01; 
			gfpOut32(data_port, data_rw8);
		}
		else{
			data_rw8 = data_rw8 & 0xFE;
			gfpOut32(data_port, data_rw8);
		}
		break;
	case OutputPin::GP81:
		if (state == true){
			data_rw8 = data_rw8 | 0x02;
			gfpOut32(data_port, data_rw8);
		}
		else
		{
			data_rw8 = data_rw8 & 0xFD; 
			gfpOut32(data_port, data_rw8); 
		}
		break;
	case OutputPin::GP82:
		if (state == true)
		{
			data_rw8 = data_rw8 | 0x04; 
			gfpOut32(data_port, data_rw8); 
		}
		else
		{
			data_rw8 = data_rw8 & 0xFB;
			gfpOut32(data_port, data_rw8); 
		}
		break;
	case OutputPin::GP83:
		if (state == true)
		{
			data_rw8 = data_rw8 | 0x08;
			gfpOut32(data_port, data_rw8); 
		}
		else
		{
			data_rw8 = data_rw8 & 0xF7; 
			gfpOut32(data_port, data_rw8); 
		}
		break;
	default:
		break;
	}
	Exit_SIO();
}

bool IoState::initialize(string file_name)
{
	DriverLoad = CheckDriverOpen(file_name);
	return DriverLoad;
}

void IoState::Enter_SIO()
{
	//enable configutation entry key 0x87 tone index port(0x4E)
	gfpOut32(index_port, 0x87);//Enter SIO entry key
	Sleep(1);
	gfpOut32(index_port, 0x87);//Enter SIO entry key
	gfpOut32(index_port, 0x07);//Select Logic Device Number Register (LDN7)
	gfpOut32(data_port, 0x06);//Select GPIO device configuration registers.
}

void IoState::Exit_SIO()
{
	gfpOut32(index_port, 0xAA);//EXIT SIO exit key
}

bool IoState::CheckDriverOpen(string file_name)
{
	hInpOutDll = LoadLibrary(file_name.c_str());	//The 32bit DLL. If we are building x64 C++ 
	if (hInpOutDll != NULL)
	{
		gfpOut32 = (lpOut32)GetProcAddress(hInpOutDll, "Out32");
		gfpInp32 = (lpInp32)GetProcAddress(hInpOutDll, "Inp32");
		gfpIsInpOutDriverOpen = (lpIsInpOutDriverOpen)GetProcAddress(hInpOutDll, "IsInpOutDriverOpen");
		gfpIsXP64Bit = (lpIsXP64Bit)GetProcAddress(hInpOutDll, "IsXP64Bit");
		if (gfpIsInpOutDriverOpen)
		{
			printf("The InpOut DLL is loaded!\n");
			return true;
		}
	}
	else
	{
		printf("Unable to load InpOut DLL!\n");
		return false;
	}

}

