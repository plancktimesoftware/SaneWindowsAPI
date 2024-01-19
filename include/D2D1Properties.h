#pragma once
#include <d2d1_1.h>
#include "Wrapper.h"
#include "WinResult.h"

namespace SWApi
{
namespace D2D1
{
	class Properties : public Unknown
	{
	public:
		template<typename T>
		auto SetValue(UINT32 index, const T& value) -> WinResult<void>;

		Properties() = default;
		Properties(const Properties& other);
		Properties(Properties&& other);

		~Properties();

		void SetNative(ID2D1Properties* d2d1PropertiesPtr);
	private:
		ID2D1Properties* mID2D1Properties = nullptr;
	};

	template<typename T>
	auto Properties::SetValue(UINT32 index, const T& value) -> WinResult<void>
	{
		if (mID2D1Properties == nullptr) return Err(E_POINTER);

		auto hres = mID2D1Properties->SetValue(index, value);
		if (hres != S_OK) return Err(hres);
		return WinResult<void>();
	}
}
}
