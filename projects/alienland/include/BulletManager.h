#pragma once

class BulletFactory;

class BulletManager
{
public:
	BulletManager();

	void Init(const std::filesystem::path & resourcesDirectory);

private:
	std::shared_ptr<BulletFactory> _bulletFactory;
};