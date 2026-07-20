// Copyright  Pzp


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"
FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attribute_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Primary.Strength"),
    FString("Increases physical damage")
);

GameplayTags.Attribute_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Primary.Intelligence"),
    FString("Increases magical damage")
);

GameplayTags.Attribute_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Primary.Resilience"),
    FString("Increases Armor and Armor Penetration")
);

GameplayTags.Attribute_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Primary.Vigor"),
    FString("Increases Health")
);

    
GameplayTags.Attribute_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Secondary.Armor"),
    FString("Reduces damage taken, improves Block Chance")
);

GameplayTags.Attribute_Secondary_Armor_Pen = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Secondary.Armor_Pen"),
    FString("Ignores percentage of enemy Armor, increases Crit Hit Chance")
);

GameplayTags.Attribute_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Secondary.BlockChance"),
    FString("Chance to cut incoming damage in half")
);

GameplayTags.Attribute_Secondary_Critical_Rate = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Secondary.Critical_Rate"),
    FString("Chance to double damage plus critical hit bonus")
);

GameplayTags.Attribute_Secondary_Critical_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Secondary.Critical_Damage"),
    FString("Bonus damage added when a critical hit is scored")
);

GameplayTags.Attribute_Secondary_Critical_Resistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Secondary.Critical_Resistance"),
    FString("Reduces critical hit chance of attacking enemies")
);

GameplayTags.Attribute_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Secondary.HealthRegeneration"),
    FString("Amount of Health regenerated every 1 second")
);

GameplayTags.Attribute_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Secondary.ManaRegeneration"),
    FString("Amount of Mana regenerated every 1 second")
);

GameplayTags.Attribute_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Secondary.MaxHealth"),
    FString("Maximum amount of Health obtainable")
);

GameplayTags.Attribute_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Secondary.MaxMana"),
    FString("Maximum amount of Mana obtainable")
);	
    
    
    /*
     *InputTags
     * 
     */
    GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("InputTag.LMB"),
    FString("Input Tag for Left Mouse Button.")
);	
    GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("InputTag.RMB"),
FString("Input Tag for Right Mouse Button.")
);	
    
    GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("InputTag.1"),
FString("Input Tag for 1 Button.")
);	
    GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("InputTag.2"),
FString("Input Tag for 2 Button.")
);	
    GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("InputTag.3"),
FString("Input Tag for 3 Button.")
);	
    GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("InputTag.4"),
FString("Input Tag for 4 Button.")
);	
    
    GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Damage"),
FString("Damage")
);	
    
    //元素伤害
    GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Damage.Fire"),
FString("Fire Damage type ")
);	
    GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Damage.Lightning"),
FString("Lightning Damage type ")
);	    GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Damage.Arcane"),
FString("Arcane Damage type ")
);	    GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Damage.Physical"),
FString("Physical Damage type ")
);	
    
    //元素抗性
    GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Attributes.Resistance.Fire"),
FString("Fire Resistance type ")
);	
    GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Attributes.Resistance.Lightning"),
FString("Lightning Resistance type ")
);	    GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Attributes.Resistance.Arcane"),
FString("Arcane Resistance type ")
);	    GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Attributes.Resistance.Physical"),
FString("Physical Resistance type ")
);	
    
    
    GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire,GameplayTags.Attributes_Resistance_Fire);
    GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning,GameplayTags.Attributes_Resistance_Lightning);
    GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane,GameplayTags.Attributes_Resistance_Arcane);
    GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical,GameplayTags.Attributes_Resistance_Physical);

    
    GameplayTags.Effect_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Effect.HitReact"),
FString("HitReact Animation")
);	
          
    
    
    //Attack
    GameplayTags.Ability_Attack_Melee = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Ability.Attack.Melee"),
FString("Melee  Attack")
);	
         
 
    //Montage
    GameplayTags.Montage_Attack_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Montage.Attack.Weapon"),
FString("Montage witch Attack by Weapon.")
);	
    GameplayTags.Montage_Attack_RHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Montage.Attack.RHand"),
FString("Montage witch Attack by Right Hand.")
);	    GameplayTags.Montage_Attack_LHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("Montage.Attack.LHand"),
FString("Montage witch Attack by Left Hand.")
);	      
    
}
