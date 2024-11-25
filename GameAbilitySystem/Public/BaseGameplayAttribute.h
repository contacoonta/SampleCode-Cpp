
#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "BaseGameplayAttribute.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class GASAPPLIED_API UBaseGameplayAttribute : public UAttributeSet
{
	GENERATED_BODY()

public:
    UBaseGameplayAttribute();
	
    virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

protected:
    virtual void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const;

};
