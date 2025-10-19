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
