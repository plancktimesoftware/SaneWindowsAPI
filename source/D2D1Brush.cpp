#include "D2D1Brush.h"

namespace SWApi
{
namespace D2D1
{
	Brush::Brush(const Brush& other)
		: Resource(other)
		, mID2D1Brush{ other.mID2D1Brush }
	{
		if (mID2D1Brush) mID2D1Brush->AddRef();
	}
	Brush::Brush(Brush&& other) noexcept(true)
		: Resource(std::forward<Resource>(other))
		, mID2D1Brush{ other.mID2D1Brush }
	{
		other.mID2D1Brush = nullptr;
	}

	Brush::~Brush()
	{
		if (mID2D1Brush == nullptr) return;
		mID2D1Brush->Release();
		mID2D1Brush = nullptr;
	}

	void Brush::SetNative(ID2D1Brush* d2d1BrushPtr)
	{
		if (mID2D1Brush && mID2D1Brush != d2d1BrushPtr)
			mID2D1Brush->Release();

		mID2D1Brush = d2d1BrushPtr;

		ID2D1Resource* d2d1ResourcePtr = nullptr;
		if (mID2D1Brush == nullptr || S_OK != mID2D1Brush->QueryInterface(&d2d1ResourcePtr))
			d2d1ResourcePtr = nullptr;
		Resource::SetNative(d2d1ResourcePtr);
	}
}
}
