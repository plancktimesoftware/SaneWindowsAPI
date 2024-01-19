#include "DXGIFactory.h"
#include "DXGIDevice.h"
#include "DXGISwapChain.h"

#pragma comment(lib, "dxgi")

namespace SWApi
{
namespace DXGI
{

	auto Factory::Create(UINT flags) -> WinResult<Factory>
	{
		DECLARE_VERSIONED_POINTER_VARIABLES(DXGIFACTORY_VERSIONS, NUM_DXGIFACTORY_VERSIONS, IDXGIFactory, factory, nullptr)

		IDXGIFactory2* tempfactoryV2 = nullptr;
		auto hres = CreateDXGIFactory2(flags, __uuidof(IDXGIFactory2), reinterpret_cast<void**>(&tempfactoryV2));

		IDXGIFactory1* tempfactoryV1 = nullptr;
		if (hres != S_OK)
			hres = CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&tempfactoryV1));

		IDXGIFactory* tempfactoryV0 = nullptr;
		if (hres != S_OK)
			hres = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&tempfactoryV0));

		if (hres != S_OK)
			return Err(hres);

		Factory factory;
		if (tempfactoryV2)
			factory.SetNative(tempfactoryV2);
		else if (tempfactoryV1)
			factory.SetNative(tempfactoryV1);
		else
			factory.SetNative(tempfactoryV0);
		return factory;
	}

	Factory::Factory(const Factory& other)
		: Object(other)
		INITIALIZE_VERSIONED_VARIABLES(DXGIFACTORY_VERSIONS, NUM_DXGIFACTORY_VERSIONS, mFactory, other.mFactory)
	{
		ADDREF_TO_VERSIONED_VARIABLES(DXGIFACTORY_VERSIONS, NUM_DXGIFACTORY_VERSIONS, mFactory);
	}
	Factory::Factory(Factory&& other)
		: Object(std::forward<Object>(other))
		INITIALIZE_VERSIONED_VARIABLES(DXGIFACTORY_VERSIONS, NUM_DXGIFACTORY_VERSIONS, mFactory, other.mFactory)
	{
		ASSIGN_TO_VERSIONED_VARIABLES(DXGIFACTORY_VERSIONS, NUM_DXGIFACTORY_VERSIONS, other.mFactory, nullptr)
	}

	Factory::~Factory()
	{
		RELEASE_VERSIONED_VARIABLES(DXGIFACTORY_VERSIONS, NUM_DXGIFACTORY_VERSIONS, mFactory)
	}

	auto Factory::CreateSwapChainForComposition(
		const Device& device, const DXGI_SWAP_CHAIN_DESC1& desc, IDXGIOutput* pRestrictToOutput)
		-> WinResult<SwapChain>
	{
		if (mFactoryV2 == nullptr) return Err(E_POINTER);

		auto devicePtr = device.GetNative<IDXGIDevice>();
		if (devicePtr == nullptr) return Err(E_POINTER);

		IDXGISwapChain1* swapChainV1 = nullptr;
		auto hres = mFactoryV2->CreateSwapChainForComposition(
			devicePtr, &desc, pRestrictToOutput, &swapChainV1);
		if (hres != S_OK)
			return Err(hres);
		
		SwapChain swapChain;
		swapChain.SetNative(swapChainV1);
		return swapChain;
	}
}
}
