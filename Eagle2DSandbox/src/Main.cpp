#include <iostream>
#include <SDL.h>
#include "Eagle2D/Graphics/Window.h"
#include "EventHandler.h"
#include "Graphics/AssetManager.h"
#include <SDL_image.h>
#include "ECS/ECS.h"

#include "ECS/Transform.h"
#include "ECS/Sprite.h"

Eagle::Window window;
Eagle::ECS::Manager manager;

void Eagle::EventHandler::EventScript(SDL_Event event)
{
	if (event.type == SDL_QUIT)
	{
		window.Close();
	}

	switch (event.key.keysym.sym)
	{
	case SDLK_RETURN:
		std::cout << "Enter Key Pressed" << std::endl;
		break;
	}
}

int main(int agrc, char** argv)
{
	window.Init("App", 1280, 720, SDL_WINDOW_OPENGL, SDL_RENDERER_ACCELERATED);
	window.SetFrameRate(240);

	Eagle::EventHandler handler;
	Eagle::AssetManager aManger;

	aManger.AddTexture("assets/goblin_king.png", "goblin");
	SDL_Rect rect = { 0, 0, 64, 64 };

	manager.Init();

	Eagle::ECS::EntityID goblin = manager.CreateEntity();
	manager.AddComponent<Transform>(goblin, Eagle::Rect(0.0f, 0.0f, 64.0f, 64.0f), 0.0f);
	manager.AddComponent<Sprite>(goblin, "goblin", SDL_Rect{ 0, 0, 13, 25 });

	Sprite& sprite = manager.GetComponent<Sprite>(goblin);
	Transform& trans = manager.GetComponent<Transform>(goblin);

	sprite.dst.x = static_cast<int>(trans.transform.position.x);
	sprite.dst.y = static_cast<int>(trans.transform.position.y);
	sprite.dst.w = static_cast<int>(trans.transform.scale.x);
	sprite.dst.h = static_cast<int>(trans.transform.scale.y);

	while (window.IsOpen())
	{
		handler.HandleEvents(&window);

		window.Clear();
		SDL_RenderCopy(Eagle::Window::m_Renderer, aManger.GetTexture(sprite.id), &sprite.src, &sprite.dst);
		window.Update();
	}

	return 0;
}