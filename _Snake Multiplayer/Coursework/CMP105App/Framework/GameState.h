// Game State Class
// Simple game state controller. enum lists possible game states (can be modified), tracks and updates the current state
// @author Paul Robertson

#pragma once

// Possible states. This enum can be modified to add additional states as required.
enum class State { MENU, MENU_SETTINGS, MENU_CONTROLS, MENU_AUDIO, INVENTORY, LEVEL, PAUSE, CREDITS, TRANSITION, RESET, DEATH };

class GameState
{
public:
	// Set the current state
	void setCurrentState(State s);
	// Returns the current state.
	State getCurrentState();

protected:
	State currentState;
};