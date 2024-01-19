#pragma once

#include <dxgi1_5.h>
#include "DXGIDeviceSubObject.h"
#include "WinResult.h"
#include "CommonMacros.h"

namespace SWApi
{
namespace DXGI
{
	class Surface;

#define DXGISWAPCHAIN_VERSIONS (0, 1, 2, 3, 4)
#define NUM_DXGISWAPCHAIN_VERSIONS 5

	class SwapChain : public DeviceSubObject
	{
	public:
		SwapChain() = default;
		SwapChain(const SwapChain& other);
		SwapChain(SwapChain&& other);

		~SwapChain();

		template<typename DXGISwapChainT>
		void SetNative(DXGISwapChainT* swapChainPtr);

		GETNATIVE_VERSIONED_VARIABLES(DXGISWAPCHAIN_VERSIONS, NUM_DXGISWAPCHAIN_VERSIONS, IDXGISwapChain, mSwapChain)

		auto GetBuffer(UINT bufferIndex) -> WinResult<Surface>;

		auto Present(UINT SyncInterval, UINT Flags) -> WinResult<void>;

	private:
		DECLARE_VERSIONED_POINTER_VARIABLES(DXGISWAPCHAIN_VERSIONS, NUM_DXGISWAPCHAIN_VERSIONS, IDXGISwapChain, mSwapChain, nullptr)

	};

	template<typename DXGISwapChainT>
	inline void SwapChain::SetNative(DXGISwapChainT* swapChainPtr)
	{
		if (swapChainPtr == nullptr) return;

		IDXGIDeviceSubObject* deviceSubObjPtr = nullptr;
		auto hres = swapChainPtr->QueryInterface(&deviceSubObjPtr);
		if (hres != S_OK) return;
		DeviceSubObject::SetNative(deviceSubObjPtr);

		RELEASE_VERSIONED_VARIABLES(DXGISWAPCHAIN_VERSIONS, NUM_DXGISWAPCHAIN_VERSIONS, mSwapChain)

		QUERY_INTERFACE_VERSIONED_VARIABLES(DXGISWAPCHAIN_VERSIONS, NUM_DXGISWAPCHAIN_VERSIONS, mSwapChain, swapChainPtr, /*no return*/);

		swapChainPtr->Release();
	}
}
}
