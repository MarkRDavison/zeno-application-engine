#pragma once

#include <functional>
#include <filesystem>

#include <volk.h>

#include <zae/Core/Utils/NonCopyable.hpp>
#include <zae/Core/Math/Vector2.hpp>
#include <zae/Engine/Devices/Monitor.hpp>
#include <zae/Engine/Devices/WindowTypes.hpp>
#include <zae/Engine/Devices/Cursor.hpp>

struct GLFWwindow;

namespace zae
{

	using WindowId = std::size_t;

	class Window : NonCopyable
	{
	public:
		Window(std::size_t id);
		~Window();

		void Update();

		/**
		 * Gets the size of the window in pixels.
		 * @param checkFullscreen If in fullscreen and true size will be the screens size.
		 * @return The size of the window.
		 */
		const Vector2ui& GetSize(bool checkFullscreen = true) const { return (fullscreen && checkFullscreen) ? fullscreenSize : size; }

		/**
		 * Sets the window size.
		 * @param size The new size in pixels.
		 */
		void SetSize(const Vector2i& size);

		/**
		 * Gets the aspect ratio between the windows width and height.
		 * @return The aspect ratio.
		 */
		float GetAspectRatio() const { return static_cast<float>(GetSize().x) / static_cast<float>(GetSize().y); }

		/**
		 * Gets the windows position in pixels.
		 * @return The windows position.
		 */
		const Vector2ui& GetPosition() const { return position; }

		/**
		 * Sets the window position to a new position in pixels.
		 * @param position The new position in pixels.
		 */
		void SetPosition(const Vector2i& position);

		/**
		 * Gets the window's title.
		 * @return The window's title.
		 */
		const std::string& GetTitle() const { return title; }

		/**
		 * Sets window title.
		 * @param title The new title.
		 */
		void SetTitle(const std::string& title);

		/**
		 * Sets window icon images.
		 * @param filenames The new icon files.
		 */
		void SetIcons(const std::vector<std::filesystem::path>& filenames);

		/**
		 * Gets weather the window is borderless or not.
		 * @return If the window is borderless.
		 */
		bool IsBorderless() const { return borderless; }

		/**
		 * Sets the window to be borderless.
		 * @param borderless Weather or not to be borderless.
		 */
		void SetBorderless(bool borderless);

		/**
		 * Gets weather the window is resizable or not.
		 * @return If the window is resizable.
		 */
		bool IsResizable() const { return resizable; }

		/**
		 * Sets the window to be resizable.
		 * @param resizable Weather or not to be resizable.
		 */
		void SetResizable(bool resizable);

		/**
		 * Gets weather the window is floating or not, if floating the window will always display above other windows.
		 * @return If the window is floating.
		 */
		bool IsFloating() const { return floating; }

		/**
		 * Sets the window to be floating.
		 * @param floating Weather or not to be floating.
		 */
		void SetFloating(bool floating);

		/**
		 * Gets weather the window is fullscreen or not.
		 * @return Fullscreen or windowed.
		 */
		bool IsFullscreen() const { return fullscreen; }

		/**
		 * Sets the window to be fullscreen or windowed.
		 * @param fullscreen If the window will be fullscreen.
		 * @param monitor The monitor to display in.
		 */
		void SetFullscreen(bool fullscreen, Monitor* monitor = nullptr);

		/**
		 * Gets if the window is closed.
		 * @return If the window is closed.
		 */
		bool IsClosed() const { return closed; }

		/**
		 * Gets if the window is selected.
		 * @return If the window is selected.
		 */
		bool IsFocused() const { return focused; }

		/**
		 * Gets the windows is minimized.
		 * @return If the window is minimized.
		 */
		bool IsIconified() const { return iconified; }

		/**
		 * Sets the window to be iconified (minimized).
		 * @param iconify If the window will be set as iconified.
		 */
		void SetIconified(bool iconify);

		/**
		 * Gets the contents of the clipboard as a string.
		 * @return If the clipboard contents.
		 */
		std::string GetClipboard() const;

		/**
		 * Sets the clipboard to the specified string.
		 * @param string The string to set as the clipboard.
		 */
		void SetClipboard(const std::string& string) const;

		/**
		 * Gets if the display is selected.
		 * @return If the display is selected.
		 */
		bool IsWindowSelected() const { return windowSelected; }

		/**
		 * If the cursor is hidden, the mouse is the display locked if true.
		 * @return If the cursor is hidden.
		 */
		bool IsCursorHidden() const { return cursorHidden; }

		/**
		 * Sets if the operating systems cursor is hidden whilst in the display.
		 * @param hidden If the system cursor should be hidden when not shown.
		 */
		void SetCursorHidden(bool hidden);

		/**
		 * Sets the cursor new style.
		 * @param cursor The cursor style to use.
		 */
		void SetCursor(const Cursor* cursor);

		/**
		 * Gets the current state of a key.
		 * @param key The key to get the state of.
		 * @return The keys state.
		 */
		InputAction GetKey(Key key) const;

		/**
		 * Gets the current state of a mouse button.
		 * @param mouseButton The mouse button to get the state of.
		 * @return The mouse buttons state.
		 */
		InputAction GetMouseButton(MouseButton mouseButton) const;

		/**
		 * Gets the mouses position.
		 * @return The mouses position.
		 */
		const Vector2d& GetMousePosition() const { return mousePosition; }

		/**
		 * Sets the mouse position.
		 * @param position The new mouse position.
		 */
		void SetMousePosition(const Vector2d& mousePosition);

		/**
		 * Gets the mouse position delta.
		 * @return The mouse position delta.
		 */
		const Vector2d& GetMousePositionDelta() const { return mousePositionDelta; }

		/**
		 * Gets the mouses virtual scroll position.
		 * @return The mouses virtual scroll position.
		 */
		const Vector2d& GetMouseScroll() const { return mouseScroll; }

		/**
		 * Sets the mouse virtual scroll position.
		 * @param scroll The new mouse virtual scroll position.
		 */
		void SetMouseScroll(const Vector2d& scroll);

		/**
		 * Gets the mouse scroll delta.
		 * @return The mouse scroll delta.
		 */
		const Vector2d& GetMouseScrollDelta() const { return mouseScrollDelta; }

		static std::string ToString(Key key);

		GLFWwindow* GetWindow() const { return window; }

		const Monitor* GetCurrentMonitor() const;

		VkResult CreateSurface(const VkInstance& instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface) const;

		/**
		 * Called when the window is resized.
		 * @return The std::function.
		 */
		Signal<Vector2ui>& OnSize() { return onSize; }

		/**
		 * Called when the window is moved.
		 * @return The std::function.
		 */
		Signal<Vector2ui>& OnPosition() { return onPosition; }

		/**
		 * Called when the windows title changed.
		 * @return The std::function.
		 */
		Signal<std::string>& OnTitle() { return onTitle; }

		/**
		 * Called when the window has toggled borderless on or off.
		 * @return The std::function.
		 */
		Signal<bool>& OnBorderless() { return onBorderless; }

		/**
		 * Called when the window has toggled resizable on or off.
		 * @return The std::function.
		 */
		Signal<bool>& OnResizable() { return onResizable; }

		/**
		 * Called when the window has toggled floating on or off.
		 * @return The std::function.
		 */
		Signal<bool>& OnFloating() { return onFloating; }

		/**
		 * Called when the has gone fullscreen or windowed.
		 * @return The std::function.
		 */
		Signal<bool>& OnFullscreen() { return onFullscreen; }

		/**
		 * Called when the window requests a close.
		 * @return The std::function.
		 */
		Signal<>& OnClose() { return onClose; }

		/**
		 * Called when the window is focused or unfocused.
		 * @return The std::function.
		 */
		Signal<bool>& OnFocus() { return onFocus; }

		/**
		 * Called when the window is minimized or maximized.
		 * @return The std::function.
		 */
		Signal<bool>& OnIconify() { return onIconify; }

		/**
		 * Called when the mouse enters the window.
		 * @return The delegate.
		 */
		Signal<bool>& OnEnter() { return onEnter; }

		/**
		 * Called when a group of files/folders is dropped onto the window.
		 * @return The delegate.
		 */
		Signal<std::vector<std::string>>& OnDrop() { return onDrop; }

		/**
		 * Called when a key changes state.
		 * @return The delegate.
		 */
		Signal<Key, InputAction, InputMod>& OnKey() { return onKey; }

		/**
		 * Called when a character has been typed.
		 * @return The delegate.
		 */
		Signal<char>& OnChar() { return onChar; }

		/**
		 * Called when a mouse button changes state.
		 * @return The delegate.
		 */
		Signal<MouseButton, InputAction, InputMod>& OnMouseButton() { return onMouseButton; }

		/**
		 * Called when the mouse moves.
		 * @return The delegate.
		 */
		Signal<Vector2d>& OnMousePosition() { return onMousePosition; }

		/**
		 * Called when the scroll wheel changes.
		 * @return The delegate.
		 */
		Signal<Vector2d>& OnMouseScroll() { return onMouseScroll; }

	private:
		friend void CallbackWindowPosition(GLFWwindow* glfwWindow, int32_t xpos, int32_t ypos);
		friend void CallbackWindowSize(GLFWwindow* glfwWindow, int32_t width, int32_t height);
		friend void CallbackWindowClose(GLFWwindow* glfwWindow);
		friend void CallbackWindowFocus(GLFWwindow* glfwWindow, int32_t focused);
		friend void CallbackWindowIconify(GLFWwindow* glfwWindow, int32_t iconified);
		friend void CallbackFramebufferSize(GLFWwindow* glfwWindow, int32_t width, int32_t height);
		friend void CallbackCursorEnter(GLFWwindow* glfwWindow, int32_t entered);
		friend void CallbackDrop(GLFWwindow* glfwWindow, int32_t count, const char** paths);
		friend void CallbackKey(GLFWwindow* glfwWindow, int32_t key, int32_t scancode, int32_t action, int32_t mods);
		friend void CallbackChar(GLFWwindow* glfwWindow, uint32_t codepoint);
		friend void CallbackMouseButton(GLFWwindow* glfwWindow, int32_t button, int32_t action, int32_t mods);
		friend void CallbackCursorPos(GLFWwindow* glfwWindow, double xpos, double ypos);
		friend void CallbackScroll(GLFWwindow* glfwWindow, double xoffset, double yoffset);

		static double SmoothScrollWheel(double value, float delta);

		std::size_t id;
		GLFWwindow* window = nullptr;

		Vector2ui size;
		Vector2ui fullscreenSize;

		Vector2ui position;

		std::string title;
		bool borderless = false;
		bool resizable = false;
		bool floating = false;
		bool fullscreen = false;

		bool closed = false;
		bool focused = false;
		bool iconified = false;

		bool windowSelected = false;
		bool cursorHidden = false;

		Vector2d mouseLastPosition;
		Vector2d mousePosition;
		Vector2d mousePositionDelta;
		Vector2d mouseLastScroll;
		Vector2d mouseScroll;
		Vector2d mouseScrollDelta;

		Signal<Vector2ui> onSize;
		Signal<Vector2ui> onPosition;
		Signal<std::string> onTitle;
		Signal<bool> onBorderless;
		Signal<bool> onResizable;
		Signal<bool> onFloating;
		Signal<bool> onFullscreen;
		Signal<> onClose;
		Signal<bool> onFocus;
		Signal<bool> onIconify;
		Signal<bool> onEnter;
		Signal<std::vector<std::string>> onDrop;
		Signal<Key, InputAction, InputMod> onKey;
		Signal<char> onChar;
		Signal<MouseButton, InputAction, InputMod> onMouseButton;
		Signal<Vector2d> onMousePosition;
		Signal<Vector2d> onMouseScroll;
	};
}

