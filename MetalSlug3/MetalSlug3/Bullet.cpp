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
	{
		UImageRenderer* Renderer = CreateImageRenderer(-10);
		Renderer->SetImageToScale("Tool_Bomb_Right_0.bmp");
	}
}

void ABullet::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);

}