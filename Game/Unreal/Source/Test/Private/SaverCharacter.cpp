// Fill out your copyright notice in the Description page of Project Settings.


#include "SaverCharacter.h"

// Sets default values
ASaverCharacter::ASaverCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASaverCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASaverCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASaverCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

