
#include "Module.h"

namespace SWApi
{
	struct ModuleDeleterOwned
	{
		void operator() (HMODULE hModule) { FreeLibrary(hModule); }
	};

	struct ModuleDeleterNotOwned
	{
		void operator() (HMODULE) { }
	};

	Module Module::Load(const std::wstring& path)
	{
		auto hModule = LoadLibraryW(path.c_str());
		Module m;
		m.SetNative(hModule, true);
		return m;
	}

	Module Module::LoadEx(const std::wstring& path, DWORD flags)
	{
		auto hModule = LoadLibraryExW(path.c_str(), NULL, flags);
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
		if (owned)
			mModuleSharedPtr = ModuleSharedPtr(hModule, ModuleDeleterOwned());
		else
			mModuleSharedPtr = ModuleSharedPtr(hModule, ModuleDeleterNotOwned());
	}
}

