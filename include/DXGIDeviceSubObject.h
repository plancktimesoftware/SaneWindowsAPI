#pragma once

#include "DXGIObject.h"

namespace SWApi
{
namespace DXGI
{
	class DeviceSubObject : public Object
	{
	public:
		DeviceSubObject() = default;
		DeviceSubObject(const DeviceSubObject& other);
		DeviceSubObject(DeviceSubObject&& other) noexcept(true);

		~DeviceSubObject();

		void SetNative(IDXGIDeviceSubObject* deviceSubObjectPtr);
	private:
		IDXGIDeviceSubObject* mIDXGIDeviceSubObject = nullptr;
	};
}
}

