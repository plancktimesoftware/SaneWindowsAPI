#include "DCompositionDevice.h"
#include "DXGIDevice.h"
#include "DCompositionTarget.h"
#include "DCompositionVisual.h"

#pragma comment(lib, "dcomp")

namespace SWApi
{
namespace DComposition
{
	auto Device::Create(const DXGI::Device& dxgiDevice) -> WinResult<Device>
	{
		auto dxgiDeviceV0 = dxgiDevice.GetNative<IDXGIDevice>();
		if (dxgiDeviceV0 == nullptr) return Err(E_POINTER);

		IDCompositionDevice* dCompDevicePtr = nullptr;
		auto hres = DCompositionCreateDevice(
			dxgiDeviceV0, __uuidof(IDCompositionDevice), reinterpret_cast<void**>(&dCompDevicePtr));
		if (hres != S_OK)
			return Err(hres);

		Device device;
		device.SetNative(dCompDevicePtr);
		return device;
	}

	auto Device::CreateTargetForHwnd(HWND hwnd, bool topmost) -> WinResult<Target>
	{
		if (mDeviceV0 == nullptr || hwnd == nullptr)
			return Err(E_POINTER);

		IDCompositionTarget* dCompTargetPtr = nullptr;
		auto hres = mDeviceV0->CreateTargetForHwnd(
			hwnd, topmost ? TRUE : FALSE, &dCompTargetPtr);
		if (hres != S_OK)
			return Err(hres);

		Target target;
		target.SetNative(dCompTargetPtr);
		return target;
	}

	auto Device::CreateVisual() -> WinResult<Visual>
	{
		if (mDeviceV0 == nullptr)
			return Err(E_POINTER);

		IDCompositionVisual* dCompVisualPtr = nullptr;
		auto hres = mDeviceV0->CreateVisual(&dCompVisualPtr);
		if (hres != S_OK)
			return Err(hres);

		Visual visual;
		visual.SetNative(dCompVisualPtr);
		return visual;
	}

	auto Device::Commit() -> WinResult<void>
	{
		if (mDeviceV0 == nullptr)
			return Err(E_POINTER);

		auto hres = mDeviceV0->Commit();
		return (hres == S_OK) ? WinResult<void>() : Err(hres);
	}

	Device::Device(const Device& other)
		: Unknown(other)
		INITIALIZE_VERSIONED_VARIABLES(DCOMPDEVICE_VERSIONS, NUM_DCOMPDEVICE_VERSIONS, mDevice, other.mDevice)
	{
		ADDREF_TO_VERSIONED_VARIABLES(DCOMPDEVICE_VERSIONS, NUM_DCOMPDEVICE_VERSIONS, mDevice);
	}
	Device::Device(Device&& other)
		: Unknown(std::forward<Unknown>(other))
		INITIALIZE_VERSIONED_VARIABLES(DCOMPDEVICE_VERSIONS, NUM_DCOMPDEVICE_VERSIONS, mDevice, other.mDevice)
	{
		ASSIGN_TO_VERSIONED_VARIABLES(DCOMPDEVICE_VERSIONS, NUM_DCOMPDEVICE_VERSIONS, other.mDevice, nullptr)
	}

	Device::~Device()
	{
		RELEASE_VERSIONED_VARIABLES(DCOMPDEVICE_VERSIONS, NUM_DCOMPDEVICE_VERSIONS, mDevice)
	}
}
}
