// Copyright  Pzp

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"


class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;
UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const {return AttributeSet;}
protected:
	virtual auto BeginPlay() -> void override;
	UPROPERTY(EditAnywhere, Category = "Combat" )
	TObjectPtr<USkeletalMeshComponent> Weapon; //TObjectPtr 可以被引擎的反射和GC追踪，更加的安全，减少悬空指针的问题
	
	UPROPERTY(EditAnywhere, Category = "Combat" )
	FName WeaponTipSocketName; 
	
	virtual FVector GetCombatSocketLocation() override;;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	virtual void InitAbilityActorInfo();
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass,float Level) const;
	void InitializeDefaultAttributes() const;
	
	void AddCharacterAbilities();


private:
	UPROPERTY(EditAnywhere, Category ="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
