#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

// Constructor: set defaults
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Stats
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;

	// Initialize combat flags
	bIsAttacking = false;
	bCanCombo = false;
	bIsDodging = false;

	// Create a SpringArm and Camera (optional; if you want custom camera)
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;

	UCameraComponent* FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // We control rotation via controller

	// Adjust player capsule size if desired
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth; // Ensure full health at start
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// (Future) You can update stamina regen, stamina drain, etc. here.
}

// Handle damage
float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	if (CurrentHealth <= 0.0f)
	{
		return 0.0f;
	}

	CurrentHealth -= DamageAmount;
	if (CurrentHealth <= 0.0f)
	{
		Die();
	}

	return DamageAmount;
}

void APlayerCharacter::Die()
{
	// For now, just play a log and disable input
	UE_LOG(LogTemp, Warning, TEXT("Player died!"));

	AController* PC = Cast<AController>(GetController());
	if (PC)
	{
		PC->DisableInput(nullptr);
	}

	// (Future) Play death animation, show respawn menu, etc.
}

// Movement Input
void APlayerCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		// Determine forward direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		// Determine right direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void APlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

// Combat Inputs (placeholders)
void APlayerCharacter::LightAttack()
{
	if (bIsAttacking || bIsDodging)
	{
		return; // Ignore input if already attacking or dodging
	}

	bIsAttacking = true;
	UE_LOG(LogTemp, Log, TEXT("Light Attack Triggered"));

	// (Future) Play light attack animation montage
	// When animation ends, set bIsAttacking = false; and maybe bCanCombo = true;
}

void APlayerCharacter::HeavyAttack()
{
	if (bIsAttacking || bIsDodging)
	{
		return;
	}

	bIsAttacking = true;
	UE_LOG(LogTemp, Log, TEXT("Heavy Attack Triggered"));

	// (Future) Play heavy attack animation montage
}

void APlayerCharacter::Dodge()
{
	if (bIsDodging || bIsAttacking)
	{
		return;
	}

	bIsDodging = true;
	UE_LOG(LogTemp, Log, TEXT("Dodge Triggered"));

	// (Future) Play dodge/roll animation and apply invincibility frames
	// After dodge finishes, set bIsDodging = false;
}

// Bind inputs
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// Mouse/camera bindings
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	// Combat bindings
	PlayerInputComponent->BindAction("LightAttack", IE_Pressed, this, &APlayerCharacter::LightAttack);
	PlayerInputComponent->BindAction("HeavyAttack", IE_Pressed, this, &APlayerCharacter::HeavyAttack);
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &APlayerCharacter::Dodge);
}

