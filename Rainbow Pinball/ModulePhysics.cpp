#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "ModuleSceneIntro.h"
#include "p2Point.h"
#include "math.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	mouse_joint = NULL;
	debug = true;

	
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	// needed to create joints like mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd);

	// big static circle as "ground" in the middle of the screen
	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;
	int diameter = SCREEN_WIDTH / 2;

	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	 //COORDS 
	int mainboard1[150] = {
		0, 895,
		24, 895,
		24, 627,
		24, 455,
		28, 384,
		38, 316,
		65, 236,
		97, 184,
		133, 144,
		187, 101,
		242, 74,
		301, 65,
		323, 42,
		363, 24,
		394, 20,
		433, 27,
		464, 45,
		496, 84,
		512, 104,
		528, 136,
		553, 196,
		564, 267,
		567, 301,
		561, 357,
		558, 368,
		493, 517,
		494, 527,
		498, 533,
		507, 537,
		518, 560,
		522, 577,
		524, 605,
		522, 820,
		493, 820,
		491, 772,
		355, 846,
		355, 897,
		574, 894,
		572, 634,
		557, 633,
		557, 602,
		537, 601,
		537, 571,
		533, 556,
		528, 543,
		522, 534,
		526, 531,
		530, 521,
		525, 508,
		515, 501,
		536, 455,
		564, 398,
		573, 358,
		573, 277,
		574, 238,
		566, 201,
		555, 162,
		526, 106,
		502, 70,
		454, 21,
		413, 6,
		364, 10,
		333, 20,
		304, 37,
		293, 36,
		283, 51,
		226, 65,
		158, 101,
		93, 160,
		53, 225,
		25, 300,
		8, 405,
		11, 453,
		11, 633,
		0, 635
	};
	CreateChain(0, 0, mainboard1, 150, false);
	int mainboard2[60] = {
		252, 895,
		55, 895,
		55, 483,
		61, 404,
		68, 345,
		81, 283,
		105, 232,
		140, 181,
		182, 145,
		242, 114,
		245, 122,
		245, 170,
		241, 175,
		164, 203,
		150, 207,
		138, 207,
		97, 280,
		84, 338,
		132, 378,
		133, 387,
		134, 403,
		134, 523,
		117, 531,
		105, 535,
		95, 544,
		84, 562,
		84, 820,
		115, 821,
		114, 771,
		252, 843
	};
	CreateChain(0, 0, mainboard2, 60, false);
	int mainboard3[104] = {
		455, 452,
		469, 459,
		502, 397,
		524, 347,
		530, 325,
		532, 301,
		533, 251,
		527, 222,
		510, 182,
		494, 152,
		472, 125,
		437, 95,
		410, 76,
		398, 72,
		387, 70,
		380, 77,
		375, 85,
		368, 85,
		354, 107,
		360, 171,
		365, 175,
		442, 201,
		447, 201,
		447, 237,
		445, 250,
		437, 279,
		430, 298,
		418, 322,
		400, 347,
		380, 370,
		349, 397,
		352, 402,
		383, 405,
		418, 362,
		447, 307,
		457, 279,
		465, 247,
		465, 192,
		455, 175,
		443, 167,
		417, 150,
		400, 147,
		393, 120,
		395, 111,
		422, 106,
		455, 122,
		486, 160,
		506, 201,
		520, 249,
		520, 312,
		506, 363,
		480, 410
	};
	CreateChain(0, 0, mainboard3, 104, false);
	int mainboard4[14] = {
		285, 163,
		291, 158,
		291, 129,
		287, 123,
		281, 123,
		277, 127,
		278, 160
	};
	CreateChain(0, 0, mainboard4, 14, false);
	CreateChain(41, 0, mainboard4, 14, false);
	int mainboard5[18] = {
		298, 353,
		304, 348,
		304, 341,
		280, 312,
		271, 309,
		255, 308,
		218, 317,
		218, 325,
		222, 330
	};
	CreateChain(0, 0, mainboard5, 18, false);
	int mainboard6[34] = {
		202, 786,
		213, 786,
		222, 777,
		219, 763,
		205, 755,
		147, 719,
		133, 705,
		127, 685,
		128, 614,
		125, 610,
		116, 608,
		112, 614,
		113, 704,
		114, 716,
		121, 729,
		126, 739,
		182, 775
	};
	CreateChain(0, 0, mainboard6, 34, false);
	int mainboard7[32] = {
		485, 610,
		493, 607,
		497, 611,
		497, 706,
		493, 722,
		480, 741,
		460, 756,
		408, 786,
		397, 786,
		389, 778,
		389, 768,
		395, 760,
		462, 718,
		476, 705,
		481, 693,
		481, 613
	};
	CreateChain(0, 0, mainboard7, 32, false);	
	
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			if(pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius, bool isDynamic)
{
	b2BodyDef body;
	if (isDynamic == true)
	{
		body.type = b2_dynamicBody;
	}
	else
	{
		body.type = b2_staticBody;
	}
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height, bool isDynamic)
{
	b2BodyDef body;
	if (isDynamic == true)
	{
		body.type = b2_dynamicBody;
	}
	else
	{
		body.type = b2_staticBody;
	}
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size, bool dynamic)
{
	b2BodyDef body;
	if (dynamic == true) 
	{
		body.type = b2_dynamicBody;
	}
	else
	{
		body.type = b2_staticBody;
	}
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	b2Body* bodyFound = nullptr;
	b2Vec2 mousePos;
	mousePos.x = PIXEL_TO_METERS(App->input->GetMouseX());
	mousePos.y = PIXEL_TO_METERS(App->input->GetMouseY());

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}

			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)				// TODO 1: If mouse button 1 is pressed ...
			{
				if (f->TestPoint(mousePos) == true)
					bodyFound = b;
			}

			// test if the current body contains mouse position
		}
	}

	// If a body was selected we will attach a mouse joint to it
	// so we can pull it around
	// TODO 2: If a body was selected, create a mouse joint
	// using mouse_joint class property
	if (bodyFound != nullptr)
	{
		LOG("Creating Joint");
		b2MouseJointDef def;
		def.bodyA = ground;
		def.bodyB = bodyFound;
		def.target = mousePos;
		def.dampingRatio = 0.5f;
		def.frequencyHz = 2.0f;
		def.maxForce = 100.0f*bodyFound->GetMass();

		mouse_joint = (b2MouseJoint*)world->CreateJoint(&def);
	}

	// TODO 3: If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && mouse_joint != nullptr)
	{
		mouse_joint->SetTarget(mousePos);
		//App->renderer->DrawLine(mouse_position.x, mouse_position.y, body_found->GetPosition().x, body_found->GetPosition().y,255,0,0);
	}

	// TODO 4: If the player releases the mouse button, destroy the joint
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP && mouse_joint != nullptr)
	{
		world->DestroyJoint(mouse_joint);
		mouse_joint = nullptr;
		bodyFound = nullptr;
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}