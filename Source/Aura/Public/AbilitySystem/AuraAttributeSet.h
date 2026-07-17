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

class UAbilitySystemComponent;
class ACharacter;
USTRUCT()
struct FEffectProperties{
	GENERATED_BODY()
	
	
	FEffectProperties(){}
	
	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor * SourceAvatarActor = nullptr;
	UPROPERTY()
	AController *SourceController= nullptr;
	UPROPERTY()
	ACharacter * SourceCharacter = nullptr;
	
	
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor * TargetAvatarActor = nullptr;
	UPROPERTY()
	AController *TargetController= nullptr;
	UPROPERTY()
	ACharacter * TargetCharacter = nullptr;
};


template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T,FDefaultDelegateUserPolicy>::FFuncPtr;


UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute,float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& EffectData) override;
	
	TMap<FGameplayTag,TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	
	
	//Primary
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing= OnRep_Strength,Category = "Primary AttributeSet")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing= OnRep_Intelligence,Category = "Primary AttributeSet")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing= OnRep_Resilience,Category = "Primary AttributeSet")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing= OnRep_Vigor,Category = "Primary AttributeSet")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);
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
	
	
	//Secondary Attributes
	//护甲
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Armor,Category = "Secondary AttributeSet")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);
	//穿甲
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Armor_Pen,Category = "Secondary AttributeSet")
	FGameplayAttributeData Armor_Pen;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor_Pen);
	//暴击率
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Critical_Rate,Category = "Secondary AttributeSet")
	FGameplayAttributeData Critical_Rate;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Critical_Rate);
	//爆伤
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Critical_Damage,Category = "Secondary AttributeSet")
	FGameplayAttributeData Critical_Damage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Critical_Damage);
	//生命回复
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_HealthRegeneration,Category = "Secondary AttributeSet")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);
	//魔力回复
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_ManaRegeneration,Category = "Secondary AttributeSet")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);
	//暴击抗性
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalResistance,Category = "Secondary AttributeSet")
	FGameplayAttributeData CriticalResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalResistance);
	//格挡
	//暴击抗性
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_BlockChance,Category = "Secondary AttributeSet")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);
	
	
	/*
	 * Meta Attributes
	 */
	
	UPROPERTY(BlueprintReadOnly,Category="Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingDamage);
	
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData &oldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData &oldMaxMana) const;
	
	
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData &oldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData &oldIntelligence) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData &oldResilience) const;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData &oldVigor) const;
	
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData &oldArmor) const;
	UFUNCTION()
	void OnRep_Armor_Pen(const FGameplayAttributeData &oldArmor_Pen) const;
	UFUNCTION()
	void OnRep_Critical_Rate(const FGameplayAttributeData &oldCritical_Rate) const;
	UFUNCTION()
	void OnRep_Critical_Damage(const FGameplayAttributeData &oldCritical_Damage) const;
	
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData &oldHealthRegeneration) const;
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData &oldManaRegeneration) const;
	UFUNCTION()
	void OnRep_CriticalResistance(const FGameplayAttributeData &oldCriticalResistance) const;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData &oldBlockChance) const;
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& EffectData,FEffectProperties& Props) const;
	
	void ShowFloatingText(FEffectProperties& Props,const float &LocalIncomingDamage,bool bBlock = false,bool bCritical= false);
};
