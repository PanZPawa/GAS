// Copyright  Pzp


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Game/AuraGameModeBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"


struct AuraDamageStatics
{
	
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor_Pen);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Critical_Rate);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Critical_Damage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalResistance);
	
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,BlockChance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Armor_Pen,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Critical_Rate,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Critical_Damage,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalResistance,Target,false);

	}
};

static AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}


UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().Armor_PenDef);
	RelevantAttributesToCapture.Add(DamageStatics().Critical_RateDef);
	RelevantAttributesToCapture.Add(DamageStatics().Critical_DamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalResistanceDef);

}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	
	AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	
	float Damage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);
	
	float Armor = 0.0f;
	float BlockChance = 0.0f;
	float Armor_Pen = 0.0f;
	float Critical_Rate = 0.0f;
	float Critical_Damage = 0.0f;
	float CriticalResistance = 0.0f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef,EvaluationParameters,Armor);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef,EvaluationParameters,BlockChance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Armor_PenDef,EvaluationParameters,Armor_Pen);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Critical_RateDef,EvaluationParameters,Critical_Rate);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Critical_DamageDef,EvaluationParameters,Critical_Damage);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalResistanceDef,EvaluationParameters,CriticalResistance);

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	Armor = FMath::Max<float>(Armor, 0.0f);
	BlockChance = FMath::Max<float>(BlockChance, 0.0f);
	Armor_Pen = FMath::Max<float>(Armor_Pen, 0.0f);
	//表格中拿穿甲系数
	UWorld* World = TargetASC->GetWorld();
	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(World));
	UCurveTable* CurveTable = AuraGameMode->CharacterClassInfo->DamageCurveTable;
	
	FRealCurve* ArmorPenCurve = CurveTable->FindCurve(
	FName("ArmorPen"),   FString("")        );
	float ArmorPenCoefficient = ArmorPenCurve->Eval(Cast<ICombatInterface>(Spec.GetContext().GetSourceObject())->GetLevel());
	
	
	FRealCurve* CritRateReductionCurve = CurveTable->FindCurve(
	FName("CritRateReduction"),   FString("")        );
	float CritRateReductionCoefficient = CritRateReductionCurve->Eval(Cast<ICombatInterface>(TargetActor)->GetLevel());
	
	FRealCurve* CritDamageReductionCurve = CurveTable->FindCurve(
	FName("CritDamageReduction"),   FString("")        );
	float CritDamageReductionCoefficient = CritDamageReductionCurve->Eval(Cast<ICombatInterface>(TargetActor)->GetLevel());
	
	float EffectiveCritRate = Critical_Rate - (CriticalResistance * CritRateReductionCoefficient);
	EffectiveCritRate = FMath::Max(EffectiveCritRate, 0);

	float CritBonusDamage = Critical_Damage - (CriticalResistance * CritDamageReductionCoefficient);
	CritBonusDamage = FMath::Max(CritBonusDamage, 0);
	
	bool bCritical = FMath::FRand() * 100 < EffectiveCritRate;
	if ( bCritical )
	{
		Damage *= 1.0 + CritBonusDamage;
	}
	UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle,bCritical);

	
	float EffectiveArmor = Armor - (Armor_Pen * ArmorPenCoefficient);
	EffectiveArmor = FMath::Max(EffectiveArmor, 0.0f);
	
	Damage *= 100.0f / (100.0f + EffectiveArmor);
	
	
	bool bBlock = FMath::RandRange(1,100) <BlockChance ;
	if (bBlock)
	{
		Damage = Damage *0.5;
	}
	
	UAuraAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle,bBlock);
	
	
//	Damage = FMath::RoundToFloat(Damage);
	const FGameplayModifierEvaluatedData EvaluationData(UAuraAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Override,Damage);

//	const FGameplayModifierEvaluatedData EvaluationData(DamageStatics().ArmorProperty,EGameplayModOp::Additive,Armor);
	OutExecutionOutput.AddOutputModifier(EvaluationData);
}
