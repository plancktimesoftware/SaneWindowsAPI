#include "DCompositionVisual.h"
#include "DXGISwapChain.h"

namespace SWApi
{
namespace DComposition
{
	auto Visual::SetContent(const DXGI::SwapChain& swapChain) -> WinResult<void>
	{
#if NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
		if (mVisualV0 == nullptr) return Err(E_POINTER);

		IDXGISwapChain1* swapChainV1 = swapChain.GetNative<IDXGISwapChain1>();
		if (swapChainV1 == nullptr) return Err(E_POINTER);

		auto hres = mVisualV0->SetContent(swapChainV1);
		if (hres != S_OK) return Err(hres);

		return WinResult<void>();
#else //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
		return Err(E_NOINTERFACE);
#endif //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
	}

#if NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
	Visual::Visual(const Visual& other)
		: Unknown(other)
		INITIALIZE_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM(DCOMPVISUAL_VERSIONS), mVisual, other.mVisual)
	{
		ADDREF_TO_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM(DCOMPVISUAL_VERSIONS), mVisual);
	}
	Visual::Visual(Visual&& other) noexcept(true)
		: Unknown(std::forward<Unknown>(other))
		INITIALIZE_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM(DCOMPVISUAL_VERSIONS), mVisual, other.mVisual)
	{
		ASSIGN_TO_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM(DCOMPVISUAL_VERSIONS), other.mVisual, nullptr)
	}

	Visual::~Visual()
	{
		RELEASE_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM(DCOMPVISUAL_VERSIONS), mVisual)
	}

#else //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8

	Visual::Visual(const Visual& other)
		: Unknown(other)
	{}
	Visual::Visual(Visual&& other) noexcept(true)
		: Unknown(std::forward<Unknown>(other))
	{}

	Visual::~Visual()
	{}

#endif //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
}
}
