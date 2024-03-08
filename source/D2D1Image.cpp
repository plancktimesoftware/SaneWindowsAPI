#include "D2D1Image.h"

namespace SWApi
{
namespace D2D1
{
	Image::Image(const Image& other)
		: Resource(other)
		, mID2D1Image{ other.mID2D1Image }
	{
		if (mID2D1Image) mID2D1Image->AddRef();
	}
	Image::Image(Image&& other) noexcept(true)
		: Resource(std::forward<Resource>(other))
		, mID2D1Image{ other.mID2D1Image }
	{
		other.mID2D1Image = nullptr;
	}

	Image::~Image()
	{
		if (mID2D1Image == nullptr) return;
		mID2D1Image->Release();
		mID2D1Image = nullptr;
	}

	void Image::SetNative(ID2D1Image* d2d1ImagePtr)
	{
		if (mID2D1Image && mID2D1Image != d2d1ImagePtr)
			mID2D1Image->Release();

		mID2D1Image = d2d1ImagePtr;

		ID2D1Resource* d2d1ResourcePtr = nullptr;
		if (mID2D1Image == nullptr || S_OK != mID2D1Image->QueryInterface(&d2d1ResourcePtr))
			d2d1ResourcePtr = nullptr;
		Resource::SetNative(d2d1ResourcePtr);
	}
}
}

