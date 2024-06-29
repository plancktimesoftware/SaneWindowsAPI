#include "D2D1Factory.h"
#include "DXGIDevice.h"
#include "D2D1Device.h"
#include "D2D1PathGeometry.h"

#pragma comment(lib, "d2d1")

namespace SWApi
{
namespace D2D1
{
	auto Factory::Create(
		D2D1_FACTORY_TYPE factoryType,
		const std::optional<D2D1_FACTORY_OPTIONS>& factoryOptions)
		-> WinResult<Factory>
	{
		DECLARE_VERSIONED_POINTER_VARIABLES(D2D1FACTORY_VERSIONS, NUM(D2D1FACTORY_VERSIONS), ID2D1Factory, factory, nullptr);

		const D2D1_FACTORY_OPTIONS* pFactoryOptions = factoryOptions ? &(factoryOptions.value()) : nullptr;

		HRESULT hres = S_OK;
		Factory factory;

#define CREATE_FACTORY(index, _unused1, _unused2, _unused3, _unused4) \
		hres = D2D1CreateFactory( \
			factoryType, __uuidof(APPEND_IF_NOT_ZERO(ID2D1Factory,index)), \
			pFactoryOptions, reinterpret_cast<void**>(&factoryV##index)); \
		if (hres == S_OK && factoryV##index) \
		{ \
			factory.SetNative(factoryV##index); \
			return factory; \
		}

#define CREATE_VERSIONED_FACTORIES(versions, numVersions) \
		REVERSE_ITERATE_MACRO_FOR_TUPLE(CREATE_FACTORY, versions, numVersions, , , , )

		CREATE_VERSIONED_FACTORIES(D2D1FACTORY_VERSIONS, NUM(D2D1FACTORY_VERSIONS))
		
		return Err(hres);
	}

	auto Factory::CreateDevice(const DXGI::Device& dxgiDevice) -> WinResult<Device>
	{
		// Minimum version needed for CreateDevice.
		if (mFactoryV1 == nullptr) return Err(E_POINTER);

		auto dxgiDevicePtr = dxgiDevice.GetNative<IDXGIDevice>();
		if (dxgiDevicePtr == nullptr) return Err(E_POINTER);

		Device device;
		HRESULT hres = S_OK;
		DECLARE_VERSIONED_POINTER_VARIABLES(D2D1DEVICE_VERSIONS, NUM_D2D1DEVICE_VERSIONS, ID2D1Device, device, nullptr)

		if (mFactoryV7)
		{
			hres = mFactoryV7->CreateDevice(dxgiDevicePtr, &deviceV6);
			if (hres == S_OK && deviceV6)
			{
				device.SetNative(deviceV6);
				return device;
			}
		}

		if (mFactoryV6)
		{
			hres = mFactoryV6->CreateDevice(dxgiDevicePtr, &deviceV5);
			if (hres == S_OK && deviceV5)
			{
				device.SetNative(deviceV5);
				return device;
			}
		}

		if (mFactoryV5)
		{
			hres = mFactoryV5->CreateDevice(dxgiDevicePtr, &deviceV4);
			if (hres == S_OK && deviceV4)
			{
				device.SetNative(deviceV4);
				return device;
			}
		}

		if (mFactoryV4)
		{
			hres = mFactoryV4->CreateDevice(dxgiDevicePtr, &deviceV3);
			if (hres == S_OK && deviceV3)
			{
				device.SetNative(deviceV3);
				return device;
			}
		}

		if (mFactoryV3)
		{
			hres = mFactoryV3->CreateDevice(dxgiDevicePtr, &deviceV2);
			if (hres == S_OK && deviceV2)
			{
				device.SetNative(deviceV2);
				return device;
			}
		}

		if (mFactoryV2)
		{
			hres = mFactoryV2->CreateDevice(dxgiDevicePtr, &deviceV1);
			if (hres == S_OK && deviceV1)
			{
				device.SetNative(deviceV1);
				return device;
			}
		}

		if (mFactoryV1)
		{
			hres = mFactoryV1->CreateDevice(dxgiDevicePtr, &deviceV0);
			if (hres == S_OK && deviceV0)
			{
				device.SetNative(deviceV0);
				return device;
			}
		}

		return Err(hres);
	}

	auto Factory::CreatePathGeometry() -> WinResult<PathGeometry>
	{
		// Minimum version needed for CreatePathGeometry.
		if (mFactoryV0 == nullptr) return Err(E_POINTER);

		HRESULT hres = S_OK;
		PathGeometry pathGeometry;
		DECLARE_VERSIONED_POINTER_VARIABLES(
			D2D1PATHGEOMETRY_VERSIONS, NUM_D2D1PATHGEOMETRY_VERSIONS,
			ID2D1PathGeometry, pathGeometry, nullptr)

		if (mFactoryV1)
		{
			hres = mFactoryV1->CreatePathGeometry(&pathGeometryV1);
			if (hres == S_OK && pathGeometryV1)
			{
				pathGeometry.SetNative(pathGeometryV1);
				return pathGeometry;
			}
		}

		if (mFactoryV0)
		{
			hres = mFactoryV0->CreatePathGeometry(&pathGeometryV0);
			if (hres == S_OK && pathGeometryV0)
			{
				pathGeometry.SetNative(pathGeometryV0);
				return pathGeometry;
			}
		}

		return Err(hres);
	}

	Factory::Factory(const Factory& other)
		: Unknown(other)
		INITIALIZE_VERSIONED_VARIABLES(D2D1FACTORY_VERSIONS, NUM(D2D1FACTORY_VERSIONS), mFactory, other.mFactory)
	{
		ADDREF_TO_VERSIONED_VARIABLES(D2D1FACTORY_VERSIONS, NUM(D2D1FACTORY_VERSIONS), mFactory);
	}
	Factory::Factory(Factory&& other) noexcept(true)
		: Unknown(std::forward<Unknown>(other))
		INITIALIZE_VERSIONED_VARIABLES(D2D1FACTORY_VERSIONS, NUM(D2D1FACTORY_VERSIONS), mFactory, other.mFactory)
	{
		ASSIGN_TO_VERSIONED_VARIABLES(D2D1FACTORY_VERSIONS, NUM(D2D1FACTORY_VERSIONS), other.mFactory, nullptr)
	}

	Factory::~Factory()
	{
		RELEASE_VERSIONED_VARIABLES(D2D1FACTORY_VERSIONS, NUM(D2D1FACTORY_VERSIONS), mFactory)
	}
}
}
