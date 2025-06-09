#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SPARKOFDAWNRPG_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Constructor
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// --- Health & Stats ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float CurrentHealth;

	// (Future) Armor slots can go here
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	// float ArmorValue;

	// --- Combat Flags ---
	bool bIsAttacking;
	bool bCanCombo;           // For future combo chains
	bool bIsDodging;

	// --- Input Functions ---
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);

	// Combat Inputs
	void LightAttack();
	void HeavyAttack();
	void Dodge();

	// Handle taking damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	// Weapon & Looting (future)
	// void LootItem(AActor* LootActor);

	// Helper: Handle death
	void Die();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Bind input 
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Accessor for Health (Blueprint‐readable)
	UFUNCTION(BlueprintPure, Category = "Stats")
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintPure, Category = "Stats")
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	// (Future) function for equipment/armor
	// void EquipArmor(AActor* ArmorPiece);
};
