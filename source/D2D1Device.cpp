#include "D2D1Device.h"
#include "D2D1DeviceContext.h"

namespace SWApi
{
namespace D2D1
{
	auto Device::CreateDeviceContext(
		D2D1_DEVICE_CONTEXT_OPTIONS options) -> WinResult<DeviceContext>
	{
		if (mDeviceV0 == nullptr) return Err(E_POINTER);

		DeviceContext dc;
		HRESULT hres = S_OK;
		DECLARE_VERSIONED_POINTER_VARIABLES(D2D1DEVICE_VERSIONS, NUM_D2D1DEVICE_VERSIONS, ID2D1DeviceContext, deviceContext, nullptr)

		if (mDeviceV6)
		{
			hres = mDeviceV6->CreateDeviceContext(options, &deviceContextV6);
			if (hres == S_OK && deviceContextV6)
			{
				dc.SetNative(deviceContextV6);
				return dc;
			}
		}

		if (mDeviceV5)
		{
			hres = mDeviceV5->CreateDeviceContext(options, &deviceContextV5);
			if (hres == S_OK && deviceContextV5)
			{
				dc.SetNative(deviceContextV5);
				return dc;
			}
		}

		if (mDeviceV4)
		{
			hres = mDeviceV4->CreateDeviceContext(options, &deviceContextV4);
			if (hres == S_OK && deviceContextV4)
			{
				dc.SetNative(deviceContextV4);
				return dc;
			}
		}

		if (mDeviceV3)
		{
			hres = mDeviceV3->CreateDeviceContext(options, &deviceContextV3);
			if (hres == S_OK && deviceContextV3)
			{
				dc.SetNative(deviceContextV3);
				return dc;
			}
		}

		if (mDeviceV2)
		{
			hres = mDeviceV2->CreateDeviceContext(options, &deviceContextV2);
			if (hres == S_OK && deviceContextV2)
			{
				dc.SetNative(deviceContextV2);
				return dc;
			}
		}

		if (mDeviceV1)
		{
			hres = mDeviceV1->CreateDeviceContext(options, &deviceContextV1);
			if (hres == S_OK && deviceContextV1)
			{
				dc.SetNative(deviceContextV1);
				return dc;
			}
		}

		if (mDeviceV0)
		{
			hres = mDeviceV0->CreateDeviceContext(options, &deviceContextV0);
			if (hres == S_OK && deviceContextV0)
			{
				dc.SetNative(deviceContextV0);
				return dc;
			}
		}
		
		return Err(hres);
	}

	Device::Device(const Device& other)
		: Resource(other)
		INITIALIZE_VERSIONED_VARIABLES(D2D1DEVICE_VERSIONS, NUM_D2D1DEVICE_VERSIONS, mDevice, other.mDevice)
	{
		ADDREF_TO_VERSIONED_VARIABLES(D2D1DEVICE_VERSIONS, NUM_D2D1DEVICE_VERSIONS, mDevice)
	}

	Device::Device(Device&& other) noexcept(true)
		: Resource(std::forward<Resource>(other))
		INITIALIZE_VERSIONED_VARIABLES(D2D1DEVICE_VERSIONS, NUM_D2D1DEVICE_VERSIONS, mDevice, other.mDevice)
	{
		ASSIGN_TO_VERSIONED_VARIABLES(D2D1DEVICE_VERSIONS, NUM_D2D1DEVICE_VERSIONS, other.mDevice, nullptr)
	}

	Device::~Device()
	{
		RELEASE_VERSIONED_VARIABLES(D2D1DEVICE_VERSIONS, NUM_D2D1DEVICE_VERSIONS, mDevice)
	}
}
}
