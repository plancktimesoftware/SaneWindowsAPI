#include "D2D1Properties.h"

namespace SWApi
{
namespace D2D1
{
	Properties::Properties(const Properties& other)
		: Unknown(other)
		, mID2D1Properties{ other.mID2D1Properties }
	{
		if (mID2D1Properties) mID2D1Properties->AddRef();
	}
	Properties::Properties(Properties&& other) noexcept(true)
		: Unknown(std::forward<Unknown>(other))
		, mID2D1Properties{ other.mID2D1Properties }
	{
		other.mID2D1Properties = nullptr;
	}

	Properties::~Properties()
	{
		if (mID2D1Properties == nullptr) return;
		mID2D1Properties->Release();
		mID2D1Properties = nullptr;
	}

	void Properties::SetNative(ID2D1Properties* d2d1PropertiesPtr)
	{
		if (mID2D1Properties && mID2D1Properties != d2d1PropertiesPtr)
			mID2D1Properties->Release();

		mID2D1Properties = d2d1PropertiesPtr;

		IUnknown* unknownNative = nullptr;
		if (mID2D1Properties == nullptr || S_OK != mID2D1Properties->QueryInterface(&unknownNative))
			unknownNative = nullptr;
		Unknown::SetNative(unknownNative);
	}
}
}

