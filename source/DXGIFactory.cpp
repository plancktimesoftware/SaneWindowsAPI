#include "DXGIFactory.h"
#include "DXGIDevice.h"
#include "DXGISwapChain.h"
#include "DXGIOutput.h"

#pragma comment(lib, "dxgi")

namespace SWApi
{
namespace DXGI
{

	auto Factory::Create(UINT flags) -> WinResult<Factory>
	{
		DECLARE_VERSIONED_POINTER_VARIABLES(DXGIFACTORY_VERSIONS, NUM_DXGIFACTORY_VERSIONS, IDXGIFactory, factory, nullptr)

		auto hres = CreateDXGIFactory2(flags, __uuidof(IDXGIFactory2), reinterpret_cast<void**>(&factoryV2));

		if (hres != S_OK)
			hres = CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&factoryV1));

		if (hres != S_OK)
			hres = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&factoryV0));

		if (hres != S_OK)
			return Err(hres);

		Factory factory;
		if (factoryV2)
			factory.SetNative(factoryV2);
		else if (factoryV1)
			factory.SetNative(factoryV1);
		else
			factory.SetNative(factoryV0);
		return factory;
	}

	Factory::Factory(const Factory& other)
		: Object(other)
		INITIALIZE_VERSIONED_VARIABLES(DXGIFACTORY_VERSIONS, NUM_DXGIFACTORY_VERSIONS, mFactory, other.mFactory)
	{
		ADDREF_TO_VERSIONED_VARIABLES(DXGIFACTORY_VERSIONS, NUM_DXGIFACTORY_VERSIONS, mFactory);
	}
	Factory::Factory(Factory&& other) noexcept(true)
		: Object(std::forward<Object>(other))
		INITIALIZE_VERSIONED_VARIABLES(DXGIFACTORY_VERSIONS, NUM_DXGIFACTORY_VERSIONS, mFactory, other.mFactory)
	{
		ASSIGN_TO_VERSIONED_VARIABLES(DXGIFACTORY_VERSIONS, NUM_DXGIFACTORY_VERSIONS, other.mFactory, nullptr)
	}

	Factory::~Factory()
	{
		RELEASE_VERSIONED_VARIABLES(DXGIFACTORY_VERSIONS, NUM_DXGIFACTORY_VERSIONS, mFactory)
	}

	auto Factory::CreateSwapChain(const Device& device, const DXGI_SWAP_CHAIN_DESC& desc)
		-> WinResult<SwapChain>
	{
		if (mFactoryV0 == nullptr) return Err(E_POINTER);

		auto devicePtr = device.GetNative<IDXGIDevice>();
		if (devicePtr == nullptr) return Err(E_POINTER);

		IDXGISwapChain* swapChainV0 = nullptr;
		DXGI_SWAP_CHAIN_DESC tempDesc = desc;
		auto hres = mFactoryV2->CreateSwapChain(
			devicePtr, &tempDesc, &swapChainV0);
		if (hres != S_OK)
			return Err(hres);

		SwapChain swapChain;
		swapChain.SetNative(swapChainV0);
		return swapChain;
	}

	auto Factory::CreateSwapChainForComposition(
		const Device& device, const DXGI_SWAP_CHAIN_DESC1& desc,
		std::optional<Output> restrictToOutput)
		-> WinResult<SwapChain>
	{
		if (mFactoryV2 == nullptr) return Err(E_POINTER);

		auto devicePtr = device.GetNative<IDXGIDevice>();
		if (devicePtr == nullptr) return Err(E_POINTER);

		IDXGIOutput* pRestrictToOutput =
			restrictToOutput ? restrictToOutput->GetNative<IDXGIOutput>() : nullptr;

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
