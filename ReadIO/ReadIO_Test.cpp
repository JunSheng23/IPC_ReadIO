#include"IoState.h"
using namespace std;

int main(int argc, char* argv[])
{
	IoState IOobj;
	bool init_status;
	init_status=IOobj.initialize("inpoutx64.dll");
	cout << "Driver load: " << init_status << endl;
	int io_name = 0;
	bool status;
	do
	{
	
		cout << "get digital input state--------------------------------------" << endl;
		status = IOobj.getDIState(IoState::InputPin::GP74);
		cout << "GP74: " << status << endl;
		cout << "--------------------------------------" << endl;
		status = IOobj.getDIState(IoState::InputPin::GP75);
		cout << "GP74: " << status << endl;
		cout << "--------------------------------------" << endl;
		status = IOobj.getDIState(IoState::InputPin::GP76);
		cout << "GP74: " << status << endl;
		cout << "--------------------------------------" << endl;
		status = IOobj.getDIState(IoState::InputPin::GP77);
		cout << "GP74: " << status << endl;
		cout << "--------------------------------------" << endl;
		Sleep(5000);
		cout << "get digital output state--------------------------------------" << endl;
		status = IOobj.getDOState(IoState::OutputPin::GP80);
		cout << "GP80: " << status << endl;
		cout << "--------------------------------------" << endl;
		status = IOobj.getDOState(IoState::OutputPin::GP81);
		cout << "GP81: " << status << endl;
		cout << "--------------------------------------" << endl;
		status = IOobj.getDOState(IoState::OutputPin::GP82);
		cout << "GP82: " << status << endl;
		cout << "--------------------------------------" << endl;
		status = IOobj.getDOState(IoState::OutputPin::GP83);
		cout << "GP83: " << status << endl;
		cout << "--------------------------------------" << endl;
		Sleep(5000);
		cout << "set output on--------------------------------------" << endl;
		IOobj.setDOState(IoState::OutputPin::GP80, true);
		IOobj.setDOState(IoState::OutputPin::GP81, true);
		IOobj.setDOState(IoState::OutputPin::GP82, true);
		IOobj.setDOState(IoState::OutputPin::GP83, true);
		cout << "--------------------------------------" << endl;
		Sleep(5000);
		cout << "get digital output state--------------------------------------" << endl;
		status = IOobj.getDOState(IoState::OutputPin::GP80);
		cout << "GP80: " << status << endl;
		cout << "--------------------------------------" << endl;
		status = IOobj.getDOState(IoState::OutputPin::GP81);
		cout << "GP81: " << status << endl;
		cout << "--------------------------------------" << endl;
		status = IOobj.getDOState(IoState::OutputPin::GP82);
		cout << "GP82: " << status << endl;
		cout << "--------------------------------------" << endl;
		status = IOobj.getDOState(IoState::OutputPin::GP83);
		cout << "GP83: " << status << endl;
		cout << "--------------------------------------" << endl;
		Sleep(5000);
		cout << "set output off--------------------------------------" << endl;
		IOobj.setDOState(IoState::OutputPin::GP80, false);
		IOobj.setDOState(IoState::OutputPin::GP81, false);
		IOobj.setDOState(IoState::OutputPin::GP82, false);
		IOobj.setDOState(IoState::OutputPin::GP83, false);
		cout << "--------------------------------------" << endl;
		Sleep(5000);
		cout << "get digital output state--------------------------------------" << endl;
		status = IOobj.getDOState(IoState::OutputPin::GP80);
		cout << "GP80: " << status << endl;
		cout << "--------------------------------------" << endl;
		status = IOobj.getDOState(IoState::OutputPin::GP81);
		cout << "GP81: " << status << endl;
		cout << "--------------------------------------" << endl;
		status = IOobj.getDOState(IoState::OutputPin::GP82);
		cout << "GP82: " << status << endl;
		cout << "--------------------------------------" << endl;
		status = IOobj.getDOState(IoState::OutputPin::GP83);
		cout << "GP83: " << status << endl;
		cout << "--------------------------------------" << endl;
		Sleep(5000);
	} while (io_name != 99);


}
