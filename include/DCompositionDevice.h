#pragma once

#include <dcomp.h>
#include "WinResult.h"
#include "Wrapper.h"
#include "CommonMacros.h"

namespace SWApi
{
	class Window;

namespace DXGI
{
	class Device;
}

namespace DComposition
{
	class Target;
	class Visual;

#if NTDDI_VERSION >= 0x0A000000//NTDDI_WINTHRESHOLD
#define DCOMPDEVICE_VERSIONS (0, 2, 3)
#elif NTDDI_VERSION >= 0x06030000//NTDDI_WINBLUE
#define DCOMPDEVICE_VERSIONS (0, 2)
#elif NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
#define DCOMPDEVICE_VERSIONS (0)
#endif

	class Device : public Unknown
	{
	public:
		static auto Create(const DXGI::Device& dxgiDevice) -> WinResult<Device>;

		auto CreateTargetForHwnd(const Window& window, bool topmost) -> WinResult<Target>;

		auto CreateVisual() -> WinResult<Visual>;

		auto Commit() -> WinResult<void>;

		Device() = default;
		Device(const Device& other);
		Device(Device&& other) noexcept(true);

		~Device();

#if NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
		GETNATIVE_VERSIONED_VARIABLES(DCOMPDEVICE_VERSIONS, NUM(DCOMPDEVICE_VERSIONS), IDCompositionDevice, mDevice)

		template<typename DCompDeviceT>
		void SetNative(DCompDeviceT* dCompDevicePtr);
	private:
		DECLARE_VERSIONED_POINTER_VARIABLES(DCOMPDEVICE_VERSIONS, NUM(DCOMPDEVICE_VERSIONS), IDCompositionDevice, mDevice, nullptr)
#endif //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
	};

#if NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
	template<typename DCompDeviceT>
	inline void Device::SetNative(DCompDeviceT* dCompDevicePtr)
	{
		if (dCompDevicePtr == nullptr) return;

		IUnknown* unknownPtr = nullptr;
		auto hres = dCompDevicePtr->QueryInterface(&unknownPtr);
		if (hres != S_OK) return;
		Unknown::SetNative(unknownPtr);

		RELEASE_VERSIONED_VARIABLES(DCOMPDEVICE_VERSIONS, NUM(DCOMPDEVICE_VERSIONS), mDevice)

		QUERY_INTERFACE_VERSIONED_VARIABLES(DCOMPDEVICE_VERSIONS, NUM(DCOMPDEVICE_VERSIONS), mDevice, dCompDevicePtr, /*no return*/)

		dCompDevicePtr->Release();
	}
#endif //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
}
}
