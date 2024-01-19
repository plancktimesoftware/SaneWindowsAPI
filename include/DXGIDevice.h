#pragma once

#include <dxgi1_5.h>
#include "Wrapper.h"
#include "CommonMacros.h"

namespace SWApi
{
namespace DXGI
{
#define DXGIDEVICE_VERSIONS (0, 1, 2, 3, 4)
#define NUM_DXGIDEVICE_VERSIONS 5

	class Device : public Unknown
	{
	public:
		Device() = default;
		Device(const Device& other);
		Device(Device&& other) noexcept;

		~Device();

		GETNATIVE_VERSIONED_VARIABLES(DXGIDEVICE_VERSIONS, NUM_DXGIDEVICE_VERSIONS, IDXGIDevice, mDevice)

		template<typename DXGIDeviceT>
		void SetNative(DXGIDeviceT* devicePtr);
	private:
		DECLARE_VERSIONED_POINTER_VARIABLES(DXGIDEVICE_VERSIONS, NUM_DXGIDEVICE_VERSIONS, IDXGIDevice, mDevice, nullptr)
	};

	template<typename DXGIDeviceT>
	inline void Device::SetNative(DXGIDeviceT* devicePtr)
	{
		if (devicePtr == nullptr) return;

		IUnknown* unknownPtr = nullptr;
		auto hres = devicePtr->QueryInterface(&unknownPtr);
		if (hres != S_OK) return;
		Unknown::SetNative(unknownPtr);

		RELEASE_VERSIONED_VARIABLES(DXGIDEVICE_VERSIONS, NUM_DXGIDEVICE_VERSIONS, mDevice)

		QUERY_INTERFACE_VERSIONED_VARIABLES(DXGIDEVICE_VERSIONS, NUM_DXGIDEVICE_VERSIONS, mDevice, devicePtr, /*no return*/)

		devicePtr->Release();
	}

}
}
