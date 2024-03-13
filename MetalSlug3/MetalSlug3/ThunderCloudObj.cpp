#include "ThunderCloudObj.h"
#include "ContentsHelper.h"
#include "Marco.h"
#include "ThunderGround.h"

ThunderCloudObj::ThunderCloudObj()
{
}

ThunderCloudObj::~ThunderCloudObj()
{
}

void ThunderCloudObj::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->CreateAnimation("Idle", "ThunderCloudObj.png", 0, 7, 0.03f,true);
	Renderer->CreateAnimation("Move", "ThunderCloudObj.png", 8, 15, 0.03f,true);
	Renderer->CreateAnimation("Attack", "ThunderCloudObj.png", 16, 39, 0.001f,false);


	Detect = CreateCollision(MT3CollisionOrder::Detect);
	Detect->SetTransform({ {0,300},{1000,600} });
	Detect->SetColType(ECollisionType::Rect);
}

void ThunderCloudObj::Tick(float _DeltaTime)
{
	StateUpdate(_DeltaTime);

	if (RemainLaunchNum <= 0)
	{
		Destroy();
	}
}

void ThunderCloudObj::StateUpdate(float _DeltaTime)
{
	switch (CurState)
	{
	case CloudState::None:
		None(_DeltaTime);
		break;
	case CloudState::Idle:
		Idle(_DeltaTime);
		break;
	case CloudState::Move:
		Move(_DeltaTime);
		break;
	case CloudState::Attack:
		Attack(_DeltaTime);
		break;
	default:
		break;
	}
}

void ThunderCloudObj::StateChange(CloudState _State)
{
	if (CurState != _State)
	{
		switch (_State)
		{
		case CloudState::None:
			NoneStart();
			break;
		case CloudState::Idle:
			IdleStart();
			break;
		case CloudState::Move:
			MoveStart();
			break;
		case CloudState::Attack:
			AttackStart();
			break;
		default:
			break;
		}
	}

	CurState = _State;
}

void ThunderCloudObj::None(float _DeltaTime)
{
	StateChange(CloudState::Idle);
	return;
}

void ThunderCloudObj::Idle(float _DeltaTime)
{
	TargetPos = { UContentsHelper::Player->GetActorLocation().X, GetWorld()->GetCameraPos().Y + 100 };
	float XGap = TargetPos.X - GetActorLocation().X;
	MoveVector = TargetPos - GetActorLocation();

	if (abs(XGap) > 3.0f)
	{
		AddActorLocation(MoveVector * _DeltaTime);
	}

	if (UEngineInput::IsDown('A') || UEngineInput::IsDown('a'))
	{
		std::vector<UCollision*> Result;
		if (Detect->CollisionCheck(MT3CollisionOrder::Enemy, Result))
		{
			TargetPos.X = Result[0]->GetOwner()->GetActorLocation().X;
			StateChange(CloudState::Move);
			return;
		}
	}
}

void ThunderCloudObj::Move(float _DeltaTime)
{
	float XGap = TargetPos.X - GetActorLocation().X;
	MoveVector = TargetPos - GetActorLocation();
	MoveVector.Normalize2D();;

	if (abs(XGap) > 10.0f)
	{
		AddActorLocation(MoveVector * Speed * _DeltaTime);
	}
	else
	{
		StateChange(CloudState::Attack);
		return;
	}
}

void ThunderCloudObj::Attack(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(CloudState::Idle);
		return;
	}
}

void ThunderCloudObj::NoneStart()
{
}

void ThunderCloudObj::IdleStart()
{
	Renderer->ChangeAnimation("Idle", false, 0, 0.03f);
}

void ThunderCloudObj::MoveStart()
{
	Renderer->ChangeAnimation("Move", false, 0, 0.03f);
}

void ThunderCloudObj::AttackStart()
{
	DetectGround = static_cast<int>(GetActorLocation().Y);
	while (true)
	{
		Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), DetectGround, Color8Bit::MagentaA);
		if (Color == Color8Bit(255, 0, 255, 0))
		{
			ThunderGround* TG = GetWorld()->SpawnActor<ThunderGround>();
			TG->SetActorLocation({ GetActorLocation().iX(), DetectGround});
			TG->ThunderSize = DetectGround;
			--RemainLaunchNum;
			break;
		}
		else
		{
			DetectGround += 1;
		}
	}


	Renderer->ChangeAnimation("Attack", false, 0, 0.03f);
}
