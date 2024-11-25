#include "Characters/CharacterDefault.h"
#include "Attributes/AttributeDefault.h"
#include "GameplayEffectTypes.h"
#include <AbilitySystemBlueprintLibrary.h>


ACharacterDefault::ACharacterDefault()
{
	AttributeDefault = CreateDefaultSubobject<UAttributeDefault>(TEXT("AttributeDefault"));
}

void ACharacterDefault::BeginPlay()
{
	Super::BeginPlay();

    if (AbilitySystemComponent)
    {
        HealthChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeDefault->GetHealthAttribute())
            .AddLambda([this](const FOnAttributeChangeData& Data) { OnHealthChanged(Data.OldValue, Data.NewValue, AttributeDefault->GetHealthMax()); });

        ShieldChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeDefault->GetShieldAttribute())
            .AddLambda([this](const FOnAttributeChangeData& Data) { OnShieldChanged(Data.OldValue, Data.NewValue, AttributeDefault->GetShieldMax()); });
    }
}

void ACharacterDefault::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (AbilitySystemComponent)
    {        
        if (HealthChangedHandle.IsValid())
            AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeDefault->GetHealthAttribute())
                .Remove(HealthChangedHandle);

        if (ShieldChangedHandle.IsValid())
            AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeDefault->GetShieldAttribute())
                .Remove(ShieldChangedHandle);
    }

    Super::EndPlay(EndPlayReason);
}


/*
* Damage ฐüทร
*/

void ACharacterDefault::ApplyDamageSetbyCallerToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass, FGameplayTag DataTag, float Magnitude)
{
    if (!AbilitySystemComponent || !GameplayEffectClass || !TargetActor) return;
    
    UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
    if (!TargetASC)
    {
        return;
    }

    FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.0f, AbilitySystemComponent->MakeEffectContext());

    if (SpecHandle.IsValid())
    {
        SpecHandle.Data->SetSetByCallerMagnitude(DataTag, Magnitude);

        AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
    }
}

void ACharacterDefault::ApplyDamageSetbyCallerSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, FGameplayTag DataTag, float Magnitude)
{
    if (AbilitySystemComponent && GameplayEffectClass)
    {
        FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.0f, AbilitySystemComponent->MakeEffectContext());

        if (SpecHandle.IsValid())
        {
            SpecHandle.Data->SetSetByCallerMagnitude(DataTag, Magnitude);

            AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
        }
    }
}


