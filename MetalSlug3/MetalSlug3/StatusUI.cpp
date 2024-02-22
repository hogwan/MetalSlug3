#include "StatusUI.h"
#include "ContentsHelper.h"
#include "Marco.h"
AStatusUI::AStatusUI()
{
}

AStatusUI::~AStatusUI()
{
}

void AStatusUI::BeginPlay()
{
	StatusPanel = CreateImageRenderer(MT3RenderOrder::UI);
	StatusPanel->SetImage("Status.png");
	StatusPanel->SetTransform({ { 0,0 }, { 500,500 } });
	StatusPanel->CreateAnimation("Status", "Status.png", 0, 0, 0.08f, true);
	StatusPanel->CameraEffectOff();
	StatusPanel->ChangeAnimation("Status", true, 0, 0.08f);

	Arms_Units = CreateImageRenderer(MT3RenderOrder::UI);
	Arms_Units->SetImage("YellowFont.png");
	Arms_Units->SetTransform({ { -10,-3 }, { 500,500 } });
	Arms_Units->CreateAnimation("Arms", "YellowFont.png", 0, 37, 0.08f, true);
	Arms_Units->CameraEffectOff();

	Arms_Tens = CreateImageRenderer(MT3RenderOrder::UI);
	Arms_Tens->SetImage("YellowFont.png");
	Arms_Tens->SetTransform({ { -30,-3 }, { 500,500 } });
	Arms_Tens->CreateAnimation("Arms", "YellowFont.png", 0, 37, 0.08f, true);
	Arms_Tens->CameraEffectOff();

	Arms_Hundreds = CreateImageRenderer(MT3RenderOrder::UI);
	Arms_Hundreds->SetImage("YellowFont.png");
	Arms_Hundreds->SetTransform({ { -50,-3 }, { 500,500 } });
	Arms_Hundreds->CreateAnimation("Arms", "YellowFont.png", 0, 37, 0.08f, true);
	Arms_Hundreds->CameraEffectOff();

	Arms_Pistol = CreateImageRenderer(MT3RenderOrder::UI);
	Arms_Pistol->SetImage("YellowFont.png");
	Arms_Pistol->SetTransform({ { -30,-3 }, { 500,500 } });
	Arms_Pistol->CreateAnimation("Arms", "YellowFont.png", 0, 37, 0.08f, true);
	Arms_Pistol->CameraEffectOff();
	

	Bombs_Units = CreateImageRenderer(MT3RenderOrder::UI);
	Bombs_Units->SetImage("YellowFont.png");
	Bombs_Units->SetTransform({ { 50,-3 }, { 500,500 } });
	Bombs_Units->CreateAnimation("Arms", "YellowFont.png", 0, 37, 0.08f, true);
	Bombs_Units->CameraEffectOff();

	Bombs_Tens = CreateImageRenderer(MT3RenderOrder::UI);
	Bombs_Tens->SetImage("YellowFont.png");
	Bombs_Tens->SetTransform({ { 30,-3 }, { 500,500 } });
	Bombs_Tens->CreateAnimation("Arms", "YellowFont.png", 0, 37, 0.08f, true);
	Bombs_Tens->CameraEffectOff();
}

void AStatusUI::Tick(float _DeltaTime)
{
	int ArmsCount = UContentsHelper::Player->ArmsCount;
	int BombsCount = UContentsHelper::Player->BombsCount;
	EGunType GunType = UContentsHelper::Player->GunType;

	if (GunType == EGunType::Pistol)
	{
		Arms_Pistol->ActiveOn();
		Arms_Units->ActiveOff();
		Arms_Tens->ActiveOff();
		Arms_Hundreds->ActiveOff();
		Arms_Pistol->ChangeAnimation("Arms", true, 37, 0.08f);
	}
	else
	{
		Arms_Pistol->ActiveOff();
		DecideNumber(ArmsCount, Arms_Units, Arms_Tens, Arms_Hundreds);
	}

	DecideNumber(BombsCount, Bombs_Units, Bombs_Tens);
}

void AStatusUI::DecideNumber(int _Count, UImageRenderer* _UnitsRenderer, UImageRenderer* _TensRenderer, UImageRenderer* _HundredsRenderer)
{
	_UnitsRenderer->ActiveOn();

	if (_Count < 10)
	{
		_TensRenderer->ActiveOff();
	}
	else
	{
		_TensRenderer->ActiveOn();
	}

	if (_HundredsRenderer != nullptr)
	{
		if (_Count < 100)
		{
			_HundredsRenderer->ActiveOff();
		}
		else
		{
			_HundredsRenderer->ActiveOn();
		}
	}

	int Units = _Count % 10;

	_Count /= 10;

	int Tens = _Count % 10;

	_Count /= 10;

	int Hundreds = _Count % 10;


	SwitchNumber(Units, _UnitsRenderer);
	SwitchNumber(Tens, _TensRenderer);
	if (nullptr != _HundredsRenderer)
	{
		SwitchNumber(Hundreds, _HundredsRenderer);
	}
	
}

void AStatusUI::SwitchNumber(int _Count, UImageRenderer* _Renderer)
{
	switch (_Count)
	{
	case 0:
		_Renderer->ChangeAnimation("Arms", true, 26, 0.08f);
		break;
	case 1:
		_Renderer->ChangeAnimation("Arms", true, 27, 0.08f);
		break;
	case 2:
		_Renderer->ChangeAnimation("Arms", true, 28, 0.08f);
		break;
	case 3:
		_Renderer->ChangeAnimation("Arms", true, 29, 0.08f);
		break;
	case 4:
		_Renderer->ChangeAnimation("Arms", true, 30, 0.08f);
		break;
	case 5:
		_Renderer->ChangeAnimation("Arms", true, 31, 0.08f);
		break;
	case 6:
		_Renderer->ChangeAnimation("Arms", true, 32, 0.08f);
		break;
	case 7:
		_Renderer->ChangeAnimation("Arms", true, 33, 0.08f);
		break;
	case 8:
		_Renderer->ChangeAnimation("Arms", true, 34, 0.08f);
		break;
	case 9:
		_Renderer->ChangeAnimation("Arms", true, 35, 0.08f);
		break;
	default:
		break;
	}
}
