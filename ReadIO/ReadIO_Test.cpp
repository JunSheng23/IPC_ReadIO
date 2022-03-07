#include"IOState.h"
using namespace std;

int main(int argc, char* argv[])
{
	IOState IOobj;
	int io_name = 0;
	do
	{
		//IOobj.Enter_SIO();
		for (int i = 1; i < 5; i++)
		{
			IOobj.Check_DI_State(i);
			cout << "--------------------------------------" << endl;
		}
		for (int i = 1; i < 5; i++)
		{
			IOobj.Check_DO_State(i);
			cout << "--------------------------------------" << endl;
		}
		//IOobj.Exit_SIO();
		Sleep(1000);
	} while (io_name != 99);


}
