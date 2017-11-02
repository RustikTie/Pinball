#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModulePhysics.h"


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	max_movement = 0;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		App->scene_intro->flipper_left->body->ApplyAngularImpulse(-2.f, true);
		int x, y;
		App->scene_intro->flipper_left->GetPosition(x, y);
		App->renderer->Blit(App->scene_intro->flipperLeft, x - 15, y - 22, NULL, 1.0f, App->scene_intro->flipper_left->GetRotation()); // 180, 739
	}
	else {
		int x, y;
		App->scene_intro->flipper_left->GetPosition(x, y);
		App->renderer->Blit(App->scene_intro->flipperLeft, x - 15, y - 22, NULL, 1.0f, App->scene_intro->flipper_left->GetRotation()); // 180, 739
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		App->scene_intro->flipper_right->body->ApplyAngularImpulse(2.f, true);
		int x, y;
		App->scene_intro->flipper_right->GetPosition(x, y);
		App->renderer->Blit(App->scene_intro->flipperRight, x - 6, y - 22, NULL, 1.0f, App->scene_intro->flipper_right->GetRotation());
	}
	else
	{
		int x, y;
		App->scene_intro->flipper_right->GetPosition(x, y);
		App->renderer->Blit(App->scene_intro->flipperRight, x - 6, y - 22, NULL, 1.0f, App->scene_intro->flipper_right->GetRotation());
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && max_movement <50)
	{		
		max_movement += 1;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		max_movement = 0;
	}

	App->renderer->Blit(App->scene_intro->spring, 17, 800 + max_movement, NULL);

	if (App->scene_intro->ball == NULL)
	{
		App->scene_intro->ball = App->physics->CreateCircle(40, 730, 10, true);
	}

	return UPDATE_CONTINUE;
}



