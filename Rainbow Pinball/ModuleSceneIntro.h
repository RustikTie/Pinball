#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	
	PhysBody* flipper_left;
	PhysBody* flipper_right;
	PhysBody* spring_;
	PhysBody* ball;

	PhysBody* sensor;
	bool sensed;

	SDL_Texture* background;
	SDL_Texture* mainBoard;
	SDL_Texture* flipperLeft;
	SDL_Texture* flipperRight;
	SDL_Texture* spring;
	SDL_Texture* circle = nullptr;
	SDL_Texture* box = nullptr;
	SDL_Texture* rick = nullptr;

	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;
};
