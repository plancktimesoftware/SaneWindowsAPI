
#include "Window.h"
#include "Module.h"
#include "Geometry.h"

namespace SWApi
{
	auto Window::Create(
		std::wstring_view className, std::wstring_view windowName,
		DWORD dwStyle, DWORD dwExStyle, const Rect& rect,
		std::optional<Window> parent, std::optional<HMENU> hMenu,
		std::optional<Module> associatedModule, std::optional<LPVOID> lpParam)
		-> WinResult<Window>
	{
		std::wstring classNameStr{ className };
		std::wstring windowNameStr{ windowName };
		HWND hwnd = CreateWindowExW(
			dwExStyle, classNameStr.c_str(), windowNameStr.c_str(), dwStyle,
			rect.left, rect.top, rect.Width(), rect.Height(),
			parent ? parent->GetNative() : nullptr, hMenu.value_or(nullptr),
			associatedModule ? associatedModule->GetNative() : nullptr,
			lpParam.value_or(nullptr));

		if (hwnd == nullptr)
			return Err(HRESULT_FROM_WIN32(GetLastError()));

		Window win;
		win.SetNative(hwnd);
		return win;
	}

	auto Window::IsEnabled() const -> bool
	{
		return GetNative() && IsWindowEnabled(GetNative());
	}

	auto Window::IsVisible() const -> bool
	{
		return GetNative() && IsWindowVisible(GetNative());
	}

	auto Window::Enable(bool bEnable) -> bool
	{
		return GetNative() && EnableWindow(GetNative(), bEnable ? TRUE : FALSE);
	}

	auto Window::Show(int nCmdShow) -> bool
	{
		return GetNative() && ShowWindow(GetNative(), nCmdShow);
	}

	auto Window::GetRect() const -> WinResult<Rect>
	{
		RECT rect{};
		BOOL res = GetWindowRect(GetNative(), &rect);
		if (res == FALSE)
			return Err(HRESULT_FROM_WIN32(GetLastError()));
		return Rect(rect);
	}

	auto Window::SetRect(Rect rect) const -> WinResult<void>
	{
		BOOL result = SetWindowPos(GetNative(), nullptr,
								   rect.left, rect.right, rect.Width(), rect.Height(),
								   SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER);
		if (result == FALSE)
			return Err(HRESULT_FROM_WIN32(GetLastError()));
		return WinResult<void>();
	}

	auto Window::SetZOrderRelative(Window windowInsertAfter) -> WinResult<void>
	{
		BOOL result = SetWindowPos(GetNative(), windowInsertAfter.GetNative(),
								   0, 0, 0, 0,
								   SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
		if (result == FALSE)
			return Err(HRESULT_FROM_WIN32(GetLastError()));
		return WinResult<void>();
	}

	auto Window::SetZOrderAbsolute(ZOrder zorder) -> WinResult<void>
	{
		HWND zorderHwnd = reinterpret_cast<HWND>(zorder);
		BOOL result = SetWindowPos(GetNative(), zorderHwnd,
								   0, 0, 0, 0,
								   SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
		if (result == FALSE)
			return Err(HRESULT_FROM_WIN32(GetLastError()));
		return WinResult<void>();
	}

	auto Window::GetStyleFlags() -> WinResult<DWORD>
	{
		SetLastError(NOERROR);
		LONG_PTR value = GetWindowLongPtr(GetNative(), GWL_STYLE);
		if (value == 0 && GetLastError() != NOERROR)
			return Err(HRESULT_FROM_WIN32(GetLastError()));
		return static_cast<DWORD>(value);
	}

	auto Window::SetStyleFlags(DWORD styleFlags) -> WinResult<void>
	{
		SetLastError(NOERROR);
		LONG_PTR result = SetWindowLongPtr(GetNative(), GWL_STYLE,
										   static_cast<LONG_PTR>(styleFlags));
		if (result == 0 && GetLastError() != NOERROR)
			return Err(HRESULT_FROM_WIN32(GetLastError()));
		return WinResult<void>();
	}

	auto Window::GetExStyleFlags() -> WinResult<DWORD>
	{
		SetLastError(NOERROR);
		LONG_PTR value = GetWindowLongPtr(GetNative(), GWL_EXSTYLE);
		if (value == 0 && GetLastError() != NOERROR)
			return Err(HRESULT_FROM_WIN32(GetLastError()));
		return static_cast<DWORD>(value);
	}

	auto Window::SetExStyleFlags(DWORD exStyleFlags) -> WinResult<void>
	{
		SetLastError(NOERROR);
		LONG_PTR result = SetWindowLongPtr(GetNative(), GWL_EXSTYLE,
										   static_cast<LONG_PTR>(exStyleFlags));
		if (result == 0 && GetLastError() != NOERROR)
			return Err(HRESULT_FROM_WIN32(GetLastError()));
		return WinResult<void>();
	}

	void Window::Update()
	{
		UpdateWindow(GetNative());
	}

	void Window::SetNative(HWND hwnd)
	{
		struct HWNDDeleter
		{
			void operator()(HWND hwnd) { DestroyWindow(hwnd); }
		};
		mHWNDSharedPtr = HWNDSharedPtr(hwnd, HWNDDeleter());
	}
}
