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
		Renderer->SetImage("Tool_Bomb_Right_0.bmp");
		Renderer->SetTransform({ {0,0},{50,50} });
		Renderer->SetImageCuttingTransform({ {0,0}, {50, 50} });
	}
}

void ABullet::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);

}