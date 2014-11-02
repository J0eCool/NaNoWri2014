#pragma once

#include "Singleton.h"

enum InputType {
	IN_Quit,

	IN_NumTypes // must be last
};

class InputManager : public Singleton<InputManager> {
//class InputManager {
private:
	bool _downInputs[IN_NumTypes];

	//static InputManager _ins;

public:
	//static InputManager *getInstance() { return &_ins; }
	void Update();
	bool IsDown(InputType input);
};
