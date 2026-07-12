// Copyright  Pzp


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();	
	AutoRun();

	
}
void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControllerPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControllerPawn->GetActorLocation(),ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation( LocationOnSpline,ESplineCoordinateSpace::World);
		ControllerPawn->AddMovementInput(Direction);
		
		const float DistanceToDirection = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDirection <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	
	/*
	 * 分以下几种情况
	 * 1，Last 和 This 都为空  跳过
	 * 2.Last为空 This 不为空  高亮 This对象
	 * 3.Last不为空 This为空  取消Last高亮
	 * 4.都不为空 
	 *		情况1  This == Last 跳过
	 *		情况2  This != Last 取消 Last高亮  高亮This
	 * 
	 * 
	 */
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			ThisActor->HighlightActor();
			//情况2
		}
		else
		{
			//情况1
		}
	}
	else
	{
		if (ThisActor != nullptr && ThisActor != LastActor)
		{	//情况4.2
			ThisActor->HighlightActor();
			LastActor->UnHighlightActor();
		}
		else if (ThisActor == nullptr)
		{	//情况3
			LastActor->UnHighlightActor();
		}
		else
		{
			//情况4.1
		}
	}
	
	
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true:false;
		bAutoRunning = false;
	}

	
	
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}
	
	if (bTargeting)
	{
		if (GetASC())GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		if (APawn* ControllerPawn = GetPawn())
		{
			if (FollowTime <= ShortPressThreshold)
			{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this,ControllerPawn->GetActorLocation(),CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc: NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc,ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(),PointLoc,8,8,FColor::Green,false,5.f);
				}
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num()-1];
				bAutoRunning = true;
			}
				
			}
		}
		FollowTime = 0.f;
		
	}

}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}
	
	if (bTargeting)
	{
		if (GetASC())GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_Visibility,false,Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}
		if (APawn* ControllerPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControllerPawn->GetActorLocation()).GetSafeNormal();
			ControllerPawn->AddMovementInput(WorldDirection);
		}
		
		
		
		
		
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return AuraAbilitySystemComponent;
}


void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!IsLocalController()) return;

	check(AuraContext);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext,0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UAuraInputComponent * AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);	
	AuraInputComponent->BindAbilityActions(InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);


}  
 
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector =  InputActionValue.Get<FVector2D>();
	const FRotator YawRotation(0.f,GetControlRotation().Yaw,0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}

