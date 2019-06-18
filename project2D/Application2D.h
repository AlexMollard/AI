#pragma once
#include "Grid.h"
#include "Application.h"
#include "Renderer2D.h"

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	_2dRenderer;
	aie::Font*			_Font;
	Grid*				_Grid;
	Vector2 _StartPos;
	Vector2 _EndPos;
	std::vector<Vector2> _Path;


	float m_timer;
};