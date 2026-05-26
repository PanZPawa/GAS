// Copyright  Pzp


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMana(50.f);
	InitMaxHealth(100.f);
	InitMaxMana(100.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		UE_LOG(LogTemp,Warning,TEXT("Health: %f"),NewValue);
	}
	if (Attribute == GetMaxHealthAttribute())
	{
		UE_LOG(LogTemp,Warning,TEXT("MaxHealth: %f"),NewValue);
	}
	
	if (Attribute == GetManaAttribute())
	{
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

