
#include "Module.h"

namespace SWApi
{
	auto Module::Load(const std::wstring& path) -> WinResult<Module>
	{
		auto hModule = LoadLibraryW(path.c_str());
		if (hModule == nullptr)
			return Err(HRESULT_FROM_WIN32(GetLastError()));

		Module m;
		m.SetNative(hModule, true);
		return m;
	}

	auto Module::LoadEx(const std::wstring& path, DWORD flags) -> WinResult<Module>
	{
		auto hModule = LoadLibraryExW(path.c_str(), NULL, flags);
		if (hModule == nullptr)
			return Err(HRESULT_FROM_WIN32(GetLastError()));

		Module m;
		m.SetNative(hModule, true);
		return m;
	}

	auto Module::GetFilePath() -> std::wstring
	{
		WCHAR path[MAX_PATH];
		auto len = GetModuleFileNameW(GetNative(), path, MAX_PATH);
		return std::wstring(path);
	}

	void Module::SetNative(HMODULE hModule, bool owned)
	{
		struct ModuleDeleterOwned
		{
			void operator() (HMODULE hModule) { FreeLibrary(hModule); }
		};

		struct ModuleDeleterNotOwned
		{
			void operator() (HMODULE) { }
		};

		if (owned)
			mModuleSharedPtr = ModuleSharedPtr(hModule, ModuleDeleterOwned());
		else
			mModuleSharedPtr = ModuleSharedPtr(hModule, ModuleDeleterNotOwned());
	}
}

