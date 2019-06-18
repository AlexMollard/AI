#pragma once
#include "Collider.h"
#include "GameObject.h"
#include "Renderer2D.h"
#include <vector>

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

	void AddObject(GameObject* object);
	void RemoveObject();
	GameObject* GetObject();
	bool loop = true;

private:
	std::vector<GameObject*> _ObjectList;
};

