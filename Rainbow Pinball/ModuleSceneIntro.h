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
	PhysBody* flipper_leftupper;
	PhysBody* flipper_right;
	PhysBody* spring_ = nullptr;
	PhysBody* ball;
	PhysBody* ball_reset;
	PhysBody* bouncer1;
	PhysBody* bouncer2;
	PhysBody* bouncer3;
	PhysBody* bouncer4;
	PhysBody* bouncer_left;
	PhysBody* bouncer_right;

	PhysBody* sensor;
	bool sensed;


	SDL_Texture* background;
	SDL_Texture* mainBoard;
	SDL_Texture* flipperLeft;
	SDL_Texture* flipperRight;
	SDL_Texture* spring;
	SDL_Texture* Ball;
	SDL_Texture* scoreBox;
	SDL_Texture* Lives;
	SDL_Texture* end;
	SDL_Texture* welldone;
	SDL_Texture* addon;
	SDL_Texture* rail;
	SDL_Texture* circle1;
	SDL_Texture* circle2;
	SDL_Texture* circle3;
	SDL_Texture* circle4;
	SDL_Texture* leftbouncer;
	SDL_Texture* rightbouncer;

	SDL_Texture* circle = nullptr;
	SDL_Texture* box = nullptr;
	SDL_Texture* rick = nullptr;

	uint lives = 3;
	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;
};
