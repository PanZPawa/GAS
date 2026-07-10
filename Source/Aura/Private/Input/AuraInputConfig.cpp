// Copyright  Pzp


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (FAuraInputAction Action: AbilityInputActions)
	{
		if (Action.InputAction && InputTag == Action.InputTag)
		{
			return Action.InputAction;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("Can`t find ability Inputaction for [%s]."),*InputTag.ToString());
	}
	return nullptr;
}
