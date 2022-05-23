#pragma once

class GameObjectTransform : sf::Transformable
{
public:
	void SetPosition(float x, float y)
	{
		setPosition(x, y);
	}

	void SetPosition(const sf::Vector2f & position)
	{
		setPosition(position);
	}

	void SetRotation(float angle)
	{
		setRotation(angle);
	}

	void SetScale(float factorX, float factorY)
	{
		setScale(factorX, factorY);
	}

	void SetScale(const sf::Vector2f & factors)
	{
		SetScale(factors);
	}

	void SetOrigin(float x, float y)
	{
		setOrigin(x, y);
	}

	void SetOrigin(const sf::Vector2f & origin)
	{
		setOrigin(origin);
	}

	const sf::Vector2f& GetPosition() const
	{
		return getPosition();
	}

	float GetRotation() const
	{
		return getRotation();
	}

	const sf::Vector2f& GetScale() const
	{
		return getScale();
	}

	const sf::Vector2f& GetOrigin() const
	{
		return getOrigin();
	}

	void Move(float offsetX, float offsetY)
	{
		move(offsetX, offsetY);
	}

	void Move(const sf::Vector2f & offset)
	{
		move(offset);
	}

	void Rotate(float angle)
	{
		rotate(angle);
	}

	void Scale(float factorX, float factorY)
	{
		scale(factorX, factorY);
	}

	void Scale(const sf::Vector2f & factor)
	{
		scale(factor);
	}

	const sf::Transform& GetTransform() const
	{
		return getTransform();
	}

	const sf::Transform& GetInverseTransform() const
	{
		return getInverseTransform();
	}
};