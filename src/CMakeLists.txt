
target_sources(${PROJECT_NAME} PRIVATE 
    App.cpp
    GameData.cpp
    Renderer.cpp
    rand.cpp
    WindowManager.cpp
    music/MusicPlayer.cpp
    entities/Entity.cpp
    entities/Player.cpp
    entities/SimpleEnemy.cpp
    entities/SimpleBullet.cpp
    entities/SimpleSpawner.cpp
    collider/CollisionSystem.cpp
    UI/Button.h
    screens/Screen.cpp
    screens/OptionsScreen.cpp
    screens/GameScreen.cpp
    screens/StartScreen.cpp
)