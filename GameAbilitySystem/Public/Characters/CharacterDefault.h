
#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayCharacter.h"
#include "GameplayEffectTypes.h"

#include "CharacterDefault.generated.h"


UCLASS()
class GASAPPLIED_API ACharacterDefault : public ABaseGameplayCharacter
{
	GENERATED_BODY()
	
protected:
	ACharacterDefault();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:

	UPROPERTY()
	class UAttributeDefault* AttributeDefault;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Abilities")
	void OnHealthChanged(float OldValue, float NewValue, float MaxValue);

	FDelegateHandle HealthChangedHandle;


	UFUNCTION(BlueprintImplementableEvent, Category = "Abilities")
	void OnShieldChanged(float OldValue, float NewValue, float MaxValue);

	FDelegateHandle ShieldChangedHandle;




protected:
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	virtual void ApplyDamageSetbyCallerToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass, FGameplayTag DataTag, float Magnitude);
	
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	virtual void ApplyDamageSetbyCallerSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, FGameplayTag DataTag, float Magnitude);

};
