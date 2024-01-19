#pragma once

#include <string>
#include <memory>

namespace SWApi
{
	class Module
	{
	public:
		static Module Load(const std::wstring& path);
		static Module LoadEx(const std::wstring& path, DWORD flags);

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



