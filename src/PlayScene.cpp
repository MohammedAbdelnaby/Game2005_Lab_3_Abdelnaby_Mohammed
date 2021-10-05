#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	float dt = Game::Instance().getDeltaTime();

	float vx = cos(LaunchElevationAngle * DegtoRads) * LaunchSpeed;
	float vy = sin(LaunchElevationAngle * DegtoRads) * LaunchSpeed;
	float TotalSimDuration = 100.0f;
	int numPoints = 3000;
	float simTime = 0.0f;
	float timeStep = TotalSimDuration / (float)numPoints;
	glm::vec2 nextPoint;
	glm::vec2 lastPoint = glm::vec2(StartingX, StartingY);
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 0, 200, 0, 255);
	for (int i = 0; i < numPoints; i++)
	{
		nextPoint.x = StartingX + vx * simTime;
		nextPoint.y = StartingY + vy * simTime + 0.5 * AccelerationGravity * pow(simTime, 2);
		SDL_RenderDrawLineF(Renderer::Instance().getRenderer(), lastPoint.x, lastPoint.y, nextPoint.x, nextPoint.y);
		lastPoint = nextPoint;
		simTime += timeStep;
	}
	XIntercept->x = StartingX + (sin((2* LaunchElevationAngle) *DegtoRads ) * pow(LaunchSpeed, 2)) / (-AccelerationGravity) - 5;
	std::cout << XIntercept->x << std::endl;
	//m_ball->getTransform()->position.y += vy * dt;
	//m_ball->getTransform()->position.x += vx * dt;
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 200, 0, 0, 255);
	SDL_RenderDrawLineF(Renderer::Instance().getRenderer(), StartingX, StartingY, StartingX + vx * 5, StartingY + vy * 5);
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 0, 0, 0, 255);
	SDL_RenderDrawLineF(Renderer::Instance().getRenderer(), 0, 500, 800, 500);
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(Renderer::Instance().getRenderer(), XIntercept);
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	m_ball = new Target();
	m_ball->getTransform()->position = glm::vec2(StartingX, StartingY);
	addChild(m_ball);
	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
	XIntercept = new SDL_Rect();
	XIntercept->y = StartingY - 5;
	XIntercept->w = 10;
	XIntercept->h = 10;
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	static float X = StartingX;
	if (ImGui::SliderFloat("X", &X, 100.0f, 400.f, "%.2f"))
	{
		StartingX = X;
		m_ball->getTransform()->position.x = StartingX;
	}

	static float Y = StartingY;
	if (ImGui::SliderFloat("Y", &Y, 500.0f, 100.f, "%.2f"))
	{
		StartingY = Y;
		m_ball->getTransform()->position.y = StartingY;
	}

	ImGui::SliderInt("Angle", &LaunchElevationAngle, 0, -90, "%.3f");

	ImGui::SliderFloat("Speed", &LaunchSpeed, 0.0f, 100.0f, "%.3f");

	ImGui::SliderFloat("Gravity", &AccelerationGravity, 20.0f, 0, "%.3f");
	
	ImGui::End();
}
