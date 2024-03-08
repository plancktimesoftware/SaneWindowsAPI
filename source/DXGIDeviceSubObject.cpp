#include "DXGIDeviceSubObject.h"

namespace SWApi
{
namespace DXGI
{
	DeviceSubObject::DeviceSubObject(const DeviceSubObject& other)
		: Object(other)
		, mIDXGIDeviceSubObject(other.mIDXGIDeviceSubObject)
	{
		if (mIDXGIDeviceSubObject) mIDXGIDeviceSubObject->AddRef();
	}

	DeviceSubObject::DeviceSubObject(DeviceSubObject&& other) noexcept(true)
		: Object(std::forward<Object>(other))
		, mIDXGIDeviceSubObject(other.mIDXGIDeviceSubObject)
	{
		other.mIDXGIDeviceSubObject = nullptr;
	}

	DeviceSubObject::~DeviceSubObject()
	{
		if (mIDXGIDeviceSubObject)
		{
			mIDXGIDeviceSubObject->Release();
			mIDXGIDeviceSubObject = nullptr;
		}
	}

	void DeviceSubObject::SetNative(IDXGIDeviceSubObject* deviceSubObjectPtr)
	{
		if (mIDXGIDeviceSubObject && mIDXGIDeviceSubObject != deviceSubObjectPtr)
			mIDXGIDeviceSubObject->Release();
		mIDXGIDeviceSubObject = deviceSubObjectPtr;

		IDXGIObject* dxgiObjectPtr = nullptr;
		if (mIDXGIDeviceSubObject == nullptr
			|| S_OK != mIDXGIDeviceSubObject->QueryInterface(&dxgiObjectPtr))
			dxgiObjectPtr = nullptr;
		Object::SetNative(dxgiObjectPtr);
	}
}
}
