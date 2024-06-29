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

#define CREATE_FACTORY(index, ...) \
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
		DECLARE_VERSIONED_POINTER_VARIABLES(D2D1DEVICE_VERSIONS, NUM(D2D1DEVICE_VERSIONS), ID2D1Device, device, nullptr)

#define CREATE_DEVICE_FROM_FACTORY(index, ...) \
		if (CAT(mFactoryV, INCREMENT(index))) \
		{ \
			hres = CAT(mFactoryV, INCREMENT(index))->CreateDevice(dxgiDevicePtr, &deviceV##index); \
			if (hres == S_OK && deviceV##index) \
			{ \
				device.SetNative(deviceV##index); \
				return device; \
			} \
		}

#define CREATE_VERSIONED_DEVICES(versions, numVersions) \
		REVERSE_ITERATE_MACRO_FOR_TUPLE(CREATE_DEVICE_FROM_FACTORY, versions, numVersions, , , , )

		CREATE_VERSIONED_DEVICES(D2D1DEVICE_VERSIONS, NUM(D2D1DEVICE_VERSIONS))

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
