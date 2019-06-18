#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
	_Texture = nullptr;
	_Parent = nullptr;
	_Collider = nullptr;
	collided = 0;
	_Score = 0;
}

GameObject::GameObject(const char* TextureName)
{
	_Texture = new aie::Texture(TextureName);
	_Parent = nullptr;
	_Collider = nullptr;
	collided = 0;
}


GameObject::~GameObject()
{
	for (int i = 0; i < _ChildList.size(); i++)
	{
		delete _ChildList[i];
	}

	if (_Texture)
	{
		delete _Texture;
		_Texture = nullptr;
	}

	if (_Collider)
	{
		delete _Collider;
		_Collider = nullptr;
	}
}

void GameObject::UpDateGlobalTransform()
{
	if (_Parent)
		_GlobalTransform = _Parent->_GlobalTransform * _LocalTransform;
	else
		_GlobalTransform = _LocalTransform;

	//Collsion
	if (_Collider)
	{
		_Collider->SetPostition(_GlobalTransform.GetTranslation());
		//_Collider->SetRotation(_GlobalTransform.getRotation());
	}

	if (_Collider2)
		_Collider2->SetPostition(_GlobalTransform.GetTranslation());

	for (GameObject* _Child : _ChildList)
	{
		_Child->UpDateGlobalTransform();
	}
}

void GameObject::Update(float deltaTime)
{
	for (GameObject* _Child : _ChildList)
	{
		_Child->Update(deltaTime);
	}
}

void GameObject::Draw(aie::Renderer2D* renderer)
{
	if (_Texture)
		renderer->drawSpriteTransformed3x3(_Texture, _GlobalTransform);

	for (GameObject* _Child : _ChildList)
	{
		_Child->Draw(renderer);
	}
}

void GameObject::SetPosition(Vector2 v2Pos)
{
	_LocalTransform.SetTranslation(v2Pos);
}

Vector2 GameObject::GetPosition()
{
	return Vector2(_LocalTransform.m[6], _LocalTransform.m[7]);
}

void GameObject::SetRotation(float radians)
{
	_LocalTransform.setRotateZ(radians);
}

float GameObject::GetRotation()
{
	return _GlobalTransform.getRotation();
}

float GameObject::GetLocalRotation()
{
	return _LocalTransform.getRotation();
}

void GameObject::SetScale(Vector2 v2Scale)
{
	_LocalTransform.setScale(v2Scale);
}

Vector2 GameObject::GetScale()
{
	return _LocalTransform.getScale();
}

void GameObject::SetParent(GameObject* Parent)
{
	if (_Parent)
		_Parent->RemoveChild(this);

	_Parent = Parent;

	if (_Parent)
		_Parent->AddChild(this);
}

GameObject* GameObject::GetParent()
{
	return _Parent;
}

void GameObject::AddChild(GameObject* Child)
{
	_ChildList.push_back(Child);
}

void GameObject::RemoveChild(GameObject* Child)
{
	auto iter = std::find(_ChildList.begin(), _ChildList.end(), Child);
	if (iter != _ChildList.end())
	{
		_ChildList.erase(iter);
	}
}

void GameObject::OnCollision(GameObject* OtherObject)
{
	std::cout << _Name << "Colliding" << OtherObject->GetName() << std::endl;
}

void GameObject::SetName(std::string name)
{
	_Name = name;
}

std::string GameObject::GetName()
{
	return _Name;
}

bool GameObject::GetCollided()
{
	return collided;
}

void GameObject::SetCollided(bool hit)
{
	collided = hit;
}

bool GameObject::HasCollider2()
{
	if (GetCollider2())
		return true;
	else
		return false;
}

void GameObject::SetLocalRotation(float newRotation)
{
	_LocalTransform.rotation = newRotation;
}

float GameObject::GetScore()
{
	return _Score;
}

void GameObject::SetScore(float newScore)
{
	_Score = newScore;
}