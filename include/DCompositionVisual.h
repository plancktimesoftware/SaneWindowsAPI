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
#define DCOMPVISUAL_VERSIONS (0, 2, 3)
#define NUM_DCOMPVISUAL_VERSIONS 3

	class Visual : public Unknown
	{
	public:
		auto SetContent(const DXGI::SwapChain& swapChain) -> WinResult<void>;

		Visual() = default;
		Visual(const Visual& other);
		Visual(Visual&& other) noexcept(true);

		~Visual();

		GETNATIVE_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM_DCOMPVISUAL_VERSIONS, IDCompositionVisual, mVisual)

		template<typename DCompVisualT>
		void SetNative(DCompVisualT* dCompVisualPtr);
	private:
		DECLARE_VERSIONED_POINTER_VARIABLES(DCOMPVISUAL_VERSIONS, NUM_DCOMPVISUAL_VERSIONS, IDCompositionVisual, mVisual, nullptr)
	};

	template<typename DCompVisualT>
	inline void Visual::SetNative(DCompVisualT* dCompVisualPtr)
	{
		if (dCompVisualPtr == nullptr) return;

		IUnknown* unknownPtr = nullptr;
		auto hres = dCompVisualPtr->QueryInterface(&unknownPtr);
		if (hres != S_OK) return;
		Unknown::SetNative(unknownPtr);

		RELEASE_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM_DCOMPVISUAL_VERSIONS, mVisual)

		QUERY_INTERFACE_VERSIONED_VARIABLES(DCOMPVISUAL_VERSIONS, NUM_DCOMPVISUAL_VERSIONS, mVisual, dCompVisualPtr, /*no return*/)

		dCompVisualPtr->Release();
	}
}
}
