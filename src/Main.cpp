#include "Main.h"

int main(int argc, char *argv[])
{
	SSMain app;

	app.init();
	app.run();
	app.shutDown();

	exit(0);
}