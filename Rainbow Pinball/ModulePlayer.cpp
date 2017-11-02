#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModulePhysics.h"
#include "ModuleWindow.h"


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
	if (App->scene_intro->lives != 0)
	{
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			App->scene_intro->flipper_left->body->ApplyAngularImpulse(-2.f, true);
			App->scene_intro->flipper_leftupper->body->ApplyAngularImpulse(-2.f, true);

			int x, y;
			App->scene_intro->flipper_left->GetPosition(x, y);
			App->renderer->Blit(App->scene_intro->flipperLeft, x, y, NULL, 1.0f, App->scene_intro->flipper_left->GetRotation()); // 180, 739
			App->scene_intro->flipper_leftupper->GetPosition(x, y);
			App->renderer->Blit(App->scene_intro->flipperLeft, x, y, NULL, 1.0f, App->scene_intro->flipper_leftupper->GetRotation()); // 180, 739

		}
		else {
			int x, y;
			App->scene_intro->flipper_left->GetPosition(x, y);
			App->renderer->Blit(App->scene_intro->flipperLeft, x , y, NULL, 1.0f, App->scene_intro->flipper_left->GetRotation()); // 180, 739
			App->scene_intro->flipper_leftupper->GetPosition(x, y);
			App->renderer->Blit(App->scene_intro->flipperLeft, x , y , NULL, 1.0f, App->scene_intro->flipper_leftupper->GetRotation());
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			App->scene_intro->flipper_right->body->ApplyAngularImpulse(2.f, true);
			int x, y;
			App->scene_intro->flipper_right->GetPosition(x, y);
			App->renderer->Blit(App->scene_intro->flipperRight, x , y , NULL, 1.0f, App->scene_intro->flipper_right->GetRotation());
		}
		else
		{
			int x, y;
			App->scene_intro->flipper_right->GetPosition(x, y);
			App->renderer->Blit(App->scene_intro->flipperRight, x , y , NULL, 1.0f, App->scene_intro->flipper_right->GetRotation());
		}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && max_movement <50)
		{
			max_movement += 1;
			if (App->scene_intro->spring_ != NULL)
			{
				App->physics->world->DestroyBody(App->scene_intro->spring_->body);
				App->scene_intro->spring_ = NULL;
			}
			App->scene_intro->ball->body->SetGravityScale(0.5);
		}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
		{
			if (App->scene_intro->spring_ == NULL)
				App->scene_intro->spring_ = App->physics->CreateRectangle(40, 825, 20, 40, false);
			int x, y;
			App->scene_intro->ball->GetPosition(x, y);
			if (y < 820 && y > 750 && x < 60)
			{
				App->scene_intro->ball->body->ApplyForce({ 0, -(max_movement * 10) }, App->scene_intro->ball->body->GetLocalCenter(), true);
				App->scene_intro->ball->body->SetGravityScale(1.5);
			}

			max_movement = 0;

		}
		App->renderer->Blit(App->scene_intro->spring, 17, 800 + max_movement, NULL);
		if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		{
			App->scene_intro->lives = 0;			
		}		
	}
	
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		App->scene_intro->ball->body->SetTransform({ PIXEL_TO_METERS(40),PIXEL_TO_METERS(790) }, 0.0f);
		App->scene_intro->ball->body->SetLinearVelocity({ 0,0 });
		App->scene_intro->ball->body->SetBullet(true);
		App->scene_intro->lives = 3;
		score = 0;
	}

	char score[64];
	char Title[64] = "Rainbow PinBall | Score: ";
	sprintf_s(score, "%d   ", App->player->score);
	strcat_s(Title, score);

	App->window->SetTitle(Title);

	return UPDATE_CONTINUE;
}



