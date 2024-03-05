#include "MonoEyes.h"
#include "Marco.h"

AMonoEyes::AMonoEyes()
{
}

AMonoEyes::~AMonoEyes()
{
}

void AMonoEyes::BeginPlay()
{
	AEnemy::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ {0,0},{600,600} });

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({ 100,300 });
	Collider->SetPosition({ 0,-150 });
	Collider->SetColType(ECollisionType::Rect);

	SetActorLocation({ 14150,2050 });
	InitialPosition = { 14150,2050 };

}

void AMonoEyes::Tick(float _DeltaTime)
{
	AEnemy::Tick(_DeltaTime);

	RotAngle += (UEngineMath::PI/3.0f) * _DeltaTime;
	VibrationAngle += UEngineMath::PI * _DeltaTime;
	// -1 ~ 1
	float CurY = sinf(RotAngle);
	float CurX = cosf(RotAngle);
	float vibration = sinf(VibrationAngle);

	FVector YPos = FVector::Up * Ratio.Y * CurY;
	FVector XPos = FVector::Right * Ratio.X * CurX;

	SetActorLocation(InitialPosition + YPos + XPos);

	if (CurY > 0.4f)
	{
		CurZPos = ZPos::Back;
		Renderer->SetTransform({ {0,0},{550,550} });

		AttachName = "Back_";
	}
	else if (CurY <= 0.4f && CurY >= -0.2f)
	{
		CurZPos = ZPos::Mid;
		Renderer->SetTransform({ {0,0},{580,580} });

		AttachName = "Mid_";
	}
	else if(CurY < -0.2f)
	{
		CurZPos = ZPos::Front;
		Renderer->SetTransform({ {0,0},{600,600} });

		AttachName = "Front_";
	}

	Idle(_DeltaTime);
}
void AMonoEyes::Spawn(float _DeltaTime)
{
}

void AMonoEyes::Idle(float _DeltaTime)
{
	FVector PlayerPos = UContentsHelper::Player->GetActorLocation();
	float XGap = GetActorLocation().X - PlayerPos.X;

	if (CurZPos == ZPos::Front)
	{
		Renderer->SetOrder(MT3RenderOrder::MonoEye_Front);
	}
	else if (CurZPos == ZPos::Mid)
	{
		Renderer->SetOrder(MT3RenderOrder::MonoEye_Mid);
	}
	else
	{
		Renderer->SetOrder(MT3RenderOrder::MonoEye_Back);
	}


	if (CurZPos == ZPos::Back || CurZPos == ZPos::Mid)
	{
		if (XGap > 300.0f)
		{
			CurImageName = "Left_9.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 250.0f)
		{
			CurImageName = "Left_8.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 200.0f)
		{
			CurImageName = "Left_7.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 150.0f)
		{
			CurImageName = "Left_6.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 100.0f)
		{
			CurImageName = "Left_5.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 80.0f)
		{
			CurImageName = "Left_4.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 60.0f)
		{
			CurImageName = "Left_3.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 40.0f)
		{
			CurImageName = "Left_2.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 20.0f)
		{
			CurImageName = "Left_1.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 0.0f)
		{
			CurImageName = "Left_0.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -20.0f)
		{
			CurImageName = "Right_0.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -40.0f)
		{
			CurImageName = "Right_1.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -60.0f)
		{
			CurImageName = "Right_2.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -80.0f)
		{
			CurImageName = "Right_3.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -100.0f)
		{
			CurImageName = "Right_4.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -150.0f)
		{
			CurImageName = "Right_5.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -200.0f)
		{
			CurImageName = "Right_6.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -250.0f)
		{
			CurImageName = "Right_7.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -300.0f)
		{
			CurImageName = "Right_8.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else
		{
			CurImageName = "Right_9.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
	}
	else
	{
		if (XGap > 150.0f)
		{
			CurImageName = "Left_10.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 100.0f)
		{
			CurImageName = "Left_11.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 80.0f)
		{
			CurImageName = "Left_12.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 60.0f)
		{
			CurImageName = "Left_13.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 40.0f)
		{
			CurImageName = "Left_14.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 20.0f)
		{
			CurImageName = "Left_15.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > 0.0f)
		{
			CurImageName = "Left_16.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -20.0f)
		{
			CurImageName = "Right_16.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -40.0f)
		{
			CurImageName = "Right_15.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -60.0f)
		{
			CurImageName = "Right_14.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -80.0f)
		{
			CurImageName = "Right_13.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -100.0f)
		{
			CurImageName = "Right_12.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else if (XGap > -150.0f)
		{
			CurImageName = "Right_11.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
		else
		{
			CurImageName = "Right_10.png";
			std::string CurAnimName = AttachName + CurImageName;
			Renderer->SetImage(CurAnimName);
		}
	}
}
