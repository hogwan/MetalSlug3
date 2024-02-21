#include "Time.h"
#include "ContentsHelper.h"
#include "Marco.h"

ATime::ATime()
{
}

ATime::~ATime()
{
}

void ATime::BeginPlay()
{
	Units = CreateImageRenderer(MT3RenderOrder::UI);
	Units->SetImage("TimeNumber.png");
	Units->SetTransform({ { 20,0 }, { 500,500 } });
	Units->CameraEffectOff();
	Units->SetImageCuttingTransform({ {1600,0},{200,200} });

	Units->CreateAnimation("Zero", "TimeNumber.png", 0, 0, 0.08f, true);
	Units->CreateAnimation("One", "TimeNumber.png", 1, 1, 0.08f, true);
	Units->CreateAnimation("Two", "TimeNumber.png", 2, 2, 0.08f, true);
	Units->CreateAnimation("Three", "TimeNumber.png", 3, 3, 0.08f, true);
	Units->CreateAnimation("Four", "TimeNumber.png", 4, 4, 0.08f, true);
	Units->CreateAnimation("Five", "TimeNumber.png", 5, 5, 0.08f, true);
	Units->CreateAnimation("Six", "TimeNumber.png", 6, 6, 0.08f, true);
	Units->CreateAnimation("Seven", "TimeNumber.png", 7, 7, 0.08f, true);
	Units->CreateAnimation("Eight", "TimeNumber.png", 8, 8, 0.08f, true);
	Units->CreateAnimation("Nine", "TimeNumber.png", 9, 9, 0.08f, true);

	Tens = CreateImageRenderer(MT3RenderOrder::UI);
	Tens->SetImage("TimeNumber.png");
	Tens->SetTransform({ { -20,0 }, { 500,500 } });
	Tens->CameraEffectOff();

	Tens->CreateAnimation("Zero", "TimeNumber.png", 0, 0, 0.08f, true);
	Tens->CreateAnimation("One", "TimeNumber.png", 1, 1, 0.08f, true);
	Tens->CreateAnimation("Two", "TimeNumber.png", 2, 2, 0.08f, true);
	Tens->CreateAnimation("Three", "TimeNumber.png", 3, 3, 0.08f, true);
	Tens->CreateAnimation("Four", "TimeNumber.png", 4, 4, 0.08f, true);
	Tens->CreateAnimation("Five", "TimeNumber.png", 5, 5, 0.08f, true);
	Tens->CreateAnimation("Six", "TimeNumber.png", 6, 6, 0.08f, true);
	Tens->CreateAnimation("Seven", "TimeNumber.png", 7, 7, 0.08f, true);
	Tens->CreateAnimation("Eight", "TimeNumber.png", 8, 8, 0.08f, true);
	Tens->CreateAnimation("Nine", "TimeNumber.png", 9, 9, 0.08f, true);
}

void ATime::Tick(float _DeltaTime)
{
	if (RemainTime < 0.0f)
	{
		UContentsHelper::Player->IsDeath = true;
		RemainTime = 60;
	}

	UCollision* ScreenCollider = UContentsHelper::ScreenCol->GetCollider();
	std::vector<UCollision*> Result;
	if (false == ScreenCollider->CollisionCheck(MT3CollisionOrder::Enemy, Result))
	{
		RemainTime -= _DeltaTime/2.0f;
	}

	int _Units = static_cast<int>(RemainTime) % 10;
	int _Tens = static_cast<int>(RemainTime) / 10;

	switch(_Units)
	{
	case 0 :
		Units->ChangeAnimation("Zero");
		break;
	case 1:
		Units->ChangeAnimation("One");
		break;
	case 2:
		Units->ChangeAnimation("Two");
		break;
	case 3:
		Units->ChangeAnimation("Three");
		break;
	case 4:
		Units->ChangeAnimation("Four");
		break;
	case 5:
		Units->ChangeAnimation("Five");
		break;
	case 6:
		Units->ChangeAnimation("Six");
		break;
	case 7:
		Units->ChangeAnimation("Seven");
		break;
	case 8:
		Units->ChangeAnimation("Eight");
		break;
	case 9:
		Units->ChangeAnimation("Nine");
		break;
	default:
		break;
	}

	switch (_Tens)
	{
	case 0:
		Tens->ChangeAnimation("Zero");
		break;
	case 1:
		Tens->ChangeAnimation("One");
		break;
	case 2:
		Tens->ChangeAnimation("Two");
		break;
	case 3:
		Tens->ChangeAnimation("Three");
		break;
	case 4:
		Tens->ChangeAnimation("Four");
		break;
	case 5:
		Tens->ChangeAnimation("Five");
		break;
	case 6:
		Tens->ChangeAnimation("Six");
		break;
	case 7:
		Tens->ChangeAnimation("Seven");
		break;
	case 8:
		Tens->ChangeAnimation("Eight");
		break;
	case 9:
		Tens->ChangeAnimation("Nine");
		break;
	default:
		break;

	}
}
