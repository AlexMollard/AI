#pragma once
#include "Matrix3.h"
#include "Vector2.h"
#include "Renderer2D.h"
#include "Texture.h"
#include "Collider.h"
#include <string.h>
#include <vector>

class GameObject
{
public:
	GameObject();
	GameObject(const char* TextureName);
	virtual ~GameObject();

	void UpDateGlobalTransform();

	virtual void Update(float deltaTime);
	virtual void Draw(aie::Renderer2D* renderer);

	virtual void OnCollision(GameObject* OtherObject);

	void SetPosition(Vector2 v2Pos);
	Vector2 GetPosition();

	void SetRotation(float radians);
	float GetRotation();
	float GetLocalRotation();
	bool collided;

	void SetCollided(bool hit);
	bool GetCollided();

	void SetScale(Vector2 v2Scale);
	Vector2 GetScale();

	void SetParent(GameObject* Parent);
	GameObject* GetParent();

	Vector2 _V2ColliderMin;
	Vector2 _V2ColliderMax;

	Collider* GetCollider() { return _Collider; }
	Collider* GetCollider2() { return _Collider2; }
	bool HasCollider2();
	void SetLocalRotation(float newRotation);

	float GetScore();
	void SetScore(float newScore);

	std::string GameObject::GetName();
	void SetName(std::string name);
	std::string _Name;
	float _Score;
protected:

	GameObject* _Parent;
	std::vector<GameObject*> _ChildList;

	Matrix3 _LocalTransform;
	Matrix3 _GlobalTransform;
	aie::Texture* _Texture;

	Collider* _Collider;
	Collider* _Collider2 = nullptr;
private:
	void AddChild(GameObject* Child);
	void RemoveChild(GameObject* Child);
};

/*
World
	Global = Identity
	Local = Global

Tank
	Local = pos, rot, scale
	Global = World.Global * Local

Turrent
	Local = pos, rot, scale
	Global = Tank.Global * Local

*/