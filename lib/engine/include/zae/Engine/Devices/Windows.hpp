#pragma once

#include <zae/Engine/Engine.hpp>
#include <zae/Engine/Devices/Window.hpp>

namespace zae
{
	class Windows
	{
		Windows();
		~Windows();

	public:
		static Windows* Get() // TODO: Better scope management
		{
			if (Instance == nullptr)
			{
				Instance = new Windows();
			}
			return Instance;
		}

		void Update();

		Window* AddWindow();
		const Window* GetWindow(WindowId id) const;
		Window* GetWindow(WindowId id);

		const std::vector<std::unique_ptr<Monitor>>& GetMonitors() const { return monitors; };

		const Monitor* GetPrimaryMonitor() const;

		/**
		 * Called when a window has been added or closed.
		 * @return The std::function.
		 */
		Signal<Window*, bool>& OnAddWindow() { return onAddWindow; }

		/**
		 * Called when a monitor has been connected or disconnected.
		 * @return The std::function.
		 */
		Signal<Monitor*, bool>& OnMonitorConnect() { return onMonitorConnect; }

		static std::string StringifyResultGlfw(int32_t result);
		static void CheckGlfw(int32_t result);

		std::pair<const char**, uint32_t> GetInstanceExtensions() const;

	private:
		static Windows* Instance;
		friend void CallbackError(int32_t error, const char* description);
		friend void CallbackMonitor(GLFWmonitor* glfwMonitor, int32_t event);

		std::vector<std::unique_ptr<Window>> windows;

		std::vector<std::unique_ptr<Monitor>> monitors;

		Signal<Window*, bool> onAddWindow;
		Signal<Monitor*, bool> onMonitorConnect;
	};
}
