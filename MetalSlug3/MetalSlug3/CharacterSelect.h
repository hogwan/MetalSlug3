#pragma once
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineSound.h>
class CharacterSelect : public ULevel
{
public:
	// constructor destructor
	CharacterSelect();
	~CharacterSelect();

	// delete Function
	CharacterSelect(const CharacterSelect& _Other) = delete;
	CharacterSelect(CharacterSelect&& _Other) noexcept = delete;
	CharacterSelect& operator=(const CharacterSelect& _Other) = delete;
	CharacterSelect& operator=(CharacterSelect&& _Other) = delete;

protected:
	void BeginPlay() override;
};

