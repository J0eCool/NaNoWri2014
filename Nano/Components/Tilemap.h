#pragma once

#include <Nano/Engine/Engine.h>

class Tilemap : public Component {
private:
	String _file;

public:
	//$$_file:String
	void LoadArg(String const& key, String const& val) override;

	void Start() override;
};
