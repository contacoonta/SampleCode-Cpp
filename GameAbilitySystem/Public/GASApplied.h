// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

//UENUM(BlueprintType)
//enum class EAbilityInputID : uint8
//{
//	None,
//	Confirm,
//	Cancel,
//	PrimaryAbility,
//	SecondaryAbility,
//	Weaponfire
//};

class FGASAppliedModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
