#include "MonoEye_UFO.h"

MonoEye_UFO::MonoEye_UFO()
{
}

MonoEye_UFO::~MonoEye_UFO()
{
}

void MonoEye_UFO::BeginPlay()
{
	SetActorLocation({ 14150,2050 });

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ {0,0},{750,750} });
	Renderer->CreateAnimation("Idle", "MonoEye_UFO_Idle.png", 0, 4,0.08f, true);
	Renderer->CreateAnimation("Charging", "MonoEye_UFO_Charging.png", 0, 3,0.08f, false);
	Renderer->CreateAnimation("Firing", "MonoEye_UFO_Firing.png", 0, 5, 0.08f, true);

	Body = CreateImageRenderer(MT3RenderOrder::UFO_Body);
	Body->SetImage("MonoEye_UFO_Body.png");
	Body->SetTransform({ {0,205},{750,750} });

	BrokenBackBody = CreateImageRenderer(MT3RenderOrder::UFO_BackBody);
	BrokenBackBody->SetImage("MonoEye_UFO_DestroyedBack.png");
	BrokenBackBody->SetTransform({ {0,205},{750,750} });

	AncientCharactor = CreateImageRenderer(MT3RenderOrder::UFO_AncientCharactor);
	AncientCharactor->SetImage("AncientCharacter.png");
	AncientCharactor->SetTransform({ {0,0},{600,200} });
	AncientCharactor->ActiveOff();

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetTransform({ {0,0},{300,200} });
	Collider->SetColType(ECollisionType::Rect);
}

void MonoEye_UFO::Tick(float _DeltaTime)
{
	StateUpdate(_DeltaTime);
}

void MonoEye_UFO::StateUpdate(float _DeltaTime)
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
	default:
		break;
	}
}

void MonoEye_UFO::StateChange(UFOState _State)
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
		default:
			break;
		}
	}
	CurState = _State;
}

void MonoEye_UFO::None(float _DeltaTime)
{
	StateChange(UFOState::Idle);
	return;
}

void MonoEye_UFO::Idle(float _DeltaTime)
{
	AccCoolTime += _DeltaTime;
	if (AccCoolTime > CoolTime)
	{
		AccCoolTime = 0.0f;
		StateChange(UFOState::Charging);
	}
}

void MonoEye_UFO::Charging(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(UFOState::Firing);
	}
}

void MonoEye_UFO::Firing(float _DeltaTime)
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
		StateChange(UFOState::Idle);
		return;
	}
}

void MonoEye_UFO::IdleStart()
{
	Renderer->ChangeAnimation("Idle", false, 0, 0.08);
}

void MonoEye_UFO::ChargingStart()
{
	Renderer->ChangeAnimation("Charging", false, 0, 0.08);
}

void MonoEye_UFO::FiringStart()
{
	Renderer->ChangeAnimation("Firing", false, 0, 0.08);
	AncientCharactor->SetTransform({ {0,0},{600,200} });
	AncientCharactor->ActiveOn();
}
