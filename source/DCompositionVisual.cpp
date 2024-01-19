#include "DCompositionVisual.h"
#include "DXGISwapChain.h"

namespace SWApi
{
namespace DComposition
{
	auto Visual::SetContent(const DXGI::SwapChain& swapChain) -> WinResult<void>
	{
		if (mVisualV0 == nullptr) return Err(E_POINTER);

		IDXGISwapChain1* swapChainV1 = swapChain.GetNative<IDXGISwapChain1>();
		if (swapChainV1 == nullptr) return Err(E_POINTER);

		auto hres = mVisualV0->SetContent(swapChainV1);
		if (hres != S_OK) return Err(hres);

		return WinResult<void>();
	}

	Visual::Visual(const Visual& other)
		: Unknown(other)
		INITIALIZE_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM_DCOMPVISUAL_VERSIONS, mVisual, other.mVisual)
	{
		ADDREF_TO_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM_DCOMPVISUAL_VERSIONS, mVisual);
	}
	Visual::Visual(Visual&& other)
		: Unknown(std::forward<Unknown>(other))
		INITIALIZE_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM_DCOMPVISUAL_VERSIONS, mVisual, other.mVisual)
	{
		ASSIGN_TO_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM_DCOMPVISUAL_VERSIONS, other.mVisual, nullptr)
	}

	Visual::~Visual()
	{
		RELEASE_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM_DCOMPVISUAL_VERSIONS, mVisual)
	}
}
}
