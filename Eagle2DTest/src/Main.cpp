#include "egpch.h"
#include "Eagle2D.h"
#include <SDL.h>
#include <SDL_image.h>

#include "ECS/Transform.h"
#include "ECS/Sprite.h"
#include "ECS/RigidBody.h"
#include "ECS/Light.h"

#include "ECS/PhysicsSystem.h"
#include "ECS/RenderSystem.h"
#include "ECS/LightingSystem.h"

Eagle::Window window;
Eagle::AssetManager aManager;
Eagle::ECS::Manager manager;
Eagle::ECS::EntityID goblin;

std::shared_ptr<Eagle::PhysicsSystem> physicsSystem;
std::shared_ptr<Eagle::RenderSystem> renderSystem;
std::shared_ptr<Eagle::LightingSystem> lightingSystem;

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

	manager.Init();

	Eagle::EventHandler handler;
	//

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

	{
		Eagle::ECS::Signature signature;
		signature.set(manager.GetComponentType<Eagle::Light>());
		signature.set(manager.GetComponentType<Eagle::Transform>());

		lightingSystem = manager.AddSystem<Eagle::LightingSystem>(signature);
	}

	goblin = manager.CreateEntity();
	manager.AddComponent<Eagle::Transform>(goblin, Eagle::Rect(0.0f, 0.0f, 64.0f, 64.0f), 0.0f);
	manager.AddComponent<Eagle::Sprite>(goblin, "goblin", SDL_Rect{ 0, 0, 13, 25 });
	manager.AddComponent<Eagle::RigidBody>(goblin, Eagle::Rect(20.0f, 38.0f, 34.0f, 24.0f), Eagle::Vector2f(), Eagle::Vector2f());
	manager.AddComponent<Eagle::Light>(goblin, "light", 200.0f, Eagle::Vector2f(32.0f, 32.0f), SDL_Color{ 0, 255, 255 });

	Eagle::ECS::EntityID room = manager.CreateEntity();
	manager.AddComponent<Eagle::Transform>(room, Eagle::Rect(0.0f, 0.0f, 1280.0f, 720.0f), 0.0f);
	manager.AddComponent<Eagle::Sprite>(room, "room", SDL_Rect{ 0, 0, 165, 90 });

	Eagle::ECS::EntityID wall = manager.CreateEntity();
	manager.AddComponent<Eagle::Transform>(wall, Eagle::Rect(800.0f, 100.0f, 20.0f, 300.0f), 0.0f);
	manager.AddComponent<Eagle::Sprite>(wall, "goblin", SDL_Rect{ 0, 0, 13, 25 });
	manager.AddComponent<Eagle::RigidBody>(wall, Eagle::Rect(0.0f, 0.0f, 20.0f, 280.0f));
	manager.AddComponent<Eagle::Light>(wall, "light", 200.0f, Eagle::Vector2f(), SDL_Color{ 255, 165, 0 });

	EG_WARN("Created Entities.");

	Eagle::Sprite& sprite = manager.GetComponent<Eagle::Sprite>(goblin);
	Eagle::Transform& trans = manager.GetComponent<Eagle::Transform>(goblin);
	Eagle::RigidBody& rb = manager.GetComponent<Eagle::RigidBody>(goblin);

	Eagle::Transform& t = manager.GetComponent<Eagle::Transform>(wall);

	aManager.Init(&window);

	aManager.AddTexture("assets/goblin_king.png", "goblin");
	aManager.AddTexture("assets/light.png", "light");
	aManager.AddTexture("assets/Full_Room_1.png", "room");

	aManager.SetLayer("room", 0);
	aManager.SetLayer("goblin", 1);

	physicsSystem->Init();

	//SDL_SetTextureBlendMode(aManager.GetTexture("light"), SDL_BLENDMODE_ADD);

	//SDL_Texture* rend_shadow = SDL_CreateTexture(window.m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
	//SDL_SetTextureBlendMode(rend_shadow, SDL_BLENDMODE_MOD);

	//SDL_Texture* rend_shadow2 = SDL_CreateTexture(window.m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
	//SDL_SetTextureBlendMode(rend_shadow2, SDL_BLENDMODE_MOD);

	//SDL_SetRenderDrawBlendMode(*window.GetRenderer(), SDL_BLENDMODE_BLEND);

	//SDL_Texture* backgroundLayer = SDL_CreateTexture(*window.GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
	//SDL_Texture* lightLayer = SDL_CreateTexture(*window.GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
	//SDL_Texture* resultLayer = SDL_CreateTexture(*window.GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);

	//SDL_SetTextureBlendMode(lightLayer, SDL_BLENDMODE_MOD);
	//SDL_SetTextureColorMod(aManager.GetTexture("light"), 0, 255, 255);

	renderSystem->Init(&aManager);
	renderSystem->UpdateLayers();

	lightingSystem->Init(&window, &aManager);

	while (window.IsOpen())
	{
		handler.HandleEvents();
		physicsSystem->Update();

		//METHOD 3 OF LIGHTS
		//SDL_SetRenderTarget(*window.GetRenderer(), lightLayer);
		//SDL_SetRenderDrawColor(*window.GetRenderer(), 50, 50, 50, 255);
		//SDL_RenderClear(*window.GetRenderer());

		//SDL_RenderFillRect(*window.GetRenderer(), nullptr);

		//SDL_Rect spot1 = { trans.transform.position.x - 200, trans.transform.position.y - 200, 500, 500 };
		//SDL_Rect spot2 = { 400, 400, 100, 100 };

		//SDL_RenderCopy(*window.GetRenderer(), aManager.GetTexture("light"), nullptr, &spot1);
		//SDL_RenderCopy(*window.GetRenderer(), aManager.GetTexture("light"), nullptr, &spot2);

		//SDL_SetRenderTarget(*window.GetRenderer(), NULL);
		//SDL_RenderClear(*window.GetRenderer());

		//SDL_RenderCopy(window.m_Renderer, aManager.GetTexture("room"), nullptr, nullptr);
		//spot1 = { static_cast<int>(trans.transform.position.x), static_cast<int>(trans.transform.position.y), 64, 64 };
		//SDL_RenderCopy(window.m_Renderer, aManager.GetTexture("goblin"), nullptr, &spot1);
		SDL_Color color;
		color.r = 0; color.g = 0; color.b = 0;
		lightingSystem->Update(color);
		renderSystem->Update();
		//SDL_RenderCopy(*window.GetRenderer(), aManager.GetTexture("lightLayer"), nullptr, nullptr);
		lightingSystem->Clear();

		window.Update();
		//yuhb
	}

	return 0;
}