#include "Program.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	setlocale(LC_CTYPE, "Polish");
	Program program("Symulator ruchu drogowego", 1400, 800);

	while (program.isRunning())
	{
		//Render
		program.update();
		//Draw
		program.render();
	}
	return 0;
}