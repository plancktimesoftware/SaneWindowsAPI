#pragma once

#include <optional>
#include <dxgi1_6.h>
#include "WinResult.h"
#include "DXGIObject.h"
#include "CommonMacros.h"

namespace SWApi
{
namespace DXGI
{
	class Device;
	class SwapChain;
	class Output;

#define DXGIFACTORY_VERSIONS (0, 1, 2, 3, 4, 5, 6)
#define NUM_DXGIFACTORY_VERSIONS 7

	class Factory : public Object
	{
	public:
		static auto Create(UINT flags) -> WinResult<Factory>;

		Factory() = default;
		Factory(const Factory& other);
		Factory(Factory&& other) noexcept(true);

		~Factory();

		template<typename DXGIFactoryT>
		void SetNative(DXGIFactoryT* factoryPtr);

		auto CreateSwapChain(const Device& device, const DXGI_SWAP_CHAIN_DESC& desc)
			-> WinResult<SwapChain>;

		auto CreateSwapChainForComposition(
			const Device& device, const DXGI_SWAP_CHAIN_DESC1& desc,
			std::optional<Output> restrictToOutput)
			-> WinResult<SwapChain>;

	private:
		DECLARE_VERSIONED_POINTER_VARIABLES(DXGIFACTORY_VERSIONS, NUM_DXGIFACTORY_VERSIONS, IDXGIFactory, mFactory, nullptr)
	};

	template<typename DXGIFactoryT>
	inline void Factory::SetNative(DXGIFactoryT* factoryPtr)
	{
		if (factoryPtr == nullptr) return;

		IDXGIObject* dxgiObjectPtr = nullptr;
		auto hres = factoryPtr->QueryInterface(&dxgiObjectPtr);
		if (hres != S_OK) return;
		Object::SetNative(dxgiObjectPtr);

		RELEASE_VERSIONED_VARIABLES(DXGIFACTORY_VERSIONS, NUM_DXGIFACTORY_VERSIONS, mFactory)
		
		QUERY_INTERFACE_VERSIONED_VARIABLES(DXGIFACTORY_VERSIONS, NUM_DXGIFACTORY_VERSIONS, mFactory, factoryPtr, /*no return*/);

		factoryPtr->Release();
	}
}
}
