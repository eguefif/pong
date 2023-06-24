#include "pong.h"

Pong::Pong()
{}


void Pong::onRun()
{
	int type = EXIT;

	while (true)
	{
		type = onMenu();
		if (type == EXIT)
			break;
		onCreateGame(type);
	}
	onCleanup();
}

int Pong::onMenu()
{
	return 1;
}

void Pong::onCreateGame(int type)
{
}

void Pong::onInit()
{
}

void Pong::onCleanup()
{
}
