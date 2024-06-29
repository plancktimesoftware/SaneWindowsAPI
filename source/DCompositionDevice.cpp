#include "DCompositionDevice.h"
#include "DXGIDevice.h"
#include "DCompositionTarget.h"
#include "DCompositionVisual.h"
#include "Window.h"

#pragma comment(lib, "dcomp")

namespace SWApi
{
namespace DComposition
{

	auto Device::Create(const DXGI::Device& dxgiDevice) -> WinResult<Device>
	{
#if NTDDI_VERSION >= 0x06020000//NTDDI_WIN8

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

#else //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
		return Err(E_NOINTERFACE);
#endif //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
	}

	auto Device::CreateTargetForHwnd(const Window& window, bool topmost) -> WinResult<Target>
	{
#if NTDDI_VERSION >= 0x06020000//NTDDI_WIN8

		if (mDeviceV0 == nullptr || window.GetNative() == nullptr)
			return Err(E_POINTER);

		IDCompositionTarget* dCompTargetPtr = nullptr;
		auto hres = mDeviceV0->CreateTargetForHwnd(
			window.GetNative(), topmost ? TRUE : FALSE, &dCompTargetPtr);
		if (hres != S_OK)
			return Err(hres);

		Target target;
		target.SetNative(dCompTargetPtr);
		return target;

#else //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
return Err(E_NOINTERFACE);
#endif //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
	}

	auto Device::CreateVisual() -> WinResult<Visual>
	{
#if NTDDI_VERSION >= 0x06020000//NTDDI_WIN8

		if (mDeviceV0 == nullptr)
			return Err(E_POINTER);

		IDCompositionVisual* dCompVisualPtr = nullptr;
		auto hres = mDeviceV0->CreateVisual(&dCompVisualPtr);
		if (hres != S_OK)
			return Err(hres);

		Visual visual;
		visual.SetNative(dCompVisualPtr);
		return visual;

#else //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
return Err(E_NOINTERFACE);
#endif //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
	}

	auto Device::Commit() -> WinResult<void>
	{
#if NTDDI_VERSION >= 0x06020000//NTDDI_WIN8

		if (mDeviceV0 == nullptr)
			return Err(E_POINTER);

		auto hres = mDeviceV0->Commit();
		return (hres == S_OK) ? WinResult<void>() : Err(hres);

#else //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
return Err(E_NOINTERFACE);
#endif //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
	}

#if NTDDI_VERSION >= 0x06020000//NTDDI_WIN8

	Device::Device(const Device& other)
		: Unknown(other)
		INITIALIZE_VERSIONED_VARIABLES(DCOMPDEVICE_VERSIONS, NUM(DCOMPDEVICE_VERSIONS), mDevice, other.mDevice)
	{
		ADDREF_TO_VERSIONED_VARIABLES(DCOMPDEVICE_VERSIONS, NUM(DCOMPDEVICE_VERSIONS), mDevice);
	}

	Device::Device(Device&& other) noexcept(true)
		: Unknown(std::forward<Unknown>(other))
		INITIALIZE_VERSIONED_VARIABLES(DCOMPDEVICE_VERSIONS, NUM(DCOMPDEVICE_VERSIONS), mDevice, other.mDevice)
	{
		ASSIGN_TO_VERSIONED_VARIABLES(DCOMPDEVICE_VERSIONS, NUM(DCOMPDEVICE_VERSIONS), other.mDevice, nullptr)
	}

	Device::~Device()
	{
		RELEASE_VERSIONED_VARIABLES(DCOMPDEVICE_VERSIONS, NUM(DCOMPDEVICE_VERSIONS), mDevice)
	}

#else //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8

	Device::Device(const Device& other)
		: Unknown(other)
	{}

	Device::Device(Device&& other) noexcept(true)
		: Unknown(std::forward<Unknown>(other))
	{}

	Device::~Device()
	{}

#endif //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
}
}
