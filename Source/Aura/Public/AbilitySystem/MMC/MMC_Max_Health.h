// Copyright  Pzp

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_Max_Health.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_Max_Health : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_Max_Health();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
private:
	FGameplayEffectAttributeCaptureDefinition VigorDef;
};
