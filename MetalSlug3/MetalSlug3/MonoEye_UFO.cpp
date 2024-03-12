#include "MonoEye_UFO.h"
#include "Laser.h"

AMonoEye_UFO::AMonoEye_UFO()
{
}

AMonoEye_UFO::~AMonoEye_UFO()
{
}

void AMonoEye_UFO::BeginPlay()
{
	SetActorLocation({ 14150,2098 });

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ {0,0},{800,850} });
	Renderer->CreateAnimation("Idle", "MonoEye_UFO_Idle.png", 0, 4,0.08f, true);
	Renderer->CreateAnimation("Charging", "MonoEye_UFO_Charging.png", 0, 3,0.08f, false);
	Renderer->CreateAnimation("Firing", "MonoEye_UFO_Firing.png", 0, 5, 0.08f, true);

	Body = CreateImageRenderer(MT3RenderOrder::UFO_Body);
	Body->SetImage("MonoEye_UFO_Body.png");
	Body->SetTransform({ {0,232},{800,850} });

	BrokenBackBody = CreateImageRenderer(MT3RenderOrder::UFO_BackBody);
	BrokenBackBody->SetImage("MonoEye_UFO_DestroyedBack.png");
	BrokenBackBody->SetTransform({ {0,40},{800,850} });
	BrokenBackBody->ActiveOff();

	AncientCharactor = CreateImageRenderer(MT3RenderOrder::UFO_AncientCharactor);
	AncientCharactor->SetImage("AncientCharacter.png");
	AncientCharactor->SetTransform({ {0,0},{600,200} });
	AncientCharactor->ActiveOff();

	Collider = CreateCollision(MT3CollisionOrder::Boss);
	Collider->SetTransform({ {0,-100},{300,200} });
	Collider->SetColType(ECollisionType::Rect);
}

void AMonoEye_UFO::Tick(float _DeltaTime)
{
	StateUpdate(_DeltaTime);

	if (Hp <= 0)
	{
		StateChange(UFOState::Destroyed);
		return;
	}
}

void AMonoEye_UFO::StateUpdate(float _DeltaTime)
{
	switch (CurState)
	{
	case UFOState::None:
		None(_DeltaTime);
		break;
	case UFOState::Idle:
		Idle(_DeltaTime);
		break;
	case UFOState::Charging:
		Charging(_DeltaTime);
		break;
	case UFOState::Firing:
		Firing(_DeltaTime);
		break;
	case UFOState::Destroyed:
		Destroyed(_DeltaTime);
	default:
		break;
	}
}

void AMonoEye_UFO::StateChange(UFOState _State)
{
	if (CurState != _State)
	{
		switch (_State)
		{
		case UFOState::Idle:
			IdleStart();
			break;
		case UFOState::Charging:
			ChargingStart();
			break;
		case UFOState::Firing:
			FiringStart();
			break;
		case UFOState::Destroyed:
			DestroyedStart();
		default:
			break;
		}
	}
	CurState = _State;
}

void AMonoEye_UFO::None(float _DeltaTime)
{
	StateChange(UFOState::Idle);
	return;
}

void AMonoEye_UFO::Idle(float _DeltaTime)
{
	AccCoolTime += _DeltaTime;
	if (AccCoolTime > CoolTime)
	{
		AccCoolTime = 0.0f;
		StateChange(UFOState::Charging);
	}
}

void AMonoEye_UFO::Charging(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(UFOState::Firing);
	}
}

void AMonoEye_UFO::Firing(float _DeltaTime)
{
	float AncientYSize = AncientCharactor->GetTransform().GetScale().Y;
	AncientCharactor->SetPosition({ 0,static_cast<int>(AncientCharactor->GetPosition().Y) % MaxYPosition });
	if (AncientYSize < CharactorMaxSize)
	{
		AncientCharactor->AddScale({ 0.f,500.f * _DeltaTime });
	}
	else
	{
		AncientCharactor->AddPosition({ 0.f,-2000.f * _DeltaTime });
	}

	AccFiring += _DeltaTime;
	if (AccFiring > FiringTime)
	{
		AccFiring = 0.0f;
		AncientCharactor->SetTransform({ {0,0},{600,200} });
		AncientCharactor->ActiveOff();

		ALaser* Laser = GetWorld()->SpawnActor<ALaser>();

		StateChange(UFOState::Idle);
		return;
	}
}

void AMonoEye_UFO::Destroyed(float _DeltaTime)
{
}

void AMonoEye_UFO::IdleStart()
{
	Renderer->ChangeAnimation("Idle", false, 0, 0.08f);
}

void AMonoEye_UFO::ChargingStart()
{
	Renderer->ChangeAnimation("Charging", false, 0, 0.08f);
}

void AMonoEye_UFO::FiringStart()
{
	Renderer->ChangeAnimation("Firing", false, 0, 0.08f);
	AncientCharactor->SetTransform({ {0,0},{600,200} });
	AncientCharactor->ActiveOn();
}

void AMonoEye_UFO::DestroyedStart()
{
	Body->SetImage("MonoEye_UFO_DestroyedFront.png");
	BrokenBackBody->ActiveOn();
	Collider->ActiveOff();
	Renderer->ActiveOff();
	AncientCharactor->ActiveOff();
}
