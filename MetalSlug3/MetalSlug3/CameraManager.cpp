#include "CameraManager.h"
#include "ContentsHelper.h"
#include "Marco.h"

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

void CameraManager::BeginPlay()
{
}

void CameraManager::Tick(float _DeltaTime)
{
	CameraUpdate(_DeltaTime);
}

void CameraManager::CameraUpdate(float _DeltaTime)
{
	FVector CameraPos = GetWorld()->GetCameraPos();
	FVector PlayerPos = UContentsHelper::Player->GetActorLocation();
	float XGap = PlayerPos.X - CameraPos.X;

	CameraMode;

	switch (CameraMode)
	{
	case 0:
	{
		if (XGap > 300.0f)
		{
			CameraSpeed = XGap - 180.0f;
			GetWorld()->AddCameraPos(FVector::Right * CameraSpeed * _DeltaTime);
		}
		else
		{
			CameraSpeed = 0.0f;
		}
	}
	break;
	case 1:
	{
		if (CameraPos.X + 800.0f > 1960.0f)
		{
			return;
		}
		
		if (XGap > 300.0f)
		{
			CameraSpeed = XGap - 180.0f;
			GetWorld()->AddCameraPos(FVector::Right * CameraSpeed * _DeltaTime);
		}
		else
		{
			CameraSpeed = 0.0f;
		}
	}
	break;
	case 2:
	{
		if (XGap > 300.0f)
		{
			CameraSpeed = XGap - 180.0f;
			GetWorld()->AddCameraPos(FVector::Right * CameraSpeed * _DeltaTime);
		}
		else
		{
			CameraSpeed = 0.0f;
		}
	}
	break;
	case 3:
	{
		float TargetY = 969.0f;
		float CameraBottomPos = CameraPos.Y + 600.0f;
		if (XGap > 300.0f)
		{
			CameraSpeed = XGap - 180.0f;
			GetWorld()->AddCameraPos(FVector::Right * CameraSpeed * _DeltaTime);
		}

		if (CameraBottomPos > TargetY)
		{
			CameraSpeed = 500.0f;
			GetWorld()->AddCameraPos(FVector::Up * CameraSpeed * _DeltaTime);
		}
	}
	break;
	case 4:
	{
		float TargetY = PlayerPos.Y + 60;
		float CameraBottomPos = CameraPos.Y + 600.0f;
		if (XGap > 300.0f)
		{
			CameraSpeed = XGap - 180.0f;
			GetWorld()->AddCameraPos(FVector::Right * CameraSpeed * _DeltaTime);
		}

		if (CameraBottomPos < TargetY)
		{
			CameraSpeed = 500.0f;
			GetWorld()->AddCameraPos(FVector::Down * CameraSpeed * _DeltaTime);
		}
	}
	break;
	case 5:
	{
		float TargetY = 1483;
		float TargetX = 7275;
		float CameraBottomPosY = CameraPos.Y + 600.0f;
		float CameraRightPosX = CameraPos.X + 800.0f;

		if (abs(CameraBottomPosY - TargetY) < 1.0f && abs(CameraRightPosX > TargetX) < 1.0f)
		{
			return;
		}

		FVector DirVector = { (TargetX - CameraRightPosX), (TargetY - CameraBottomPosY) };
		CameraSpeed = 1000.0f;
		DirVector.Normalize2D();
		GetWorld()->AddCameraPos(DirVector * CameraSpeed * _DeltaTime);
	}
	break;
	case 6:
	{
		float TargetY = 1869;
		float CameraBottomPos = CameraPos.Y + 600.0f;
		if (XGap > 300.0f)
		{
			CameraSpeed = XGap - 180.0f;
			GetWorld()->AddCameraPos(FVector::Right * CameraSpeed * _DeltaTime);
		}

		if (CameraBottomPos < TargetY)
		{
			CameraSpeed = 1000.0f;
			GetWorld()->AddCameraPos(FVector::Down * CameraSpeed * _DeltaTime);
		}
	}
	break;
	case 7:
	{
		float TargetY = PlayerPos.Y + 100;
		float CameraBottomPos = CameraPos.Y + 600.0f;
		if (XGap > 300.0f)
		{
			CameraSpeed = XGap - 180.0f;
			GetWorld()->AddCameraPos(FVector::Right * CameraSpeed * _DeltaTime);
		}

		if (CameraBottomPos < TargetY)
		{
			CameraSpeed = 500.0f;
			GetWorld()->AddCameraPos(FVector::Down * CameraSpeed * _DeltaTime);
		}
	}
	break;
	case 8:
	{
		float TargetY = 2255;
		float CameraBottomPos = CameraPos.Y + 600.0f;
		if (XGap > 300.0f)
		{
			CameraSpeed = XGap - 180.0f;
			GetWorld()->AddCameraPos(FVector::Right * CameraSpeed * _DeltaTime);
		}

		FVector DirVector = { 0.f,TargetY - CameraBottomPos };

		if (abs(TargetY - CameraBottomPos) < 1.0f)
		{
			return;
		}

		DirVector.Normalize2D();
		CameraSpeed = 1000.0f;
		GetWorld()->AddCameraPos(DirVector * CameraSpeed * _DeltaTime);
	}
	break;
	case 9:
	{
		if (CameraPos.X + 800.0f > 9550.0f)
		{
			return;
		}

		if (XGap > 300.0f)
		{
			CameraSpeed = XGap - 180.0f;
			GetWorld()->AddCameraPos(FVector::Right * CameraSpeed * _DeltaTime);
		}
		else
		{
			CameraSpeed = 0.0f;
		}
	}
	break;
	case 10:
	{
		float TargetY = PlayerPos.Y + 100;
		float CameraBottomPos = CameraPos.Y + 600.0f;
		if (XGap > 300.0f)
		{
			CameraSpeed = XGap - 180.0f;
			GetWorld()->AddCameraPos(FVector::Right * CameraSpeed * _DeltaTime);
		}

		if (CameraBottomPos < TargetY)
		{
			CameraSpeed = 500.0f;
			GetWorld()->AddCameraPos(FVector::Down * CameraSpeed * _DeltaTime);
		}
	}
	break;
	case 11:
	{
		float EndX = 14572;
		float TargetY = 2427;
		float CameraBottomPos = CameraPos.Y + 600.0f;
		float CameraRightPos = CameraPos.X + 800.0f;
		if (EndX < CameraRightPos)
		{
			return;
		}

		if (XGap > 300.0f)
		{
			CameraSpeed = XGap - 180.0f;
			GetWorld()->AddCameraPos(FVector::Right * CameraSpeed * _DeltaTime);
		}

		FVector DirVector = { 0.f,TargetY - CameraBottomPos };

		if (abs(TargetY - CameraBottomPos) < 1.0f)
		{
			return;
		}

		DirVector.Normalize2D();
		CameraSpeed = 1000.0f;
		GetWorld()->AddCameraPos(DirVector * CameraSpeed * _DeltaTime);
	}
	break;
	default:
		break;
	}
}
