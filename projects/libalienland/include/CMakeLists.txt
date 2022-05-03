target_sources(${PROJECT_NAME} PRIVATE
	Imgui/Impl/FrameProcessor.h
	Imgui/ImguiController.h
	Imgui/ImguiDebugWidget.h
	Imgui/ImguiWidgetBase.h

	Internal/pch.h

	Render/SimpleSpriteUnitRender.h

	Game.h
	GameLoopDelegate.h
	SfmlGameLoopDelegate.h
	GameObject.h
	GameObjectTransform.h
	GameScene.h
	Character.h
	Enemy.h
	Bullet.h
	BulletFactory.h
	BulletManager.h
	Utils.h
	SfmlUtils.h
)

target_precompile_headers(${PROJECT_NAME} PRIVATE Internal/pch.h)
