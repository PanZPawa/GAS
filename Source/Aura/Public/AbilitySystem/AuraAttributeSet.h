// Copyright  Pzp

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

/**
 * 
 */
	#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//生命 生命上限
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing= OnRep_Health,Category = "Vital AttributeSet")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxHealth ,Category = "Vital AttributeSet")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData &oldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData &oldMaxHealth) const;
	
	//魔力 魔力上限
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Mana,Category = "Vital AttributeSet")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxMana,Category = "Vital AttributeSet")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData &oldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData &oldMaxMana) const;
};
