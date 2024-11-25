
#include "BaseGameplayCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilities/Public/Abilities/GameplayAbility.h"
#include "GameplayEffect.h"


ABaseGameplayCharacter::ABaseGameplayCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
}

UAbilitySystemComponent* ABaseGameplayCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseGameplayCharacter::InitAbilitySystemComponent()
{
	 if (!AbilitySystemComponent) return;

	 GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
}



void ABaseGameplayCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystemComponent();

	GiveAbilities();
	GiveEffects();
}

void ABaseGameplayCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystemComponent();
	
	ClearAllAbilities();
	GiveAbilities();
	GiveEffects();
}




/*
* Gameplay Abilities
*/

void ABaseGameplayCharacter::GiveAbilities()
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : AbilitiesBase)
	{
		if (AbilityClass)
		{
			UGameplayAbility* Ability = AbilityClass.GetDefaultObject();
			if (Ability)
				FGameplayAbilitySpecHandle spec = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(Ability));
		}
	}
}

void ABaseGameplayCharacter::ClearAllAbilities()
{
	if (!AbilitySystemComponent) return;

	GetAbilitySystemComponent()->ClearAllAbilities();
}


bool ABaseGameplayCharacter::ActivateAbilitiesByTag()
{
	if (!AbilitySystemComponent || AbilityTags.Num() <= 0) return false;
		
	return GetAbilitySystemComponent()->TryActivateAbilitiesByTag(AbilityTags);
}



/*
* Gameplay Effects
*/

void ABaseGameplayCharacter::GiveEffects()
{
	if (!AbilitySystemComponent) return;


	FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContext.AddSourceObject(this);	

	int32 ClampedLevel = FMath::Clamp(EffectsLevel, 0, 100);

	for (TSubclassOf<UGameplayEffect> EffectClass : EffectsBase)
	{
		FGameplayEffectSpecHandle NewHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(EffectClass, ClampedLevel, EffectContext);

		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
	}
}