#include "DXGISwapChain.h"
#include "DXGISurface.h"

namespace SWApi
{
namespace DXGI
{
	SwapChain::SwapChain(const SwapChain& other)
		: DeviceSubObject(other)
		INITIALIZE_VERSIONED_VARIABLES(DXGISWAPCHAIN_VERSIONS, NUM_DXGISWAPCHAIN_VERSIONS, mSwapChain, other.mSwapChain)
	{
		ADDREF_TO_VERSIONED_VARIABLES(DXGISWAPCHAIN_VERSIONS, NUM_DXGISWAPCHAIN_VERSIONS, mSwapChain)
	}

	SwapChain::SwapChain(SwapChain&& other)
		: DeviceSubObject(std::forward<DeviceSubObject>(other))
		INITIALIZE_VERSIONED_VARIABLES(DXGISWAPCHAIN_VERSIONS, NUM_DXGISWAPCHAIN_VERSIONS, mSwapChain, other.mSwapChain)
	{
		ASSIGN_TO_VERSIONED_VARIABLES(DXGISWAPCHAIN_VERSIONS, NUM_DXGISWAPCHAIN_VERSIONS, other.mSwapChain, nullptr)
	}

	SwapChain::~SwapChain()
	{
		RELEASE_VERSIONED_VARIABLES(DXGISWAPCHAIN_VERSIONS, NUM_DXGISWAPCHAIN_VERSIONS, mSwapChain)
	}

	auto SwapChain::GetBuffer(UINT bufferIndex) -> WinResult<Surface>
	{
		IDXGISurface2* surfacePtr = nullptr;
		auto hres = mSwapChainV0->GetBuffer(bufferIndex, __uuidof(IDXGISurface2), reinterpret_cast<void**>(&surfacePtr));
		if (hres != S_OK)
			return Err(hres);
	
		Surface surface;
		surface.SetNative(surfacePtr);
		return surface;
	}

	auto SwapChain::Present(UINT syncInterval, UINT flags) -> WinResult<void>
	{
		auto hres = mSwapChainV0->Present(syncInterval, flags);
		if (hres != S_OK)
			return Err(hres);

		return WinResult<void>();
	}
}
}
