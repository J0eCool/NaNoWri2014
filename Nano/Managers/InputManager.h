#pragma once

#include "Singleton.h"

enum InputType {
	IT_None,
	IT_Quit,
	IT_Left,
	IT_Right,
	IT_Jump,

	IT_NumTypes // must be last
};

class InputManager : public Singleton<InputManager> {
private:
	enum InputState {
		IS_Up,
		IS_Held,
		IS_Down,
	};

	InputState _inputStates[IT_NumTypes];
	
	void setInputState(InputType type, InputState state);

public:
	void Update();
	bool IsHeld(InputType input);
	bool IsDown(InputType input);
};
