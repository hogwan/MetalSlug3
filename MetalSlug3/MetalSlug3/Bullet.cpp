#include "Bullet.h"
#include <Windows.h>
#include <EngineCore\EngineCore.h>

ABullet::ABullet()
{
}

ABullet::~ABullet()
{
}


void ABullet::BeginPlay()
{
	
}

void ABullet::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);
}