// Copyright  Pzp

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

/**
 * 
 */
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
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxHealth ,Category = "Vital AttributeSet")
	FGameplayAttributeData MaxHealth;
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData &oldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData &oldMaxHealth) const;
	//魔力 魔力上限
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Mana,Category = "Vital AttributeSet")
	FGameplayAttributeData Mana;
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxMana,Category = "Vital AttributeSet")
	FGameplayAttributeData MaxMana;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData &oldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData &oldMaxMana) const;
};
