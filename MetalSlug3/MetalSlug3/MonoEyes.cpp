#include "MonoEyes.h"

MonoEyes::MonoEyes()
{
}

MonoEyes::~MonoEyes()
{
}

void MonoEyes::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ {0,0},{500,500} });

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({ 100,300 });
	Collider->SetPosition({ 0,-150 });
	Collider->SetColType(ECollisionType::Rect);
}

void MonoEyes::Tick(float _DeltaTime)
{
}

void MonoEyes::StateUpdate()
{
}

void MonoEyes::StateChange()
{
}

void MonoEyes::None(float _DeltaTime)
{
}

void MonoEyes::Spawn(float _DeltaTime)
{
}

void MonoEyes::Idle(float _DeltaTime)
{
}

void MonoEyes::Attack(float _DeltaTime)
{
}

void MonoEyes::NoneStart()
{
}

void MonoEyes::SpawnStart()
{
}

void MonoEyes::IdleStart()
{
}

void MonoEyes::AttackStart()
{
}
