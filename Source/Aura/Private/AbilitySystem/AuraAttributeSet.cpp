// Copyright  Pzp


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
//	InitHealth(50.f);
//	InitMana(50.f);
//	InitMaxHealth(100.f);
//	InitMaxMana(100.f);
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	/*Primary Attributes*/
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Strength,GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Resilience, GetResilienceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Vigor, GetVigorAttribute);
	/*Secondary Attributes*/
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Armor_Pen, GetArmor_PenAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_BlockChance, GetBlockChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Critical_Damage, GetCritical_DamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Critical_Rate, GetCritical_RateAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Critical_Resistance, GetCriticalResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_MaxMana, GetMaxManaAttribute);



}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Vigor, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMana, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Armor_Pen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Critical_Rate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Critical_Damage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,BlockChance, COND_None, REPNOTIFY_Always);

}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.f,GetMaxHealth());
	}
	if (Attribute == GetMaxHealthAttribute())
	{
		UE_LOG(LogTemp,Warning,TEXT("MaxHealth: %f"),NewValue);
	}
	
	if (Attribute == GetManaAttribute())
	{			
		NewValue = FMath::Clamp(NewValue,0.f,GetMaxMana());
		UE_LOG(LogTemp,Warning,TEXT("Mana: %f"),NewValue);
	}
	if (Attribute == GetMaxManaAttribute())
	{
		UE_LOG(LogTemp,Warning,TEXT("MaxMana: %f"),NewValue);
	}
}
void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& EffectData, FEffectProperties& Props) const
{
	Props.EffectContextHandle = EffectData.EffectSpec.GetContext();
	Props.SourceASC =  Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController  = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
		
	}
	if (EffectData.Target.AbilityActorInfo.IsValid() && EffectData.Target.AbilityActorInfo.IsValid())
	{
		Props.TargetAvatarActor = EffectData.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = EffectData.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>( Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& EffectData)
{
	Super::PostGameplayEffectExecute(EffectData);
	
	FEffectProperties Props;
	SetEffectProperties(EffectData,Props);
	
	if (EffectData.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0.f,GetMaxHealth()));
		UE_LOG(LogTemp,Warning,TEXT("Changed Health On %s, Health: %f"),*Props.TargetAvatarActor->GetName(),GetHealth());

	}
}



void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& oldHealth) const 
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Health, oldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& oldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxHealth, oldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& oldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Mana, oldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData &oldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxMana, oldMaxMana);
}

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& oldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Strength, oldStrength);

}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& oldIntelligence) const
{	
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Intelligence, oldIntelligence);

}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& oldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Resilience, oldResilience);

}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& oldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Vigor, oldVigor);

}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& oldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Armor, oldArmor);

}

void UAuraAttributeSet::OnRep_Armor_Pen(const FGameplayAttributeData& oldArmor_Pen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Armor_Pen, oldArmor_Pen);

}

void UAuraAttributeSet::OnRep_Critical_Rate(const FGameplayAttributeData& oldCritical_Rate) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Critical_Rate, oldCritical_Rate);
}

void UAuraAttributeSet::OnRep_Critical_Damage(const FGameplayAttributeData& oldCritical_Damage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Critical_Damage, oldCritical_Damage);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& oldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,HealthRegeneration, oldHealthRegeneration);

}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& oldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,ManaRegeneration, oldManaRegeneration);

}

void UAuraAttributeSet::OnRep_CriticalResistance(const FGameplayAttributeData& oldCriticalResistance) const
{	
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,CriticalResistance, oldCriticalResistance);

}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& oldBlockChance) const
{	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,BlockChance, oldBlockChance);

}



