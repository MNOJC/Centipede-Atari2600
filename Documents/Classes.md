classDiagram
    class MainCharacter {
        +Move()
        +Shoot()
    }
    
    class CentipedeProjectile {
        +OnBeginOverlap()
    }
    
    class Damageable {
        +Damage()
    }
    
    class Mushroom {
    }
    
    class MushroomManager {
        +GenerateMushroomsOnGrid()
    }
    
    class Health_Component {
        +Damage()
        +HandleDeath()
    }
    
    class CentipedeGameMode {
        +Add_Score()
        +NextLevel()
        +GetMaterialByTag()
        +SkipLevel()
    }
    
    class CentipedeManager {
        +SpawnCentipede()
    }
    
    class CentipedeEntity {
        +Initialise()
        +Move()
    }
    
    MainCharacter --> CentipedeProjectile : Spawn Actor
    MainCharacter --> CentipedeGameMode : GetMaterial
    CentipedeProjectile --> Damageable
    MushroomManager --> Mushroom : Spawn Actor
    Mushroom ..|> Damageable : implements
    Damageable --> Health_Component
    Mushroom --> Health_Component
    Health_Component --> CentipedeGameMode : Add_Score
    CentipedeGameMode --> CentipedeGameMode : Exec SkipLevel
    CentipedeManager --> CentipedeEntity : SpawnCentipede