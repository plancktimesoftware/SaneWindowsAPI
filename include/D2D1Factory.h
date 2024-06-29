#pragma once

#include <d2d1_3.h>
#include <optional>
#include "WinResult.h"
#include "Wrapper.h"
#include "CommonMacros.h"

namespace SWApi
{
namespace DXGI
{
	class Device;
}

namespace D2D1
{
	class Device;
	class PathGeometry;

#define D2D1FACTORY_VERSIONS (0, 1, 2, 3, 4, 5, 6, 7)

	class Factory : public Unknown
	{
	public:

		static auto Create(
			D2D1_FACTORY_TYPE factoryType,
			const std::optional<D2D1_FACTORY_OPTIONS>& factoryOptions)
			-> WinResult<Factory>;

		auto CreateDevice(const DXGI::Device& dxgiDevice) -> WinResult<Device>;

		auto CreatePathGeometry() -> WinResult<PathGeometry>;
	
		Factory() = default;
		Factory(const Factory& other);
		Factory(Factory&& other) noexcept(true);

		~Factory();

		template<typename D2D1FactoryT>
		void SetNative(D2D1FactoryT* factoryPtr);

	private:
		DECLARE_VERSIONED_POINTER_VARIABLES(D2D1FACTORY_VERSIONS, NUM(D2D1FACTORY_VERSIONS), ID2D1Factory, mFactory, nullptr)
	};

	template<typename D2D1FactoryT>
	inline void Factory::SetNative(D2D1FactoryT* factoryPtr)
	{
		if (factoryPtr == nullptr) return;

		IUnknown* unknownPtr = nullptr;
		auto hres = factoryPtr->QueryInterface(&unknownPtr);
		if (hres != S_OK) return;
		Unknown::SetNative(unknownPtr);

		RELEASE_VERSIONED_VARIABLES(D2D1FACTORY_VERSIONS, NUM(D2D1FACTORY_VERSIONS), mFactory)

		QUERY_INTERFACE_VERSIONED_VARIABLES(D2D1FACTORY_VERSIONS, NUM(D2D1FACTORY_VERSIONS), mFactory, factoryPtr, /*no return*/);

		factoryPtr->Release();
	}
}
}
