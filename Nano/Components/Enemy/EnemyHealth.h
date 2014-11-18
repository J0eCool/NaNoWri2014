#pragma once

#include <Nano/Engine/Engine.h>

class EnemyHealth : public Component {
private:
	int _maxHealth;
	int _health;

public:
	//$$_maxHealth:Int
	void LoadArg(std::string const& key, std::string const& val) override;

	void Start() override;
	void HandleMessage(std::string const& message, void *data) override;
};
