

#include "Attributes/AttributeDefault.h"
#include "GameplayEffectExtension.h"


UAttributeDefault::UAttributeDefault()
{
	InitHealth(1.0f);
	InitHealthMax(1.0f);

    InitShield(1.0f);
    InitShieldMax(1.0f);
    InitShieldRegen(1.0f);
    InitShieldRegenDelay(1.0f);
}


void UAttributeDefault::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
    if (Attribute == GetHealthAttribute())
        NewValue = FMath::Clamp(NewValue, 0.0f, GetHealthMax());
    else if (Attribute == GetShieldAttribute())
        NewValue = FMath::Clamp(NewValue, 0.0f, GetShieldMax());
}

void UAttributeDefault::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
     
    if (Data.EvaluatedData.Attribute == GetInDamageAttribute())
    {
        float damage = GetInDamage();
        float shield = GetShield();
        SetShield(FMath::Clamp(GetShield() - damage, 0.0f, GetShieldMax()));
        SetHealth(FMath::Clamp(GetHealth() - damage + shield, 0.0f, GetHealthMax()));
        SetInDamage(0.0f);
    }
}
