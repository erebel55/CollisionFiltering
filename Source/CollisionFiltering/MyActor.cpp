// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
}

void AMyActor::PostInitializeComponents() {
	Super::PostInitializeComponents();

	Mesh->SetMaskFilterOnBodyInstance((uint8)MaskFilter);
	Mesh->SetMoveIgnoreMask((uint8)MaskFilter);


	//Go through body setups and see which bodies should be turned on and off
	for (int32 BodyIdx = 0; BodyIdx < Mesh->Bodies.Num(); ++BodyIdx)
	{
		if (FBodyInstance* BodyInst = Mesh->Bodies[BodyIdx])
		{
			BodyInst->SetMaskFilter((uint8)MaskFilter);
		}
	}
}

void AMyActor::PerformTrace(FVector StartTrace, FVector EndTrace, EMaskFilterChannels Filter) {
	static FName WeaponFireTag = FName(TEXT("WeaponTrace"));
	FCollisionQueryParams TraceParams(WeaponFireTag, true);
	TraceParams.bReturnPhysicalMaterial = true;

	const FMaskFilter IgnoreMask = (FMaskFilter)Filter;
	TraceParams.IgnoreMask = IgnoreMask;

	FHitResult Hit(ForceInit);

	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, TraceParams);

	if (Hit.bBlockingHit) {
		if (Hit.Component.IsValid()) {
			FMaskFilter TheMaskFilter = Hit.Component->GetMaskFilterOnBodyInstance(0);
			FMaskFilter TheIgnoreMask = Hit.Component->GetMoveIgnoreMask();
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("MaskFilter: %d IgnoreMask %d"), TheMaskFilter, TheIgnoreMask));
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Component: %s"), *Hit.Component->GetName()));
		}

		if (Hit.GetActor()) {
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Actor: %s"), *Hit.GetActor()->GetName()));
		}

		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("=============HIT INFO============")));
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Trace IgnoreMask: %d"), IgnoreMask));
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("=============TRACE INFO============")));
}
