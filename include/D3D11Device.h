
#pragma once

#if _HAS_CXX20
#include <span>
#endif //#if _HAS_CXX20
#include <d3d11_4.h>
#include "WinResult.h"
#include "Wrapper.h"
#include "CommonMacros.h"

namespace SWApi
{

namespace DXGI
{
	class Device;
}

namespace D3D11
{
#define D3D11DEVICE_VERSIONS (0, 1, 2, 3, 4, 5)
#define NUM_D3D11DEVICE_VERSIONS 6

	class Device : public Unknown
	{
	public:
#if _HAS_CXX20
		static auto Create(
			IDXGIAdapter* pAdapter,
			D3D_DRIVER_TYPE				 driverType,
			HMODULE						 hModule,
			UINT						 flags,
			std::span<D3D_FEATURE_LEVEL> featureLevels,
			UINT						 sdkVersion)
			-> WinResult<Device>;
#endif //#if _HAS_CXX20

		static auto Create(
			IDXGIAdapter* pAdapter,
			D3D_DRIVER_TYPE			 driverType,
			HMODULE					 hModule,
			UINT					 flags,
			const D3D_FEATURE_LEVEL* featureLevels,
			UINT					 numFeatureLevels,
			UINT					 sdkVersion)
			-> WinResult<Device>;

		auto AsDxgiDevice() -> WinResult<DXGI::Device>;

		Device() = default;
		Device(const Device& other);
		Device(Device&& other) noexcept(true);

		~Device();

		GETNATIVE_VERSIONED_VARIABLES(D3D11DEVICE_VERSIONS, NUM_D3D11DEVICE_VERSIONS, ID3D11Device, mDevice)

			template<typename D3D11DeviceT>
		void SetNative(D3D11DeviceT* devicePtr);
	private:
		DECLARE_VERSIONED_POINTER_VARIABLES(D3D11DEVICE_VERSIONS, NUM_D3D11DEVICE_VERSIONS, ID3D11Device, mDevice, nullptr)
		D3D_FEATURE_LEVEL mFeatureLevel = D3D_FEATURE_LEVEL_1_0_CORE;
		ID3D11DeviceContext* mDeviceContext = nullptr;
	};

	template<typename D3D11DeviceT>
	inline void Device::SetNative(D3D11DeviceT* devicePtr)
	{
		if (devicePtr == nullptr) return;

		IUnknown* unknownPtr = nullptr;
		auto hres = devicePtr->QueryInterface(&unknownPtr);
		if (hres != S_OK) return;
		Unknown::SetNative(unknownPtr);

		RELEASE_VERSIONED_VARIABLES(D3D11DEVICE_VERSIONS, NUM_D3D11DEVICE_VERSIONS, mDevice)

			QUERY_INTERFACE_VERSIONED_VARIABLES(D3D11DEVICE_VERSIONS, NUM_D3D11DEVICE_VERSIONS, mDevice, devicePtr, /*no return*/);

		devicePtr->Release();
	}
}
}

