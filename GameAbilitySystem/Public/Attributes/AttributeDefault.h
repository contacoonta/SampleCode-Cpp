// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAttribute.h"
#include "AbilitySystemComponent.h"

#include "AttributeDefault.generated.h"


UCLASS()
class GASAPPLIED_API UAttributeDefault : public UBaseGameplayAttribute
{
	GENERATED_BODY()
	
protected:

	UAttributeDefault();

	virtual void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

public: // Damage
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData InDamage;
	ATTRIBUTE_ACCESSORS(UAttributeDefault, InDamage)

public: // Health

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAttributeDefault, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData HealthMax;
	ATTRIBUTE_ACCESSORS(UAttributeDefault, HealthMax)


public: // Shield

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(UAttributeDefault, Shield)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData ShieldMax;
	ATTRIBUTE_ACCESSORS(UAttributeDefault, ShieldMax)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData ShieldRegen;
	ATTRIBUTE_ACCESSORS(UAttributeDefault, ShieldRegen)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData ShieldRegenDelay;
	ATTRIBUTE_ACCESSORS(UAttributeDefault, ShieldRegenDelay)
};
