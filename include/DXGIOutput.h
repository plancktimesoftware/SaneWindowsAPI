#pragma once

#include <dxgi1_6.h>
#include "DXGIObject.h"
#include "CommonMacros.h"

namespace SWApi
{
namespace DXGI
{

#define DXGIOUTPUT_VERSIONS (0, 1, 2, 3, 4, 5, 6)
#define NUM_DXGIOUTPUT_VERSIONS 7

	class Output : public Object
	{
	public:
		Output() = default;
		Output(const Output& other);
		Output(Output&& other) noexcept(true);

		~Output();

		GETNATIVE_VERSIONED_VARIABLES(DXGIOUTPUT_VERSIONS, NUM_DXGIOUTPUT_VERSIONS, IDXGIOutput, mOutput)

		template<typename DXGIOutputT>
		void SetNative(DXGIOutputT* outputPtr);

	private:
		DECLARE_VERSIONED_POINTER_VARIABLES(DXGIOUTPUT_VERSIONS, NUM_DXGIOUTPUT_VERSIONS, IDXGIOutput, mOutput, nullptr)
	};

	template<typename DXGIOutputT>
	inline void Output::SetNative(DXGIOutputT* outputPtr)
	{
		if (outputPtr == nullptr) return;

		IDXGIObject* dxgiObjectPtr = nullptr;
		auto hres = outputPtr->QueryInterface(&dxgiObjectPtr);
		if (hres != S_OK) return;
		Object::SetNative(dxgiObjectPtr);

		RELEASE_VERSIONED_VARIABLES(DXGIOUTPUT_VERSIONS, NUM_DXGIOUTPUT_VERSIONS, mOutput)

		QUERY_INTERFACE_VERSIONED_VARIABLES(DXGIOUTPUT_VERSIONS, NUM_DXGIOUTPUT_VERSIONS, mOutput, outputPtr, /*no return*/);

		outputPtr->Release();
	}
}
}

