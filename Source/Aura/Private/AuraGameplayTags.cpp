// Copyright  Pzp


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"
FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	
	GameplayTags.Attribute_Primary_Strength= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"),FString(" "));
	GameplayTags.Attribute_Primary_Intelligence= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"),FString(" "));
	GameplayTags.Attribute_Primary_Resilience= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"),FString(" "));
	GameplayTags.Attribute_Primary_Vigor= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"),FString(" "));
	
	
	
	
	
	
	
	GameplayTags.Attribute_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),FString("Reduces damage taken,improves Block Chance"));
	GameplayTags.Attribute_Secondary_Armor_Pen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor_Pen"),FString(" "));
	GameplayTags.Attribute_Secondary_BlockChance  = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"),FString(" "));
	GameplayTags.Attribute_Secondary_Critical_Rate= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Critical_Rate"),FString(" "));
	GameplayTags.Attribute_Secondary_Critical_Damage= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Critical_Damage"),FString(" "));
	GameplayTags.Attribute_Secondary_Critical_Resistance= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Critical_Resistance"),FString(" "));
	GameplayTags.Attribute_Secondary_HealthRegeneration= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"),FString(" "));
	GameplayTags.Attribute_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"),FString(" "));
	GameplayTags.Attribute_Secondary_MaxHealth= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),FString(" "));
	GameplayTags.Attribute_Secondary_MaxMana= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"),FString(" "));	
}
