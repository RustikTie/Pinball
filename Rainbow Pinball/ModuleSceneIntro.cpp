#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ray_on = false;
	sensed = false;

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	background = App->textures->Load("assets/background.png");
	mainBoard = App->textures->Load("assets/mainboard.png");
	flipperLeft = App->textures->Load("assets/flipperleft.png");
	flipperRight = App->textures->Load("assets/flipperright.png");
	spring = App->textures->Load("assets/spring.png");
	Ball = App->textures->Load("assets/ball.png");
	scoreBox = App->textures->Load("assets/scorebox.png");
	Lives = App->textures->Load("assets/lives.png");
	end = App->textures->Load("assets/end.png");
	welldone = App->textures->Load("assets/welldone.png");
	addon = App->textures->Load("assets/addon.png");
	rail = App->textures->Load("assets/rail.png");
	circle1 = App->textures->Load("assets/bouncer1.png");
	circle2 = App->textures->Load("assets/bouncer2.png");
	circle3 = App->textures->Load("assets/bouncer3.png");
	circle4 = App->textures->Load("assets/bouncer4.png");
	leftbouncer = App->textures->Load("assets/bouncerleft.png");
	rightbouncer = App->textures->Load("assets/bouncerright.png");

	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

		
	//----------FLIPPER JOINTS-----------//

	flipper_right = App->physics->CreateRectangle(360, 770, 99, 19, true); 
	flipper_left = App->physics->CreateRectangle(250, 770, 99, 19, true); 	
	flipper_leftupper = App->physics->CreateRectangle(140, 380- 50, 99, 19, true); 

	PhysBody* right_joint = App->physics->CreateCircle(401, 772, 5, false);
	PhysBody* left_joint = App->physics->CreateCircle(205, 772, 5, false);	
	PhysBody* left_jointupper = App->physics->CreateCircle(95, 380-50, 5, false);

	b2RevoluteJointDef RightFJoint;
	b2RevoluteJointDef LeftFJoint;
	b2RevoluteJointDef LeftUpperJoint;
	b2RevoluteJoint* joint_r;
	b2RevoluteJoint* joint_l;
	b2RevoluteJoint* joint_lu;


	RightFJoint.Initialize(flipper_right->body, right_joint->body, right_joint->body->GetWorldCenter());
	LeftFJoint.Initialize(flipper_left->body, left_joint->body, left_joint->body->GetWorldCenter());
	LeftUpperJoint.Initialize(flipper_leftupper->body, left_jointupper->body, left_jointupper->body->GetWorldCenter());

	RightFJoint.lowerAngle =  -30 * DEGTORAD;
	RightFJoint.upperAngle = 30 * DEGTORAD;
	RightFJoint.enableLimit = true;
	RightFJoint.collideConnected = false;
	joint_r = (b2RevoluteJoint*)App->physics->world->CreateJoint(&RightFJoint);

	LeftFJoint.lowerAngle = -30 * DEGTORAD;
	LeftFJoint.upperAngle = 30 * DEGTORAD;
	LeftFJoint.enableLimit = true;
	LeftFJoint.collideConnected = false;
	joint_l = (b2RevoluteJoint*)App->physics->world->CreateJoint(&LeftFJoint);

	LeftUpperJoint.lowerAngle = -30 * DEGTORAD;
	LeftUpperJoint.upperAngle = 30 * DEGTORAD;
	LeftUpperJoint.enableLimit = true;
	LeftUpperJoint.collideConnected = false;
	joint_lu = (b2RevoluteJoint*)App->physics->world->CreateJoint(&LeftUpperJoint);
	
	//----------SPRING---------//

	spring_ = App->physics->CreateRectangle(40, 825, 20, 40, false);

	//-------------BALL-----------//

	ball = App->physics->CreateCircle(40, 790, 11, true);
	ball->body->SetBullet(true);

	//----------BOUNCERS----------//
	bouncer1 = App->physics->CreateCircle(359, 407, 25, false);
	b2Fixture* fix1 = bouncer1->body->GetFixtureList();
	fix1->SetRestitution(3.0f);

	bouncer2 = App->physics->CreateCircle(280, 307, 25, false);
	b2Fixture* fix2 = bouncer2->body->GetFixtureList();
	fix2->SetRestitution(3.0f);

	bouncer3 = App->physics->CreateCircle(285, 225, 25, false);
	b2Fixture* fix3 = bouncer3->body->GetFixtureList();
	fix3->SetRestitution(3.0f);

	bouncer4 = App->physics->CreateCircle(360, 255, 25, false);
	b2Fixture* fix4 = bouncer4->body->GetFixtureList();
	fix4->SetRestitution(3.0f);

	int bouncerleft[8] = {
		71, 113,
		31, 13,
		27, 14,
		67, 114
	};
	bouncer_left = App->physics->CreateChain(150, 600, bouncerleft, 8, false);
	b2Fixture* fix5 = bouncer_left->body->GetFixtureList();
	fix5->SetRestitution(3.0f);

	int bouncerright[8] = {
		40, 111,
		78, 16,
		83, 19,
		46, 113
	};
	bouncer_right = App->physics->CreateChain(340, 600, bouncerright, 8, false);
	b2Fixture* fix6 = bouncer_right->body->GetFixtureList();
	fix6->SetRestitution(3.0f);

	bouncer5 = App->physics->CreateRectangle(100, 819, 30, 3, false);
	b2Fixture* fix7 = bouncer5->body->GetFixtureList();
	fix7->SetRestitution(3.0f);

	bouncer6 = App->physics->CreateRectangle(510, 819, 30, 3, false);
	b2Fixture* fix8 = bouncer6->body->GetFixtureList();
	fix8->SetRestitution(3.0f);
	
	//---------MUSIC----------//
	App->audio->PlayMusic("assets/ukelele.ogg", 2.0f);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(background);
	App->textures->Unload(mainBoard);
	App->textures->Unload(flipperLeft);
	App->textures->Unload(flipperRight);
	App->textures->Unload(spring);
	App->textures->Unload(Ball);
	App->textures->Unload(scoreBox);
	App->textures->Unload(Lives);
	App->textures->Unload(end);
	App->textures->Unload(welldone);
	App->textures->Unload(addon);
	App->textures->Unload(rail);	

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	if (lives > 0)
	{
		App->renderer->Blit(background, 0, 0, NULL);
		App->renderer->Blit(addon, 0, 0, NULL);
		App->renderer->Blit(mainBoard, 0, 0, NULL);


		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10, true));
			circles.getLast()->data->listener = this;
		}

		// All draw functions ------------------------------------------------------

		int x, y;
		ball->GetPosition(x, y);
		App->renderer->Blit(Ball, x, y, NULL, 1.0f);
		if (y > 899)
		{
			ball->body->SetTransform({ PIXEL_TO_METERS(40),PIXEL_TO_METERS(790) }, 0.0f);
			ball->body->SetLinearVelocity({ 0,0 });
			lives = lives - 1;
		}	
		App->renderer->Blit(rail, 0, 0, NULL);
		SDL_Rect b;
			b.x = 23;
			b.y = 24;
			b.h = 59;
			b.w = 59;
		App->renderer->Blit(circle1, 330, 380, &b, 0.0f);
		App->renderer->Blit(circle2, 255, 280, &b, 0.0f);
		App->renderer->Blit(circle3, 260, 200, &b, 0.0f);
		App->renderer->Blit(circle4, 335, 230, &b, 0.0f);
		b.x = 17;
		b.y = 9;
		b.h = 121;
		b.w = 66;
		App->renderer->Blit(leftbouncer, 165, 610, &b, 0.0f);
		b.x = 39;
		b.y = 11;
		b.h = 121;
		b.w = 66;
		App->renderer->Blit(rightbouncer, 380, 615, &b, 0.0f);



			SDL_Rect r;
			r.h = 15;
			r.w = 100;
			r.x = 0;
			App->renderer->Blit(scoreBox, 5, 5, NULL, 0.0f);

			if (lives == 1)
			{
				r.y = 15;
				App->renderer->Blit(Lives, 90, 25, &r, 0.0f);
			}
			else if (lives == 2)
			{
				r.y = 30;
				App->renderer->Blit(Lives, 90, 25, &r, 0.0f);
			}
			else if (lives == 3)
			{
				r.y = 45;
				App->renderer->Blit(Lives, 90, 25, &r, 0.0f);
			}	


	}

	if (lives == 0)
	{
		App->renderer->Blit(end, 0,0, NULL, 0.0f);
		App->renderer->Blit(welldone, 0, 0, NULL, 0.0f);

	}
	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);



	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
