#include <Nano/Components/Components.h>
#include <Nano/Engine/Engine.h>

void EnemyHealth::LoadArg(std::string const& key, std::string const& val) {
	if (key == "maxHealth") { _maxHealth = ParseInt(val); }
	else { Log("ERROR: EnemyHealth: Invalid argument: Key=", key, ", Val=", val); }
}

void EnemySpawner::LoadArg(std::string const& key, std::string const& val) {
	if (key == "spawnName") { _spawnName = ParseString(val); }
	else { Log("ERROR: EnemySpawner: Invalid argument: Key=", key, ", Val=", val); }
}

void EnemyWander::LoadArg(std::string const& key, std::string const& val) {
	if (key == "speed") { _speed = ParseFloat(val); }
	else if (key == "dir") { _dir = ParseInt(val); }
	else { Log("ERROR: EnemyWander: Invalid argument: Key=", key, ", Val=", val); }
}

void Collider::LoadArg(std::string const& key, std::string const& val) {
	if (key == "layerMask") { _layerMask = ParseInt(val); }
	else if (key == "trigger") { _trigger = ParseBool(val); }
	else { Log("ERROR: Collider: Invalid argument: Key=", key, ", Val=", val); }
}

void Rigidbody::LoadArg(std::string const& key, std::string const& val) {
	if (key == "layerMask") { _layerMask = ParseInt(val); }
	else { Log("ERROR: Rigidbody: Invalid argument: Key=", key, ", Val=", val); }
}

void Bullet::LoadArg(std::string const& key, std::string const& val) {
	if (key == "layerMask") { _layerMask = ParseInt(val); }
	else if (key == "speed") { _speed = ParseFloat(val); }
	else if (key == "damage") { _damage = ParseInt(val); }
	else { Log("ERROR: Bullet: Invalid argument: Key=", key, ", Val=", val); }
}

void CameraFollow::LoadArg(std::string const& key, std::string const& val) {
	if (key == "followName") { _followName = ParseString(val); }
	else if (key == "boundsName") { _boundsName = ParseString(val); }
	else { Log("ERROR: CameraFollow: Invalid argument: Key=", key, ", Val=", val); }
}

void PlayerController::LoadArg(std::string const& key, std::string const& val) {
	if (key == "speed") { _speed = ParseFloat(val); }
	else if (key == "jumpHeight") { _jumpHeight = ParseFloat(val); }
	else if (key == "shotOffset") { _shotOffset = ParseVec2(val); }
	else { Log("ERROR: PlayerController: Invalid argument: Key=", key, ", Val=", val); }
}

void RemoveWhenOffscreen::LoadArg(std::string const& key, std::string const& val) {
	if (key == "remove") { _remove = ParseBool(val); }
	else { Log("ERROR: RemoveWhenOffscreen: Invalid argument: Key=", key, ", Val=", val); }
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

void Tilemap::LoadArg(std::string const& key, std::string const& val) {
	if (key == "file") { _file = ParseString(val); }
	else { Log("ERROR: Tilemap: Invalid argument: Key=", key, ", Val=", val); }
}

void Transform::LoadArg(std::string const& key, std::string const& val) {
	if (key == "pos") { pos = ParseVec2(val); }
	else if (key == "size") { size = ParseVec2(val); }
	else { Log("ERROR: Transform: Invalid argument: Key=", key, ", Val=", val); }
}
