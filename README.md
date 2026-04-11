# DanzmannBitmasking

A plugin that simplifies bitmasks use in C++ and Blueprints by providing generic functions to most common operations.
The following functions are available:
- `AddFlags()`;
- `RemoveFlags()`;
- `FlipFlags()`;
- `HasAllFlags()`;
- `HasAnyFlags()`.

More info on enums can be found [here](http://danzmann.dev/#/posts/enums-what-whey-are-where-they-live-and-how-to-use-them).

---

## Usage Example

> Make sure you have added the `DanzmannBitmasking` module to your project's `Build.cs` file.

Create an enum that allows bitmasking by adding the required specifiers and macros, like this:

```cpp
// ElementType.h

#pragma once

#include "ElementType.generated.h"

/**
 * Example enum that using bitmasks can be useful.
 */
UENUM(BlueprintType, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = true))
enum class EElementType : uint8
{
    None      = 0 UMETA(Hidden), // 0x00
    Fire      = 1,               // 0x01 // 1 << 0
    Frost     = 2,               // 0x02 // 1 << 1
    Lightning = 4,               // 0x04 // 1 << 2
    Poison    = 8                // 0x08 // 1 << 3
};

ENUM_CLASS_FLAGS(EElementType)
ENUM_RANGE_BY_FIRST_AND_LAST(EElementType, EElementType::None, EElementType::Poison)
```

Then we can use the provided functions by the plugin along with the bitmask as such:
```cpp
// ExampleActor.h

#pragma once

#include "CoreMinimal.h"
#include "DanzmannBitmaskingFunctionLibrary.h"
#include "ElementType.h"
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
        void SetDebuffs(UPARAM(Meta = (Bitmask, BitmaskEnum = "/Script/MyProject.ElementType")) const int32 NewDebuffs)
        {
            Debuffs = NewDebuffs;
        }

    protected:
        /**
         * @see more info in Actor.h.
         */
        virtual void BeginPlay() override
        {
            Super::BeginPlay();

            // Set actor's negative stats as fire and lightning
            UDanzmannBitmaskingFunctionLibrary::AddFlags(Debuffs, EElementType::Fire | EElementType::Lightning);

            // Check if actor has lightning or poison negative stats
            bool bResult = UDanzmannBitmaskingFunctionLibrary::HasAnyFlags(Debuffs, EElementType::Poison | EElementType::Lightning);
        }

    private:
        /**
         * Current debuffs.
         */
        int32 Debuffs = 0;
};
```
