target_sources(${PROJECT_NAME} PRIVATE
	Internal/pch.h
	Game.h
	TestScene.h
	Character.h
	Enemy.h
	Bullet.h
)

target_precompile_headers(${PROJECT_NAME} PRIVATE Internal/pch.h)
