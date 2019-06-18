#pragma once
#include "GameObject.h"
#include "CollisionManager.h"

class Level : public GameObject
{
public:
	Level();
	~Level();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);
private:
	CollisionManager* _collisionManager;
};

