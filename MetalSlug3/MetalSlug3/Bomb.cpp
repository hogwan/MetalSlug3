#include "Bomb.h"
#include "EngineCore/EngineCore.h"
#include "ContentsHelper.h"
#include "Marco.h"
#include "Enemy.h"

ABomb::ABomb()
{
}

ABomb::~ABomb()
{
	++UContentsHelper::Player->RemainBomb;
}

ABomb::ABomb(FVector _Force)
{
	Force = _Force;
}

void ABomb::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Collider = CreateCollision(MT3CollisionOrder::PlayerBullet);
	FVector MarcoSize = { 527.27273f, 527.27273f };
	Renderer->SetImage("Bomb.png");
	Renderer->SetTransform({ {0,0},MarcoSize });

	Collider->SetScale({25.0f,25.0f});
	Collider->SetPosition({ 0.0f,0.0f });
	Collider->SetColType(ECollisionType::Rect);

	Renderer->CreateAnimation("Rotate_Right", "Bomb.png", 0, 31, 0.03f, true);
	Renderer->ChangeAnimation("Rotate_Right");

	Destroy(1.2f);
	--UContentsHelper::Player->RemainBomb;
}
void ABomb::GravityCheck(float _DeltaTime)
{
	MoveVector += Gravity * _DeltaTime;
}
void ABomb::ReflectionCheck()
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation({ 0.0f, -10.0f});
		MoveVector.Y = -0.7f * MoveVector.Y;
		MoveVector.X = 1.1f * MoveVector.X;
	}
}
void ABomb::HitCheck()
{
	std::vector<UCollision*> Result;
	if (Collider->CollisionCheck(MT3CollisionOrder::Player, Result))
	{
		AEnemy* Enemy = dynamic_cast<AEnemy*>(Result[0]);
		Enemy->Damaged(Damage);
		Destroy();
	}
}
void ABomb::Tick(float _DeltaTime)
{
	AddActorLocation(MoveVector * _DeltaTime);
	GravityCheck(_DeltaTime);
	ReflectionCheck();

}

