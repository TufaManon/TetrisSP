// TetrisSP.cpp: 定义应用程序的入口点。
//

#include "TetrisSP.h"

using namespace std;

int main(int flagc, char* flags[])
{
	try
	{
		Game::GetGame()->Run();
	}
	catch(const GameError& e)
	{
		e.PrintError();
	}
	return 0;
} 