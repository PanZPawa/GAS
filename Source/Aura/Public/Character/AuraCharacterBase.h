// Copyright  Pzp

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Combat" )
	TObjectPtr<USkeletalMeshComponent> Weapon; //TObjectPtr 可以被引擎的反射和GC追踪，更加的安全，减少悬空指针的问题

};
