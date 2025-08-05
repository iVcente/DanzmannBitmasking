# Bitmasking
A plugin that simplifies bitmasks use in C++ and Blueprints by providing generic functions to most common operations.
The following functions are available:
* `AddFlags()`;
* `RemoveFlags()`;
* `FlipFlags()`;
* `HasAllFlags()`;
* `HasAnyFlags()`.

---

### Usage Example

Create an enum that allows bitmasking by adding the required specifiers and macros, like this:

```cpp
// ExampleEnum.h

#pragma once

#include "ExampleEnum.generated.h"

/**
 * Example enum that using bitmasks can be useful.
 */
UENUM(BlueprintType, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = true))
enum class EExampleEnum : uint8
{
    None      = 0 UMETA(Hidden), // 0x00
    Fire      = 1,               // 0x01 // 1 << 0
    Frost     = 2,               // 0x02 // 1 << 1
    Lightning = 4,               // 0x04 // 1 << 2
    Poison    = 8                // 0x08 // 1 << 3
};

ENUM_CLASS_FLAGS(EExampleEnum)
ENUM_RANGE_BY_FIRST_AND_LAST(EExampleEnum, EExampleEnum::None, EExampleEnum::Poison)
```

Then we can use the provided functions by the plugin along with the bitmask as such:
```cpp
// ExampleActor.h

#pragma once

#include "CoreMinimal.h"
#include "DanzmannBitmaskingFunctionLibrary.h"
#include "ExampleEnum.h"
#include "GameFramework/Actor.h"

#include "ExampleActor.generated.h"

/**
 * Example Actor.
 */
UCLASS()
class AExampleActor : public AActor
{
    GENERATED_BODY()

    public:
        /**
         * Get current debuffs.
         * @return Actor's debuffs.
         */
        UFUNCTION(BlueprintPure)
        int32 GetDebuffs() const
        {
            return Debuffs;
        }

        /**
         * Set current debuffs.
         * @param NewDebuffs New debuffs.
         */
        UFUNCTION(BlueprintCallable)
        void SetDebuffs(UPARAM(Meta = (Bitmask, BitmaskEnum = "/Script/MyProject.ExampleEnum")) const int32 NewDebuffs)
        {
            Debuffs = NewDebuffs;
        }

    protected:
        virtual void BeginPlay() override
        {
            Super::BeginPlay();

            // Set actor's negative stats as fire and lightning
            UDanzmannBitmaskingFunctionLibrary::AddFlags(Debuffs, EExampleEnum::Fire | EExampleEnum::Lightning);

            // Check if actor has lightning or poison negative stats
            bool bResult = UDanzmannBitmaskingFunctionLibrary::HasAnyFlags(Debuffs, EExampleEnum::Poison | EExampleEnum::Lightning);
        }

    private:
        /**
         * Current debuffs.
         */
        int32 Debuffs = 0;
};
```
---
More info on enums can be found [here](https://www.notion.so/danzmann/Enums-53e162396fee4495b4475ee66c22081e?pvs=4).
