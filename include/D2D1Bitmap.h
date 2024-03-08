#pragma once

#include <utility>
#include <d2d1_3.h>
#include "Wrapper.h"
#include "D2D1Image.h"
#include "CommonMacros.h"

namespace SWApi
{
namespace D2D1
{
#define D2D1BITMAP_VERSIONS (0, 1)
#define NUM_D2D1BITMAP_VERSIONS 2

	class Bitmap : public Image
	{
	public:
		Bitmap() = default;
		Bitmap(const Bitmap& other);
		Bitmap(Bitmap&& other) noexcept(true);

		~Bitmap();

		GETNATIVE_VERSIONED_VARIABLES(D2D1BITMAP_VERSIONS, NUM_D2D1BITMAP_VERSIONS, ID2D1Bitmap, mBitmap)

		template<typename D2D1BitmapT>
		void SetNative(D2D1BitmapT* BitmapPtr);
	private:
		DECLARE_VERSIONED_POINTER_VARIABLES(D2D1BITMAP_VERSIONS, NUM_D2D1BITMAP_VERSIONS, ID2D1Bitmap, mBitmap, nullptr)
	};

	template<typename D2D1BitmapT>
	inline void Bitmap::SetNative(D2D1BitmapT* bitmapPtr)
	{
		if (bitmapPtr == nullptr) return;

		ID2D1Image* imagePtr = nullptr;
		auto hres = bitmapPtr->QueryInterface(&imagePtr);
		if (hres != S_OK) return;
		Image::SetNative(imagePtr);

		RELEASE_VERSIONED_VARIABLES(D2D1BITMAP_VERSIONS, NUM_D2D1BITMAP_VERSIONS, mBitmap)

		QUERY_INTERFACE_VERSIONED_VARIABLES(D2D1BITMAP_VERSIONS, NUM_D2D1BITMAP_VERSIONS, mBitmap, bitmapPtr, /*no return*/);

		bitmapPtr->Release();
	}
}
}
