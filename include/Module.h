#pragma once

#include <string>
#include <memory>
#include "WinResult.h"

namespace SWApi
{
	class Module
	{
	public:
		static auto Load(const std::wstring& path) -> WinResult<Module>;
		static auto LoadEx(const std::wstring& path, DWORD flags) -> WinResult<Module>;

		auto GetFilePath() -> std::wstring;

		Module() = default;
		Module(const Module& other) = default;
		Module(Module&& other) = default;
		~Module() = default;

		auto GetNative() const -> HMODULE { return mModuleSharedPtr.get(); }

		void SetNative(HMODULE ModulePtr, bool owned);
	private:
		/**
		 * Unique pointer for storing pointers allocated using ASmalloc, AScalloc, etc.
		 * Has a custom deleter that calls ASfree when this unique pointer is destroyed.
		 */
		using ModuleSharedPtr = std::shared_ptr<HINSTANCE__>;
		ModuleSharedPtr mModuleSharedPtr;
	};

}



