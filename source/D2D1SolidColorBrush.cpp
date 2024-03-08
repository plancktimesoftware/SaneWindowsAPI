#include "D2D1SolidColorBrush.h"

namespace SWApi
{
namespace D2D1
{
	SolidColorBrush::SolidColorBrush(const SolidColorBrush& other)
		: Brush(other)
		, mID2D1SolidColorBrush{ other.mID2D1SolidColorBrush }
	{
		if (mID2D1SolidColorBrush) mID2D1SolidColorBrush->AddRef();
	}
	SolidColorBrush::SolidColorBrush(SolidColorBrush&& other) noexcept(true)
		: Brush(std::forward<Brush>(other))
		, mID2D1SolidColorBrush{ other.mID2D1SolidColorBrush }
	{
		other.mID2D1SolidColorBrush = nullptr;
	}

	SolidColorBrush::~SolidColorBrush()
	{
		if (mID2D1SolidColorBrush == nullptr) return;
		mID2D1SolidColorBrush->Release();
		mID2D1SolidColorBrush = nullptr;
	}

	void SolidColorBrush::SetNative(ID2D1SolidColorBrush* d2d1BrushPtr)
	{
		if (mID2D1SolidColorBrush && mID2D1SolidColorBrush != d2d1BrushPtr)
			mID2D1SolidColorBrush->Release();

		mID2D1SolidColorBrush = d2d1BrushPtr;

		ID2D1Brush* baseBrushPtr = nullptr;
		if (mID2D1SolidColorBrush == nullptr
			|| S_OK != mID2D1SolidColorBrush->QueryInterface(&baseBrushPtr))
			baseBrushPtr = nullptr;
		Brush::SetNative(baseBrushPtr);
	}
}
}
