#pragma once

#include <dcomp.h>
#include "WinResult.h"
#include "Wrapper.h"
#include "CommonMacros.h"

namespace SWApi
{
namespace DXGI
{
	class SwapChain;
}

namespace DComposition
{

#if NTDDI_VERSION >= 0x0A000000//NTDDI_WINTHRESHOLD
#define DCOMPVISUAL_VERSIONS (0, 2, 3)
#elif NTDDI_VERSION >= 0x06030000//NTDDI_WINBLUE
#define DCOMPVISUAL_VERSIONS (0, 2)
#elif NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
#define DCOMPVISUAL_VERSIONS (0)
#endif

	class Visual : public Unknown
	{
	public:
		auto SetContent(const DXGI::SwapChain& swapChain) -> WinResult<void>;

		Visual() = default;
		Visual(const Visual& other);
		Visual(Visual&& other) noexcept(true);

		~Visual();

#if NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
		GETNATIVE_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM(DCOMPVISUAL_VERSIONS), IDCompositionVisual, mVisual)

		template<typename DCompVisualT>
		void SetNative(DCompVisualT* dCompVisualPtr);
	private:
		DECLARE_VERSIONED_POINTER_VARIABLES(DCOMPVISUAL_VERSIONS, NUM(DCOMPVISUAL_VERSIONS), IDCompositionVisual, mVisual, nullptr)
#endif NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
	};

#if NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
	template<typename DCompVisualT>
	inline void Visual::SetNative(DCompVisualT* dCompVisualPtr)
	{
		if (dCompVisualPtr == nullptr) return;

		IUnknown* unknownPtr = nullptr;
		auto hres = dCompVisualPtr->QueryInterface(&unknownPtr);
		if (hres != S_OK) return;
		Unknown::SetNative(unknownPtr);

		RELEASE_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM(DCOMPVISUAL_VERSIONS), mVisual)

		QUERY_INTERFACE_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM(DCOMPVISUAL_VERSIONS), mVisual, dCompVisualPtr, /*no return*/)

		dCompVisualPtr->Release();
	}
#endif NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
}
}
