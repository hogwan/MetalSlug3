#pragma once
class EliteHelicopterProjectile
{
public:
	// constructor destructor
	EliteHelicopterProjectile();
	~EliteHelicopterProjectile();

	// delete Function
	EliteHelicopterProjectile(const EliteHelicopterProjectile& _Other) = delete;
	EliteHelicopterProjectile(EliteHelicopterProjectile&& _Other) noexcept = delete;
	EliteHelicopterProjectile& operator=(const EliteHelicopterProjectile& _Other) = delete;
	EliteHelicopterProjectile& operator=(EliteHelicopterProjectile&& _Other) = delete;
};

