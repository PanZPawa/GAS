// Copyright  Pzp


#include "UI/WidgetController/AuraAttributeMenu.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAuraAttributeMenu::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	for (auto& Pair:	AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this,Pair,AS](const FOnAttributeChangeData& Data)
			{
	 			BroadcastAttributeInfo(Pair.Key,Pair.Value());
			}); 
	}

}

void UAuraAttributeMenu::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Pair:AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key,Pair.Value());
	}
}

void UAuraAttributeMenu::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
