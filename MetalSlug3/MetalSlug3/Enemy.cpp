#include <EngineCore/Actor.h>
#include "Enemy.h"
#include "contentpartner.h"
#include "ScreenCollision.h"
AEnemy::AEnemy()
{

}

AEnemy::~AEnemy()
{

}

void AEnemy::BeginPlay()
{
	AMT3Object::BeginPlay();
}

void AEnemy::Tick(float _DeltaTime)
{
	AMT3Object::Tick(_DeltaTime);
}