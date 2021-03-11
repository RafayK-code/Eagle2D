#include "egpch.h"
#include "Eagle2D.h"
#include <SDL.h>
#include <SDL_image.h>

#include "ECS/Transform.h"
#include "ECS/Sprite.h"
#include "ECS/RigidBody.h"

#include "ECS/RenderSystem.h"
#include "ECS/PhysicsSystem.h"

Eagle::Window window;
Eagle::ECS::Manager manager;
Eagle::AssetManager aManager;

Eagle::ECS::EntityID goblin;

std::shared_ptr<Eagle::RenderSystem> renderSystem;
std::shared_ptr<Eagle::PhysicsSystem> physicsSystem;

void Eagle::EventScript(SDL_Event event)
{
	Transform& t = manager.GetComponent<Transform>(goblin);
	RigidBody& rb = manager.GetComponent<RigidBody>(goblin);

	if (event.type == SDL_QUIT)
	{
		window.Close();
	}

	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			rb.velocity.y = -3.0f;
			break;
		case SDLK_s:
			rb.velocity.y = 3.0f;
			break;
		case SDLK_a:
			rb.velocity.x = -3.0f;
			break;
		case SDLK_d:
			rb.velocity.x = 3.0f;
			break;
		}
	}

	if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			rb.velocity.y = 0;
			break;
		case SDLK_s:
			rb.velocity.y = 0;
			break;
		case SDLK_a:
			rb.velocity.x = 0;
			break;
		case SDLK_d:
			rb.velocity.x = 0;
			break;
		}
	}
}

int main(int agrc, char** argv)
{
	Eagle::Log::Init("APP");

	EG_ERROR("Welcome to test");

	window.Init("App", 1280, 720, SDL_WINDOW_OPENGL, SDL_RENDERER_ACCELERATED);
	window.SetFrameRate(60);

	aManager.Init(&window);

	Eagle::EventHandler handler;

	aManager.AddTexture("assets/goblin_king.png", "goblin");
	aManager.AddTexture("assets/light.png", "light");
	aManager.AddTexture("assets/Full_Room_1.png", "room");

	aManager.CreateLight("shadow1", SDL_Color{255, 255, 255, 255});
	aManager.CreateLight("shadow2", SDL_Color{ 255, 255, 255, 255 });
	SDL_Rect rect = { 0, 0, 64, 64 };

	manager.Init();

	{
		Eagle::ECS::Signature signature;
		signature.set(manager.GetComponentType<Eagle::Transform>());
		signature.set(manager.GetComponentType<Eagle::RigidBody>());

		physicsSystem = manager.AddSystem<Eagle::PhysicsSystem>(signature);
	}

	{
		Eagle::ECS::Signature signature;
		signature.set(manager.GetComponentType<Eagle::Transform>());
		signature.set(manager.GetComponentType<Eagle::Sprite>());

		renderSystem = manager.AddSystem<Eagle::RenderSystem>(signature);
	}

	Eagle::ECS::EntityID wall = manager.CreateEntity();
	manager.AddComponent<Eagle::Transform>(wall, Eagle::Rect(800.0f, 100.0f, 20.0f, 300.0f), 0.0f);
	manager.AddComponent<Eagle::Sprite>(wall, "goblin", SDL_Rect{ 0, 0, 13, 25 });
	manager.AddComponent<Eagle::RigidBody>(wall, Eagle::Rect(0.0f, 0.0f, 20.0f, 280.0f));

	goblin = manager.CreateEntity();
	manager.AddComponent<Eagle::Transform>(goblin, Eagle::Rect(0.0f, 0.0f, 64.0f, 64.0f), 0.0f);
	manager.AddComponent<Eagle::Sprite>(goblin, "goblin", SDL_Rect{ 0, 0, 13, 25 });
	manager.AddComponent<Eagle::RigidBody>(goblin, Eagle::Rect(20.0f, 38.0f, 34.0f, 24.0f), Eagle::Vector2f(), Eagle::Vector2f());

	Eagle::Sprite& sprite = manager.GetComponent<Eagle::Sprite>(goblin);
	Eagle::Transform& trans = manager.GetComponent<Eagle::Transform>(goblin);
	Eagle::RigidBody& rb = manager.GetComponent<Eagle::RigidBody>(goblin);

	Eagle::Transform& t = manager.GetComponent<Eagle::Transform>(wall);

	renderSystem->Init(&aManager);
	physicsSystem->Init();

	SDL_SetTextureBlendMode(aManager.GetTexture("light"), SDL_BLENDMODE_ADD);

	//SDL_Texture* rend_shadow = SDL_CreateTexture(window.m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
	//SDL_SetTextureBlendMode(rend_shadow, SDL_BLENDMODE_MOD);

	//SDL_Texture* rend_shadow2 = SDL_CreateTexture(window.m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
	//SDL_SetTextureBlendMode(rend_shadow2, SDL_BLENDMODE_MOD);

	SDL_SetRenderDrawBlendMode(window.m_Renderer, SDL_BLENDMODE_BLEND);

	SDL_Texture* backgroundLayer = SDL_CreateTexture(window.m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
	SDL_Texture* lightLayer = SDL_CreateTexture(window.m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
	SDL_Texture* resultLayer = SDL_CreateTexture(window.m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);

	SDL_SetTextureBlendMode(lightLayer, SDL_BLENDMODE_MOD);

	while (window.IsOpen())
	{
		physicsSystem->Update();
		handler.HandleEvents();

		//METHOD 3 OF LIGHTS
		SDL_SetRenderTarget(window.m_Renderer, lightLayer);
		SDL_SetRenderDrawColor(window.m_Renderer, 0, 0, 0, 255);
		SDL_RenderClear(window.m_Renderer);

		SDL_RenderFillRect(window.m_Renderer, nullptr);

		SDL_Rect spot1 = { trans.transform.position.x - 64, trans.transform.position.y - 64, 500, 500 };
		SDL_Rect spot2 = { 400, 400, 100, 100 };

		SDL_RenderCopy(window.m_Renderer, aManager.GetTexture("light"), nullptr, &spot1);
		SDL_RenderCopy(window.m_Renderer, aManager.GetTexture("light"), nullptr, &spot2);

		SDL_SetRenderTarget(window.m_Renderer, NULL);
		SDL_RenderClear(window.m_Renderer);

		SDL_RenderCopy(window.m_Renderer, aManager.GetTexture("room"), nullptr, nullptr);
		spot1 = { static_cast<int>(trans.transform.position.x), static_cast<int>(trans.transform.position.y), 64, 64 };
		SDL_RenderCopy(window.m_Renderer, aManager.GetTexture("goblin"), nullptr, &spot1);
		renderSystem->Update();
		SDL_RenderCopy(window.m_Renderer, lightLayer, nullptr, nullptr);

		window.Update();
	}

	return 0;
}