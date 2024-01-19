#pragma once

#include <memory>
#include <string_view>
#include <optional>
#include "WinResult.h"

namespace SWApi
{
	struct Rect;
	class Module;

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

		auto GetRect() const -> WinResult<Rect>;

		Window() {}
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

