#include <Nano/Components/Components.h>
#include <Nano/Engine/Engine.h>

void CameraFollow::Load(std::vector<std::string> const& args) {
	_followName = ParseString(args[0]);
	_leftBound = ParseFloat(args[1]);
	_rightBound = ParseFloat(args[2]);
	_upBound = ParseFloat(args[3]);
	_downBound = ParseFloat(args[4]);
}

void Renderer::Load(std::vector<std::string> const& args) {
	_color = ParseColor(args[0]);
}

void SpriteRenderer::Load(std::vector<std::string> const& args) {
	_spriteName = ParseString(args[0]);
}

void TextRenderer::Load(std::vector<std::string> const& args) {
	_fontName = ParseString(args[0]);
	_fontSize = ParseInt(args[1]);
}

void SpinningSigma::Load(std::vector<std::string> const& args) {
	_speed = ParseFloat(args[0]);
	_color = ParseFloat(args[1]);
}

void Transform::Load(std::vector<std::string> const& args) {
	pos = ParseVec2(args[0]);
	size = ParseVec2(args[1]);
}
