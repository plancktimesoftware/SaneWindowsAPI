
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

	auto Window::GetRect() const -> WinResult<Rect>
	{
		RECT rect{};
		BOOL res = GetWindowRect(GetNative(), &rect);
		if (res == FALSE)
			return Err(HRESULT_FROM_WIN32(GetLastError()));
		return Rect(rect);
	}

	auto Window::Show(int nCmdShow) -> bool
	{
		return ShowWindow(GetNative(), nCmdShow);
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
