#include "SSMain.h"

namespace Sandstorms
{
	SSMain::SSMain(void)
	{
	}
	
	
	SSMain::~SSMain(void)
	{
	}

	void SSMain::init()
	{
		// Call the Graphics init method

		// Create a player

		// Create the background
	}

	void SSMain::run()
	{
		// Create a bool for whether or not the game is running

		// WHILE running
			// Call processEvents()
			// Call processLogic()
			// Call render()
	}

	void SSMain::shutDown()
	{
		// Call Graphics shutDown method
	}

	void SSMain::processEvents()
	{
		// Update the Input

		// IF 'D' is down
			// Move right
		
		// IF 'A' is down
			// Move left

		// IF 'W' OR 'SPACE' is down AND it's been long enough
			// IF the player is already in mid-jump and hasn't double-jumped
				// Jump (again)
				// Set player double-jump
			// ELSEIF player is not in mid-air
				// Jump
				// Set player jump
	}

	void SSMain::processLogic()
	{
		// Update the AnimationManager
		// Update the Player
	}

	void SSMain::render()
	{
		// Draw the background
		// Draw all Animations
		// Call Graphics Swap Buffers
	}

}
