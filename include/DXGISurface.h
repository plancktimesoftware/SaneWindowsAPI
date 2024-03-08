#pragma once

#include <dxgi1_2.h>
#include "DXGIDeviceSubObject.h"
#include "CommonMacros.h"

namespace SWApi
{
namespace DXGI
{
#define DXGISURFACE_VERSIONS (0, 1 ,2)
#define NUM_DXGISURFACE_VERSIONS 3

	class Surface : public DeviceSubObject
	{
	public:
		Surface() = default;
		Surface(const Surface& other);
		Surface(Surface&& other) noexcept(true);

		~Surface();

		template<typename DXGISurfaceT>
		void SetNative(DXGISurfaceT* surfacePtr);

		GETNATIVE_VERSIONED_VARIABLES(DXGISURFACE_VERSIONS, NUM_DXGISURFACE_VERSIONS, IDXGISurface, mSurface)

	private:
		DECLARE_VERSIONED_POINTER_VARIABLES(DXGISURFACE_VERSIONS, NUM_DXGISURFACE_VERSIONS, IDXGISurface, mSurface, nullptr)

	};

	template<typename DXGISurfaceT>
	inline void Surface::SetNative(DXGISurfaceT* surfacePtr)
	{
		if (surfacePtr == nullptr) return;

		IDXGIDeviceSubObject* deviceSubObjPtr = nullptr;
		auto hres = surfacePtr->QueryInterface(&deviceSubObjPtr);
		if (hres != S_OK) return;
		DeviceSubObject::SetNative(deviceSubObjPtr);

		RELEASE_VERSIONED_VARIABLES(DXGISURFACE_VERSIONS, NUM_DXGISURFACE_VERSIONS, mSurface)

		QUERY_INTERFACE_VERSIONED_VARIABLES(DXGISURFACE_VERSIONS, NUM_DXGISURFACE_VERSIONS, mSurface, surfacePtr, /*no return*/);

		surfacePtr->Release();
	}
}
}
