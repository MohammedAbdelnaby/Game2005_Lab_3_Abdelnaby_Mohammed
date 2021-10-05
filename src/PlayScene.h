#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Target.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	Target* m_ball;
	float DegtoRads = (double)M_PI / (double)180.0;
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	int StartingX = 100;
	int StartingY = 500;
	int LaunchElevationAngle = -60;
	float LaunchSpeed = 95;
	float AccelerationGravity = 9.8;
	float m_time = 0;
	SDL_Rect* XIntercept;
	
	glm::vec2 m_mousePosition;
};

#endif /* defined (__PLAY_SCENE__) */