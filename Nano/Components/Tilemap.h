#pragma once

#include <Nano/Engine/Engine.h>

class Tilemap : public Component {
private:
	String _file;
	Rect _bounds;

	void spawnEnemySpawner(Vec2 pos, String const& enemyName);

public:
	//$$_file:String
	void LoadArg(String const& key, String const& val) override;

	void Start() override;
	Rect GetBounds() const;
};
