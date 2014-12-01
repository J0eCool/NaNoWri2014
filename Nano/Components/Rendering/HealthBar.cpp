#include "HealthBar.h"

#include <Nano/Managers/AssetManager.h>
#include <Nano/NanoEntityConfig.h>


void HealthBar::Init() {
	auto config = static_cast<NanoEntityConfig*>(_entity->GetEntitySystem()->GetConfig());
	_segment = AssetManager::GetInstance()->LoadSprite("MeterSegment", config->renderer);
	_endcap = AssetManager::GetInstance()->LoadSprite("MeterCap", config->renderer);
}


void HealthBar::Draw() {
	if (!_curFunc || !_maxFunc) {
		return;
	}

	Transform *transform = _entity->GetTransform();
	SDL_Rect rect = transform->GetRectWithOffset({ 0, 0 });
	SDL_Color color = _colorFunc ? _colorFunc() : _color;
	_endcap.color = color;
	_endcap.DrawAt(rect);

	rect.h = rect.h * _segment.GetRect().h / _endcap.GetRect().h;
	int curCount = _curFunc();
	int maxCount = _maxFunc();
	SDL_Color black{ 0, 0, 0, 0xff };
	for (int i = 0; i < maxCount; ++i) {
		rect.y -= rect.h;
		_segment.color = i < curCount ? color : black;
		_segment.DrawAt(rect);
	}
}

void HealthBar::SetFunctions(HealthFunc cur, HealthFunc max, HealthColorFunc color) {
	_curFunc = cur;
	_maxFunc = max;
	_colorFunc = color;
}
