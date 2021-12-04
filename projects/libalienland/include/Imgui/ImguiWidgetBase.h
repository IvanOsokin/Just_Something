#pragma once

class ImguiWidgetBase
{
public:
	virtual ~ImguiWidgetBase() = default;

	void BaseBeginFrame()
	{
		if constexpr (s_imguiWidgetsEnabled)
		{
			BeginFrame();
		}
	}

	void BaseBeginUpdate()
	{
		if constexpr (s_imguiWidgetsEnabled)
		{
			BeginUpdate();
		}
	}

	void BaseUpdate(sf::Time elapsedTime)
	{
		if constexpr (s_imguiWidgetsEnabled)
		{
			Update(elapsedTime);
		}
	}

	void BaseEndUpdate()
	{
		if constexpr (s_imguiWidgetsEnabled)
		{
			EndUpdate();
		}
	}

	void BaseEndFrame()
	{
		if constexpr (s_imguiWidgetsEnabled)
		{
			EndFrame();
		}
	}

protected:
	virtual void BeginFrame() {}
	virtual void BeginUpdate() {}
	virtual void Update([[maybe_unused]] sf::Time elapsedTime) {}
	virtual void EndUpdate() {}
	virtual void EndFrame() {}

private:
	static constexpr bool s_imguiWidgetsEnabled = true;
};