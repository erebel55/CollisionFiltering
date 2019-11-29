// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestTypes.h"
#include "MyActor.generated.h"

UCLASS()
class COLLISIONFILTERING_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable)
	void PerformTrace(FVector StartTrace, FVector EndTrace, EMaskFilterChannels Filter);

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = Custom)
	EMaskFilterChannels MaskFilter;
};
