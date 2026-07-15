// Copyright  Pzp

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
/**
 * 
 */

struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get(){return GameplayTags;}
	static void InitializeNativeGameplayTags();
	
	FGameplayTag Attribute_Primary_Strength;
	FGameplayTag Attribute_Primary_Intelligence;
	FGameplayTag Attribute_Primary_Resilience;
	FGameplayTag Attribute_Primary_Vigor;
	
	FGameplayTag Attribute_Secondary_Armor;
	FGameplayTag Attribute_Secondary_Armor_Pen;
	FGameplayTag Attribute_Secondary_BlockChance;
	FGameplayTag Attribute_Secondary_Critical_Rate;
	FGameplayTag Attribute_Secondary_Critical_Damage;
	FGameplayTag Attribute_Secondary_Critical_Resistance;
	FGameplayTag Attribute_Secondary_HealthRegeneration;
	FGameplayTag Attribute_Secondary_ManaRegeneration;
	FGameplayTag Attribute_Secondary_MaxHealth;
	FGameplayTag Attribute_Secondary_MaxMana;
	
	
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;


	FGameplayTag Damage;
	FGameplayTag Effect_HitReact;

protected:
	
private:
	static FAuraGameplayTags GameplayTags;
	
	
	
};