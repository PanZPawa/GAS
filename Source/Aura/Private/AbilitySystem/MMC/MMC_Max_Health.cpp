// Copyright  Pzp


#include "AbilitySystem/MMC/MMC_Max_Health.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_Max_Health::UMMC_Max_Health()
{
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;
	
	RelevantAttributesToCapture.Add(VigorDef);	
}

float UMMC_Max_Health::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Vigor =0.f;
	GetCapturedAttributeMagnitude(VigorDef,Spec,EvaluateParameters,Vigor);
	Vigor = FMath::Max(Vigor,0.f);
	
	ICombatInterface * CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32  PlayerLevel = CombatInterface->GetLevel();
	
	return 80.f + 2.5f*Vigor +10.f * PlayerLevel;
}
