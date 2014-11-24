#pragma once

#include <Nano/Engine/Engine.h>

class Tilemap;

class CameraFollow : public Component {
private:
	String _followName;
	String _boundsName;
	Transform *_followTransform;
	Tilemap *_boundsTilemap;

public:
	//$$_followName:String|_boundsName:String
	void LoadArg(String const& key, String const& val) override;
	void Start() override;
	void Update(float dt) override;
};
