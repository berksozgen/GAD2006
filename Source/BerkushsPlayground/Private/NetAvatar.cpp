// Fill out your copyright notice in the Description page of Project Settings.


#include "NetAvatar.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ANetAvatar::ANetAvatar()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	if(SpringArm==nullptr) return;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if(Camera) Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ANetAvatar::BeginPlay()
{
	Super::BeginPlay();

	if(Camera) Camera->bUsePawnControlRotation = false;
	if(SpringArm) SpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ANetAvatar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("Turn",this,&ACharacter::AddControllerYawInput);
	InputComponent->BindAxis("Lookup",this,&ACharacter::AddControllerPitchInput);

	InputComponent->BindAxis("MoveForward",this,&ANetAvatar::MoveForward);
	InputComponent->BindAxis("MoveRight",this,&ANetAvatar::MoveRight);
}

void ANetAvatar::MoveForward(float Val)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(.0f,Rotation.Yaw,.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, Val);
}

void ANetAvatar::MoveRight(float Val)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(.0f,Rotation.Yaw,.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardDirection, Val);
}
