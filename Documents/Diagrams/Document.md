# 🎮 My Unreal Game

## 🧩 Class Diagram

```mermaid
classDiagram
    class ACharacter {
        +BeginPlay()
        +Tick()
    }

    class APlayerCharacter {
        +InputMove()
        +Attack()
    }

    class AEnemyCharacter {
        +AIController
        +TakeDamage()
    }

    APlayerCharacter --> ACharacter
    AEnemyCharacter --> ACharacter