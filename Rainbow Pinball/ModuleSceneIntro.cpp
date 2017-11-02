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
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);
		
	//----------FLIPPER JOINTS-----------//

	flipper_right = App->physics->CreateRectangle(360, 770-50, 99, 19, true);  //change to true once its fixed on the chain
	flipper_left = App->physics->CreateRectangle(250, 770-50, 99, 19, true); //change to true once its fixed on the chain	
	PhysBody* right_joint = App->physics->CreateCircle(401, 772-50, 5, false);
	PhysBody* left_joint = App->physics->CreateCircle(205, 772-50, 5, false);	
	b2RevoluteJointDef RightFJoint;
	b2RevoluteJointDef LeftFJoint;
	b2RevoluteJoint* joint_r;
	b2RevoluteJoint* joint_l;

	RightFJoint.Initialize(flipper_right->body, right_joint->body, right_joint->body->GetWorldCenter());
	LeftFJoint.Initialize(flipper_left->body, left_joint->body, left_joint->body->GetWorldCenter());

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
	
	//----------SPRING---------//

	spring_ = App->physics->CreateRectangle(40, 750, 20, 40, false);

	//-------------BALL-----------//

	ball = App->physics->CreateCircle(40, 730, 10, true);

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

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(background, 0, 0, NULL);
	App->renderer->Blit(mainBoard, 0, 0, NULL);


	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10, true));
		circles.getLast()->data->listener = this;
	}
	
	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
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
