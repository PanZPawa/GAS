// Copyright  Pzp


#include "AuraAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "AuraGameplayTags.h"
UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	return *Cast<UAuraAssetManager>(GEngine->AssetManager);
	
	
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	FAuraGameplayTags::InitializeNativeGameplayTags();
	
	//TargetData need !
	//UAbilitySystemGlobals::Get().InitGlobalData();
}
