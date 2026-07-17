#include "AuraAbilityTypes.h"

bool FAuraGameplayEffectContext::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{	
	if (!FGameplayEffectContext::NetSerialize(Ar, Map, bOutSuccess))
	{
		return false;
	}
	uint32 RepBits =0;
	if (Ar.IsSaving())
	{
		if (IsBlockedHit())
		{
			RepBits |= 1<<0;
		}
		if (IsCriticalHit())
		{
			RepBits |= 1<<1;
		}
	}
	
	
	Ar.SerializeBits(&RepBits, 2);
	
	if (RepBits &= 1<<0)
	{
		Ar << bIsBlockedHit;
	}
	
	if (RepBits &= 1<<1)
	{
		Ar << bIsCriticalHit;
	}
	
	bOutSuccess = true;
	return true;
}
