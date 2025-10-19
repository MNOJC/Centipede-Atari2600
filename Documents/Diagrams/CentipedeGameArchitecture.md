# Centipede Game Architecture

```mermaid
classDiagram
    class MainCharacter {
        Move()
        Shoot()
    }

    class CentipedeProjectile {
        OnBeginOverlap()
    }

    class Damageable {
        Damage()
    }

    class Health_Component {
        Damage()
        HandleDeath()
    }

    class Mushroom {
    }

    class MushroomManager {
        GenerateMushroomsOnGrid()
    }

    class CentipedeManager {
        SpawnCentipede()
    }

    class CentipedeEntity {
        Initialise()
        Move()
    }

    class CentipedeGameMode {
        Add_Score()
        NextLevel()
        GetMaterialByTag()
        SkipLevel_debug_cmd()
    }

    %% Relationships
    MainCharacter ..> CentipedeProjectile : Shoot
    MainCharacter --> CentipedeGameMode : Get Material
    CentipedeProjectile --> Damageable : OnBeginOverlap → Damage
    Damageable o-- Health_Component : Damage()
    Health_Component --> CentipedeGameMode : HandleDeath → Add_Score
    Mushroom *-- Damageable
    CentipedeEntity *-- Damageable
    MushroomManager ..> Mushroom : Spawn Actor
    CentipedeManager ..> CentipedeEntity : SpawnCentipede()
```

# Centipede Game FileTree
```
Private/
├── Camera/
│   └── CentipedeCamera.cpp
├── Centipede/
│   ├── CentipedeEntity.cpp
│   ├── CentipedeManager.cpp
│   └── CentipedeSegment.cpp
├── Component/
│   ├── CentipedeMovementComponent.cpp
│   └── Health_Component.cpp
├── Core/
│   ├── CentipedeGameInstance.cpp
│   ├── CentipedeGameMode.cpp
│   ├── CentipedeHUD.cpp
│   └── CentipedePlayerController.cpp
├── DataAsset/
│   └── CentipedColorDA.cpp
├── Function/
│   └── CentipedeColorFunctions.cpp
├── Grid/
│   └── CentipedeGridGenerator.cpp
├── Log/
│   ├── CentipedeLogger.cpp
│   └── CentipedeLoggerCategories.cpp
├── MainCharacter/
│   └── MainCharacter.cpp
├── Mushrooms/
│   ├── Mushrooms.cpp
│   └── MushroomsManager.cpp
├── Parent/
│   └── Damageable.cpp
└── Projectile/
    └── CentipedeProjectile.cpp
```