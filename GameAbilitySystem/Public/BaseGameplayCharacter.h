
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

#include "BaseGameplayCharacter.generated.h"



UCLASS()
class GASAPPLIED_API ABaseGameplayCharacter : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseGameplayCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	void InitAbilitySystemComponent();

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;


public:
	
	// 발동시킬 Ability Tags
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities", meta = (Categories = "Ability"))
	FGameplayTagContainer AbilityTags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> AbilitiesBase;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> EffectsBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	int32 EffectsLevel;


public:
	
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	virtual void GiveAbilities();

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	virtual void ClearAllAbilities();

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	virtual bool ActivateAbilitiesByTag();


public:

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	virtual void GiveEffects();


};
