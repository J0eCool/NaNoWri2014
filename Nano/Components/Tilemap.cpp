#include "Tilemap.h"

void Tilemap::Start() {
	auto lines = ReadLinesFromFile("../Assets/Tilemaps/" + _file);
	Transform *transform = GetTransform();
	for (unsigned y = 0; y < lines.size(); ++y) {
		for (unsigned x = 0; x < lines[y].length(); ++x) {
			if (lines[y][x] == '1') {
				Entity *tile = LoadPrefabFromFile("../Assets/Prefabs/Tile.prefab");
				Vec2 offset = tile->GetTransform()->size.Mult({ (float)x, (float)y });
				tile->GetTransform()->pos = transform->pos + offset;
				GetEntitySystem()->AddEntity(tile);
			}
		}
	}
}
