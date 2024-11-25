
#include "BaseGameplayAttribute.h"



UBaseGameplayAttribute::UBaseGameplayAttribute()
{
    
}


void UBaseGameplayAttribute::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::PreAttributeBaseChange(Attribute, NewValue);

    ClampAttributeOnChange(Attribute, NewValue);
}

void UBaseGameplayAttribute::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    ClampAttributeOnChange(Attribute, NewValue);
}

void UBaseGameplayAttribute::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);

    ClampAttributeOnChange(Attribute, NewValue);
}


void UBaseGameplayAttribute::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
}