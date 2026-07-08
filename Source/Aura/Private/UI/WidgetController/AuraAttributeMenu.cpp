// Copyright  Pzp


#include "UI/WidgetController/AuraAttributeMenu.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAuraAttributeMenu::BindCallbacksToDependencies()
{
}

void UAuraAttributeMenu::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);
	FAuraAttributeInfo info = AttributeInfo->FindAttributeInfoTag(FAuraGameplayTags::Get().Attribute_Primary_Strength);
	info.AttributeValue =  AS->GetStrength();
	AttributeInfoDelegate.Broadcast(info);
}
