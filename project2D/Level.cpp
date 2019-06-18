#include "Level.h"

Level::Level()
{
	SetName("Level");
	_Score = 0;
	_collisionManager = new CollisionManager();

	// _Tank = new Tank();
	// _Tank->SetParent(this);
	// _Tank->SetPosition(Vector2(500,500));
	// _Tank->UpDateGlobalTransform();
	// _collisionManager->AddObject(_Tank);
}

Level::~Level()
{
	delete _collisionManager;
	_collisionManager = nullptr;
}

void Level::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	_collisionManager->Update(deltaTime);
}

void Level::Draw(aie::Renderer2D* renderer)
{
	GameObject::Draw(renderer);
	_collisionManager->Draw(renderer);
}