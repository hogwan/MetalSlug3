#include "ScoreUI.h"
#include "ContentsHelper.h"

AScoreUI::AScoreUI()
{
}

AScoreUI::~AScoreUI()
{
}

void AScoreUI::BeginPlay()
{
	Units = CreateImageRenderer(MT3RenderOrder::UI);
	Units->SetImage("NormalFont.png");
	Units->SetTransform({ { 0,0 }, { 500,500 } });
	Units->CreateAnimation("Score", "NormalFont.png", 0, 37, 0.08f, true);
	Units->CameraEffectOff();

	Tens = CreateImageRenderer(MT3RenderOrder::UI);
	Tens->SetImage("NormalFont.png");
	Tens->SetTransform({ { -20,0 }, { 500,500 } });
	Tens->CreateAnimation("Score", "NormalFont.png", 0, 37, 0.08f, true);
	Tens->CameraEffectOff();

	Hundreds = CreateImageRenderer(MT3RenderOrder::UI);
	Hundreds->SetImage("NormalFont.png");
	Hundreds->SetTransform({ { -40,0 }, { 500,500 } });
	Hundreds->CreateAnimation("Score", "NormalFont.png", 0, 37, 0.08f, true);
	Hundreds->CameraEffectOff();

	Thousands = CreateImageRenderer(MT3RenderOrder::UI);
	Thousands->SetImage("NormalFont.png");
	Thousands->SetTransform({ { -60,0 }, { 500,500 } });
	Thousands->CreateAnimation("Score", "NormalFont.png", 0, 37, 0.08f, true);
	Thousands->CameraEffectOff();

	TenThousands = CreateImageRenderer(MT3RenderOrder::UI);
	TenThousands->SetImage("NormalFont.png");
	TenThousands->SetTransform({ { -80,0 }, { 500,500 } });
	TenThousands->CreateAnimation("Score", "NormalFont.png", 0, 37, 0.08f, true);
	TenThousands->CameraEffectOff();

	HundredThousands = CreateImageRenderer(MT3RenderOrder::UI);
	HundredThousands->SetImage("NormalFont.png");
	HundredThousands->SetTransform({ { -100,0 }, { 500,500 } });
	HundredThousands->CreateAnimation("Score", "NormalFont.png", 0, 37, 0.08f, true);
	HundredThousands->CameraEffectOff();

	Millions = CreateImageRenderer(MT3RenderOrder::UI);
	Millions->SetImage("NormalFont.png");
	Millions->SetTransform({ { -120,0 }, { 500,500 } });
	Millions->CreateAnimation("Score", "NormalFont.png", 0, 37, 0.08f, true);
	Millions->CameraEffectOff();
	
}

void AScoreUI::Tick(float _DeltaTime)
{
	int Score = UContentsHelper::Score;
	DecideNumber(Score);
}

void AScoreUI::DecideNumber(int _Count)
{
	Units->ActiveOn();

	if (_Count < 10)
	{
		Tens->ActiveOff();
	}
	else
	{
		Tens->ActiveOn();
	}

	if (_Count < 100)
	{
		Hundreds->ActiveOff();
	}
	else
	{
		Hundreds->ActiveOn();
	}

	if (_Count < 1000)
	{
		Thousands->ActiveOff();
	}
	else
	{
		Thousands->ActiveOn();
	}

	if (_Count < 10000)
	{
		TenThousands->ActiveOff();
	}
	else
	{
		TenThousands->ActiveOn();
	}

	if (_Count < 100000)
	{
		HundredThousands->ActiveOff();
	}
	else
	{
		HundredThousands->ActiveOn();
	}

	if (_Count < 1000000)
	{
		Millions->ActiveOff();
	}
	else
	{
		Millions->ActiveOn();
	}

	int _Units = _Count % 10;

	_Count /= 10;

	int _Tens = _Count % 10;

	_Count /= 10;

	int _Hundreds = _Count % 10;

	_Count /= 10;

	int _Thousands = _Count % 10;

	_Count /= 10;

	int _TenThousands = _Count % 10;

	_Count /= 10;

	int _HundredThousands = _Count % 10;

	_Count /= 10;

	int _Millions = _Count % 10;

	_Count /= 10;


	SwitchNumber(_Units, Units);
	SwitchNumber(_Tens, Tens);
	SwitchNumber(_Hundreds, Hundreds);
	SwitchNumber(_Thousands, Thousands);
	SwitchNumber(_TenThousands, TenThousands);
	SwitchNumber(_HundredThousands, HundredThousands);
	SwitchNumber(_Millions, Millions);

}

void AScoreUI::SwitchNumber(int _Count, UImageRenderer* _Renderer)
{
	switch (_Count)
	{
	case 0:
		_Renderer->ChangeAnimation("Score", true, 26, 0.08f);
		break;
	case 1:
		_Renderer->ChangeAnimation("Score", true, 27, 0.08f);
		break;
	case 2:
		_Renderer->ChangeAnimation("Score", true, 28, 0.08f);
		break;
	case 3:
		_Renderer->ChangeAnimation("Score", true, 29, 0.08f);
		break;
	case 4:
		_Renderer->ChangeAnimation("Score", true, 30, 0.08f);
		break;
	case 5:
		_Renderer->ChangeAnimation("Score", true, 31, 0.08f);
		break;
	case 6:
		_Renderer->ChangeAnimation("Score", true, 32, 0.08f);
		break;
	case 7:
		_Renderer->ChangeAnimation("Score", true, 33, 0.08f);
		break;
	case 8:
		_Renderer->ChangeAnimation("Score", true, 34, 0.08f);
		break;
	case 9:
		_Renderer->ChangeAnimation("Score", true, 35, 0.08f);
		break;
	default:
		break;
	}
}
