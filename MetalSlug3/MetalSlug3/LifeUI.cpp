#include "LifeUI.h"
#include "ContentsHelper.h"

ALifeUI::ALifeUI()
{
}

ALifeUI::~ALifeUI()
{
}

void ALifeUI::BeginPlay()
{
	Renderer0 = CreateImageRenderer(MT3RenderOrder::UI);
	Renderer0->SetImage("YellowFont.png");
	Renderer0->SetTransform({ { 0,0 }, { 500,500 } });
	Renderer0->CreateAnimation("1", "YellowFont.png", 0, 37, 0.08f, true);
	Renderer0->CameraEffectOff();

	Renderer1 = CreateImageRenderer(MT3RenderOrder::UI);
	Renderer1->SetImage("YellowFont.png");
	Renderer1->SetTransform({ { 20,0 }, { 500,500 } });
	Renderer1->CreateAnimation("U", "YellowFont.png", 0, 37, 0.08f, true);
	Renderer1->CameraEffectOff();

	Renderer2 = CreateImageRenderer(MT3RenderOrder::UI);
	Renderer2->SetImage("YellowFont.png");
	Renderer2->SetTransform({ { 40,0 }, { 500,500 } });
	Renderer2->CreateAnimation("P", "YellowFont.png", 0, 37, 0.08f, true);
	Renderer2->CameraEffectOff();

	Renderer3 = CreateImageRenderer(MT3RenderOrder::UI);
	Renderer3->SetImage("YellowFont.png");
	Renderer3->SetTransform({ { 60,0 }, { 500,500 } });
	Renderer3->CreateAnimation("=", "YellowFont.png", 0, 37, 0.08f, true);
	Renderer3->CameraEffectOff();

	Renderer4 = CreateImageRenderer(MT3RenderOrder::UI);
	Renderer4->SetImage("YellowFont.png");
	Renderer4->SetTransform({ { 80,0 }, { 500,500 } });
	Renderer4->CreateAnimation("Life", "YellowFont.png", 0, 37, 0.08f, true);
	Renderer4->CameraEffectOff();
}

void ALifeUI::Tick(float _DeltaTime)
{
	Renderer0->ChangeAnimation("1", true, 27, 0.08f);
	Renderer1->ChangeAnimation("U", true, 20, 0.08f);
	Renderer2->ChangeAnimation("P", true, 15, 0.08f);
	Renderer3->ChangeAnimation("=", true, 36, 0.08f);
	
	int Life = UContentsHelper::Life;
	SwitchNumber(Life, Renderer4);
}

void ALifeUI::SwitchNumber(int _Count, UImageRenderer* _Renderer)
{
	switch (_Count)
	{
	case 0:
		_Renderer->ChangeAnimation("Life", true, 26, 0.08f);
		break;
	case 1:
		_Renderer->ChangeAnimation("Life", true, 27, 0.08f);
		break;
	case 2:
		_Renderer->ChangeAnimation("Life", true, 28, 0.08f);
		break;
	case 3:
		_Renderer->ChangeAnimation("Life", true, 29, 0.08f);
		break;
	case 4:
		_Renderer->ChangeAnimation("Life", true, 30, 0.08f);
		break;
	case 5:
		_Renderer->ChangeAnimation("Life", true, 31, 0.08f);
		break;
	case 6:
		_Renderer->ChangeAnimation("Life", true, 32, 0.08f);
		break;
	case 7:
		_Renderer->ChangeAnimation("Life", true, 33, 0.08f);
		break;
	case 8:
		_Renderer->ChangeAnimation("Life", true, 34, 0.08f);
		break;
	case 9:
		_Renderer->ChangeAnimation("Life", true, 35, 0.08f);
		break;
	default:
		break;
	}
}
