#include <Nano/Components/Components.h>
#include <Nano/Engine/Engine.h>

void Collider::LoadArg(std::string const& key, std::string const& val) {
	if (key == "layerMask") { _layerMask = ParseInt(val); }
	else { Log("ERROR: Collider: Invalid argument: Key=", key, ", Val=", val); }
}

void Bullet::LoadArg(std::string const& key, std::string const& val) {
	if (key == "vel") { _vel = ParseVec2(val); }
	else { Log("ERROR: Bullet: Invalid argument: Key=", key, ", Val=", val); }
}

void CameraFollow::LoadArg(std::string const& key, std::string const& val) {
	if (key == "followName") { _followName = ParseString(val); }
	else if (key == "leftBound") { _leftBound = ParseFloat(val); }
	else if (key == "rightBound") { _rightBound = ParseFloat(val); }
	else if (key == "upBound") { _upBound = ParseFloat(val); }
	else if (key == "downBound") { _downBound = ParseFloat(val); }
	else { Log("ERROR: CameraFollow: Invalid argument: Key=", key, ", Val=", val); }
}

void Renderer::LoadArg(std::string const& key, std::string const& val) {
	if (key == "color") { _color = ParseColor(val); }
	else { Log("ERROR: Renderer: Invalid argument: Key=", key, ", Val=", val); }
}

void SpriteRenderer::LoadArg(std::string const& key, std::string const& val) {
	if (key == "spriteName") { _spriteName = ParseString(val); }
	else { Log("ERROR: SpriteRenderer: Invalid argument: Key=", key, ", Val=", val); }
}

void TextRenderer::LoadArg(std::string const& key, std::string const& val) {
	if (key == "fontName") { _fontName = ParseString(val); }
	else if (key == "fontSize") { _fontSize = ParseInt(val); }
	else { Log("ERROR: TextRenderer: Invalid argument: Key=", key, ", Val=", val); }
}

void SpinningSigma::LoadArg(std::string const& key, std::string const& val) {
	if (key == "speed") { _speed = ParseFloat(val); }
	else if (key == "color") { _color = ParseFloat(val); }
	else { Log("ERROR: SpinningSigma: Invalid argument: Key=", key, ", Val=", val); }
}

void Transform::LoadArg(std::string const& key, std::string const& val) {
	if (key == "pos") { pos = ParseVec2(val); }
	else if (key == "size") { size = ParseVec2(val); }
	else { Log("ERROR: Transform: Invalid argument: Key=", key, ", Val=", val); }
}
