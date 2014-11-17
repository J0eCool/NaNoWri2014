#pragma once

#include <Nano/Engine/Engine.h>

class CameraFollow : public Component {
private:
	std::string _followName;
	Transform* _followTransform;
	float _leftBound;
	float _rightBound;
	float _upBound;
	float _downBound;

public:
	//$$_followName:String|_leftBound:Float|_rightBound:Float|_upBound:Float|_downBound:Float
	void Load(std::vector<std::string> const& args) override;
	void Start() override;
	void Update(float dt) override;
};
