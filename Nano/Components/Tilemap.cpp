#include "Tilemap.h"

#include "Enemy/Enemy.h"

void Tilemap::spawnEnemySpawner(Vec2 pos, String const& enemyName) {
	Entity *enemy = LoadPrefabFromFile("../Assets/Prefabs/Spawner.prefab");
	Transform *trans = enemy->GetTransform();
	pos.y -= trans->size.y;
	trans->pos = pos;
	enemy->GetComponent<EnemySpawner>()->LoadArg("spawnName", enemyName);
	GetEntitySystem()->AddEntity(enemy);
}

void Tilemap::Start() {
	auto lines = ReadLinesFromFile("../Assets/Tilemaps/" + _file);
	Vec2 topLeft({ FLT_MAX, FLT_MAX });
	Vec2 botRight({ -FLT_MAX, -FLT_MAX });
	Transform *transform = GetTransform();
	Entity *tilePrefab = LoadPrefabFromFile("../Assets/Prefabs/Tile.prefab");
	Vec2 tileSize = tilePrefab->GetTransform()->size;

	for (unsigned y = 0; y < lines.size(); ++y) {
		Vec2 offset(0.0f, y * tileSize.y);
		for (unsigned x = 0; x < lines[y].length(); ++x) {
			offset.x = x * tileSize.x;
			Vec2 pos = transform->pos + offset;
			auto c = lines[y][x];
			if (c == '#') {
				Entity *tile = new Entity(*tilePrefab);
				Transform *tTrans = tile->GetTransform();
				tTrans->pos = pos;
				GetEntitySystem()->AddEntity(tile);

				topLeft = topLeft.Min(tTrans->pos);
				botRight = botRight.Max(tTrans->pos + tileSize);
			}
			else if (c == '@') {
				Entity *player = GetEntitySystem()->FindEntity("Player");
				Transform *pTrans = player->GetTransform();
				pos.y += tileSize.y - pTrans->size.y;
				pTrans->pos = pos;
			}
			else if (c == 'S') {
				pos.y += tileSize.y; 
				spawnEnemySpawner(pos, "Slime");
			}
			else if (c == 'E') {
				pos.y += tileSize.y;
				spawnEnemySpawner(pos, "Eye");
			}
			else if (c == 'B') {
				pos.y += tileSize.y;
				spawnEnemySpawner(pos, "Boss");
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
