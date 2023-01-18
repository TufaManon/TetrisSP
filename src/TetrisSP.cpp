// TetrisSP.cpp: 定义应用程序的入口点。
//

#include "TetrisSP.h"
#include "game.h"

using namespace std;

int main(int flagc, char* flags[])
{
	Game::GetGame()->Run();

	return 0;
} 