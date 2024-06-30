#pragma once

#include <memory>
#include <string_view>
#include <optional>
#include "WinResult.h"

namespace SWApi
{
	struct Rect;
	class Module;

	/**
	 * Enum containing special z-order values supported by Windows.
	 * See https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowpos
	 * Type is intptr_t so it can be reinterpret_cast to HWND.
	 */
	enum class ZOrder : intptr_t
	{
		kTop = 0, //HWND_TOP
		kBottom = 1, //HWND_BOTTOM
		kTopMost = -1, //HWND_TOPMOST
		kNoTopMost = -2	//HWND_NOTOPMOST
	};

	class Window
	{
	public:
		static auto Create(
			std::wstring_view className, std::wstring_view WindowName,
			DWORD dwStyle, DWORD dwExStyle, const Rect& rect,
			std::optional<Window> parent,
			std::optional<HMENU> hMenu,
			std::optional<Module> associatedModule,
			std::optional<LPVOID> lpParam) -> WinResult<Window>;

		auto IsEnabled() const -> bool;
		auto IsVisible() const -> bool;
		auto Enable(bool bEnable) -> bool;
		/**
		 * Sets the window's show state.
		 * \param nCmdShow Controls how the window is to be shown.
		 *		  See https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
		 * \return If the window was previously visible, returns true.
		 *		   If the window was previously hidden, returns false.
		 */
		auto Show(int nCmdShow) -> bool;

		auto GetRect() const->WinResult<Rect>;
		auto SetRect(Rect rect) const -> WinResult<void>;
		auto SetZOrderRelative(Window windowInsertAfter) -> WinResult<void>;
		auto SetZOrderAbsolute(ZOrder zorder) -> WinResult<void>;

		auto GetStyleFlags() -> WinResult<DWORD>;
		auto SetStyleFlags(DWORD styleFlags) -> WinResult<void>;
		auto GetExStyleFlags() -> WinResult<DWORD>;
		auto SetExStyleFlags(DWORD exStyleFlags) -> WinResult<void>;

		void Update();

		Window() = default;
		Window(const Window& other) = default;
		Window(Window&& other) = default;
		~Window() {}

		auto GetNative() const -> HWND { return mHWNDSharedPtr.get(); }
		void SetNative(HWND hwnd);
	private:
		using HWNDSharedPtr = std::shared_ptr<HWND__>;
		HWNDSharedPtr mHWNDSharedPtr;
	};
}

