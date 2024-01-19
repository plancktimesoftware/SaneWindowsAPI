#include "D3D11Device.h"
#include "DXGIDevice.h"

#pragma comment(lib, "d3d11")

namespace SWApi
{
namespace D3D11
{
#if _HAS_CXX20
	auto Device::Create(
		IDXGIAdapter*                pAdapter,
		D3D_DRIVER_TYPE				 driverType,
		HMODULE						 hModule,
		UINT						 flags,
		std::span<D3D_FEATURE_LEVEL> featureLevels,
		UINT						 sdkVersion)
		-> WinResult<Device>
	{
		ID3D11Device* d3dDevicePtr = nullptr;
		Device device;
		auto result = D3D11CreateDevice(
			pAdapter, driverType, hModule, flags, featureLevels.data(), static_cast<UINT>(featureLevels.size()),
			sdkVersion, &d3dDevicePtr, &device.mFeatureLevel, &device.mDeviceContext);

		if (result != S_OK)
			return Err(result);
		
		device.SetNative(d3dDevicePtr);
		return device;
	}
#endif //#if _HAS_CXX20

	auto Device::Create(
		IDXGIAdapter* pAdapter, D3D_DRIVER_TYPE driverType, HMODULE hModule, UINT flags,
		const D3D_FEATURE_LEVEL* featureLevels, UINT numFeatureLevels, UINT sdkVersion)
		-> WinResult<Device>
	{
		ID3D11Device* d3dDevicePtr = nullptr;
		Device device;
		auto result = D3D11CreateDevice(
			pAdapter, driverType, hModule, flags, featureLevels, numFeatureLevels,
			sdkVersion, &d3dDevicePtr, &device.mFeatureLevel, &device.mDeviceContext);

		if (result != S_OK)
			return Err(result);

		device.SetNative(d3dDevicePtr);
		return device;
	}

	auto Device::AsDxgiDevice() -> WinResult<DXGI::Device>
	{
		if (mDeviceV0 == nullptr) return Err(E_POINTER);

		IDXGIDevice* dxgiDeviceV0 = nullptr;
		auto hres = mDeviceV0->QueryInterface(&dxgiDeviceV0);
		if (hres != S_OK) return Err(hres);

		DXGI::Device dxgiDevice;
		dxgiDevice.SetNative(dxgiDeviceV0);
		return dxgiDevice;
	}

	Device::Device(const Device& other)
		: Unknown(other)
		, mFeatureLevel(other.mFeatureLevel)
		, mDeviceContext(other.mDeviceContext)
		INITIALIZE_VERSIONED_VARIABLES(D3D11DEVICE_VERSIONS, NUM_D3D11DEVICE_VERSIONS, mDevice, other.mDevice)
	{
		if (mDeviceContext) mDeviceContext->AddRef();
		ADDREF_TO_VERSIONED_VARIABLES(D3D11DEVICE_VERSIONS, NUM_D3D11DEVICE_VERSIONS, mDevice)
	}

	Device::Device(Device&& other) noexcept
		: Unknown(std::forward<Unknown>(other))
		, mFeatureLevel(other.mFeatureLevel)
		, mDeviceContext(other.mDeviceContext)
		INITIALIZE_VERSIONED_VARIABLES(D3D11DEVICE_VERSIONS, NUM_D3D11DEVICE_VERSIONS, mDevice, other.mDevice)
	{
		other.mDeviceContext = nullptr;
		ASSIGN_TO_VERSIONED_VARIABLES(D3D11DEVICE_VERSIONS, NUM_D3D11DEVICE_VERSIONS, other.mDevice, nullptr)
	}

	Device::~Device()
	{
		if (mDeviceContext)
		{
			mDeviceContext->Release();
			mDeviceContext = nullptr;
		}
		RELEASE_VERSIONED_VARIABLES(D3D11DEVICE_VERSIONS, NUM_D3D11DEVICE_VERSIONS, mDevice)
	}

}
}
