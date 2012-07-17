#include "SSMain.h"

namespace Sandstorms
{
	SSMain::SSMain(void)
		: player("../resources/player/idle.png", 1337, 512 / 2, 1024 - 50)
	{
	}
	
	
	SSMain::~SSMain(void)
	{
	}

	void SSMain::init()
	{
		// Call the Graphics init method
		theEngine.Graphics->init();
		
		// Create a player
		player.initAttributes(1337);

		// Create the background
	}

	void SSMain::run()
	{
		// Create a bool for whether or not the game is running
		bool running = true;

		// WHILE running
		while(running)
		{
			// Call processEvents()
			running = processEvents();

			// Call processLogic()
			processLogic();

			// Call render()
			render();
		}
	}

	void SSMain::shutDown()
	{
		// Call Graphics shutDown method
		theEngine.Graphics->shutDown();
	}

	bool SSMain::processEvents()
	{
		// Update the Input
		bool stillGoing = theEngine.Input->update();

		// IF 'D' is down
		if(theEngine.Input->keyDown(TGA::Key::key_D))
		{
			// Move right
			player.increaseAccels(3, 0);
		}

		// IF 'A' is down
		if(theEngine.Input->keyDown(TGA::Key::key_A))
		{
			// Move left
			player.increaseAccels(-3, 0);
		}

		// IF 'W' OR 'SPACE' is down AND it's been long enough
		if(theEngine.Input->keyDown(TGA::Key::key_W) || 
			theEngine.Input->keyDown(TGA::Key::key_SPACE))
		{
			player.jump();
		}

		return stillGoing;
	}

	void SSMain::processLogic()
	{
		// Update the AnimationManager
		theEngine.Animations->updateAll();

		// Update the Player
		player.updatePosition();
	}

	void SSMain::render()
	{
		// Draw the background
		// Draw all Animations
		player.draw();

		// Call Graphics Swap Buffers
		theEngine.Graphics->swapBuffers();
	}
}
