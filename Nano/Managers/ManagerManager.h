#pragma once

#include "Singleton.h"

class ManagerManager : public Singleton<ManagerManager> {
public:
	void Init();
	void Deinit();
	void Update(float dt);
};
