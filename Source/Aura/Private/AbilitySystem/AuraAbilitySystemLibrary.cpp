// Copyright  Pzp


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraAbilityTypes.h"
#include "Engine/OverlapResult.h"
#include "Interaction/CombatInterface.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(UObject* WorldContextObject)
{
	if (APlayerController* PC =UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
			return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
			
		}
	
	}
	return nullptr;
}

UAuraAttributeMenu* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(UObject* WorldContextObject)
{
	if (APlayerController* PC =UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
			return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
			
		}
	
	}
	return nullptr;
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,
	ECharacterClass CharacterClass, float Level,UAbilitySystemComponent *ASC)
{
	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	
	if (!AuraGameMode) return;
	AActor* AvatarActor = ASC->GetAvatarActor();
	
	FCharacterClassDefaultInfo ClassDefaultInfo = AuraGameMode->CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	FGameplayEffectContextHandle AttributeContextHandle = ASC->MakeEffectContext();
	AttributeContextHandle.AddSourceObject(AvatarActor); //用到自定义MMC 需要加源对象
	FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes,Level,AttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	
	FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(AuraGameMode->CharacterClassInfo->SecondaryAttributes,Level,AttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());
	
	FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(AuraGameMode->CharacterClassInfo->VitalAttributes,Level,AttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

void UAuraAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!AuraGameMode) return;
	
	UCharacterClassInfo* CharacterClassInfo = AuraGameMode->CharacterClassInfo;
	
	if (!CharacterClassInfo) return;
	
	for (auto AbilityClass:CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
		ASC->GiveAbility(AbilitySpec);
	}
	
	const FCharacterClassDefaultInfo & DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	
	for (auto& AbilityClass:DefaultInfo.StartupAbilities)
	{
		if (ICombatInterface *CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor()))
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,CombatInterface->GetLevel());
			ASC->GiveAbility(AbilitySpec);
		}
	}
}


bool UAuraAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraGameplayEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraGameplayEffectContext->IsBlockedHit();
	}
	return false;
}

bool UAuraAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraGameplayEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraGameplayEffectContext->IsCriticalHit();
	}
	return false;
}

void UAuraAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsBlocked)
{
	if (FAuraGameplayEffectContext* AuraGameplayEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraGameplayEffectContext->SetBlockedHit(bInIsBlocked);
	}
}

void UAuraAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsCritical)
{
	if (FAuraGameplayEffectContext* AuraGameplayEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraGameplayEffectContext->SetCriticalHit(bInIsCritical);
	}
}

void UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject,
	TArray<AActor*>& OutActors, TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);
	
	TArray<FOverlapResult> Overlaps;
	
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps,SphereOrigin,FQuat::Identity,FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects),FCollisionShape::MakeSphere(Radius),SphereParams);
		for (FOverlapResult& Overlap : Overlaps)
		{

			
			if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutActors.Add(Overlap.GetActor());
			}
		}
	
	}
	
}

