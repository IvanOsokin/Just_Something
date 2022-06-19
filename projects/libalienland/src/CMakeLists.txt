target_sources(${PROJECT_NAME} PRIVATE
	Imgui/Impl/FrameProcessor.cpp
	Imgui/ImguiController.cpp
	Imgui/ImguiDebugWidget.cpp

	Render/SimpleSpriteUnitRender.cpp

	Game.cpp
	SfmlGameLoopDelegate.cpp
	GameObject.cpp
	GameScene.cpp
	CollisionProcessor.cpp
	Character.cpp
	Enemy.cpp
	Bullet.cpp
	BulletFactory.cpp
	BulletManager.cpp
	Utils.cpp
	SfmlUtils.cpp
)
