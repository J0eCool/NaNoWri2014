#pragma once

#include <Nano/Engine/Engine.h>

class Bullet : public Component {
public:
	class Container {
	private:
		Set<Bullet *> _bullets;
		int _maxSize;

	public:
		Container(int maxSize);

		bool IsFull() const;
		void AddBullet(Bullet *bullet);

		friend Bullet;
	};

private:
	float _speed;
	int _damage;
	Vec2 _vel;
	Container *_container;

	void setContainer(Container *container);

public:
	//$$_speed:Float|_damage:Int
	void LoadArg(String const& key, String const& val) override;

	void Update(float dt) override;

	void SetDir(Vec2 const& dir);
};
