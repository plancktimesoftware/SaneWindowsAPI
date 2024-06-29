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
		DECLARE_VERSIONED_POINTER_VARIABLES(D2D1DEVICE_VERSIONS, NUM(D2D1DEVICE_VERSIONS), ID2D1DeviceContext, deviceContext, nullptr)

#define CREATE_DEVICE_CONTEXT(index, ...) \
		if (mDeviceV##index) \
		{ \
			hres = mDeviceV##index->CreateDeviceContext(options, &deviceContextV##index); \
			if (hres == S_OK && deviceContextV##index) \
			{ \
				dc.SetNative(deviceContextV##index); \
				return dc; \
			} \
		}

#define CREATE_VERSIONED_DEVICE_CONTEXTS(versions, numVersions) \
		REVERSE_ITERATE_MACRO_FOR_TUPLE(CREATE_DEVICE_CONTEXT, versions, numVersions, , , ,)

		CREATE_VERSIONED_DEVICE_CONTEXTS(D2D1DEVICE_VERSIONS, NUM(D2D1DEVICE_VERSIONS))

		return Err(hres);
	}

	Device::Device(const Device& other)
		: Resource(other)
		INITIALIZE_VERSIONED_VARIABLES(D2D1DEVICE_VERSIONS, NUM(D2D1DEVICE_VERSIONS), mDevice, other.mDevice)
	{
		ADDREF_TO_VERSIONED_VARIABLES(D2D1DEVICE_VERSIONS, NUM(D2D1DEVICE_VERSIONS), mDevice)
	}

	Device::Device(Device&& other) noexcept(true)
		: Resource(std::forward<Resource>(other))
		INITIALIZE_VERSIONED_VARIABLES(D2D1DEVICE_VERSIONS, NUM(D2D1DEVICE_VERSIONS), mDevice, other.mDevice)
	{
		ASSIGN_TO_VERSIONED_VARIABLES(D2D1DEVICE_VERSIONS, NUM(D2D1DEVICE_VERSIONS), other.mDevice, nullptr)
	}

	Device::~Device()
	{
		RELEASE_VERSIONED_VARIABLES(D2D1DEVICE_VERSIONS, NUM(D2D1DEVICE_VERSIONS), mDevice)
	}
}
}
