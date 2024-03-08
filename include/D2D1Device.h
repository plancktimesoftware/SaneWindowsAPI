#pragma once

#include <d2d1_3.h>
#include "WinResult.h"
#include "D2D1Resource.h"
#include "CommonMacros.h"

namespace SWApi
{
namespace D2D1
{

#define D2D1DEVICE_VERSIONS (0, 1, 2, 3, 4, 5, 6)
#define NUM_D2D1DEVICE_VERSIONS 7

	class DeviceContext;

	class Device : public Resource
	{
	public:

		auto CreateDeviceContext(
			D2D1_DEVICE_CONTEXT_OPTIONS options) -> WinResult<DeviceContext>;

		Device() = default;
		Device(const Device& other);
		Device(Device&& other) noexcept(true);

		~Device();

		GETNATIVE_VERSIONED_VARIABLES(D2D1DEVICE_VERSIONS, NUM_D2D1DEVICE_VERSIONS, ID2D1Device, mDevice)

		template<typename D2D1DeviceT>
		void SetNative(D2D1DeviceT* devicePtr);
	private:
		DECLARE_VERSIONED_POINTER_VARIABLES(D2D1DEVICE_VERSIONS, NUM_D2D1DEVICE_VERSIONS, ID2D1Device, mDevice, nullptr)
	};

	template<typename D2D1DeviceT>
	inline void Device::SetNative(D2D1DeviceT* devicePtr)
	{
		if (devicePtr == nullptr) return;

		ID2D1Resource* resourcePtr = nullptr;
		auto hres = devicePtr->QueryInterface(&resourcePtr);
		if (hres != S_OK) return;
		Resource::SetNative(resourcePtr);

		RELEASE_VERSIONED_VARIABLES(D2D1DEVICE_VERSIONS, NUM_D2D1DEVICE_VERSIONS, mDevice)

		QUERY_INTERFACE_VERSIONED_VARIABLES(D2D1DEVICE_VERSIONS, NUM_D2D1DEVICE_VERSIONS, mDevice, devicePtr, /*no return*/);

		devicePtr->Release();
	}
}
}
