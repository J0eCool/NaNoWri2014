#include "Tilemap.h"

void Tilemap::Start() {
	auto lines = ReadLinesFromFile("../Assets/Tilemaps/" + _file);
	Vec2 topLeft({ FLT_MAX, FLT_MAX });
	Vec2 botRight({ -FLT_MAX, -FLT_MAX });
	Transform *transform = GetTransform();
	Entity *tilePrefab = LoadPrefabFromFile("../Assets/Prefabs/Tile.prefab");
	Vec2 tileSize = tilePrefab->GetTransform()->size;

	for (unsigned y = 0; y < lines.size(); ++y) {
		for (unsigned x = 0; x < lines[y].length(); ++x) {
			auto c = lines[y][x];
			if (c == '#') {
				Entity *tile = new Entity(*tilePrefab);
				Transform *tTrans = tile->GetTransform();
				Vec2 offset = tileSize.Mult({ (float)x, (float)y });
				tTrans->pos = transform->pos + offset;
				GetEntitySystem()->AddEntity(tile);

				topLeft = topLeft.Min(tTrans->pos);
				botRight = botRight.Max(tTrans->pos + tileSize);
			}
			else if (c == '@') {
				//Entity *player = GetEntitySystem()->FindEntity("Player");
				//player->GetTransform
			}
		}
	}

	delete tilePrefab;

	_bounds.x = topLeft.x;
	_bounds.y = topLeft.y;
	_bounds.w = botRight.x - topLeft.x;
	_bounds.h = botRight.y - topLeft.y;
}

Rect Tilemap::GetBounds() const {
	return _bounds;
}
