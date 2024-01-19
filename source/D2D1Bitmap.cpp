#include "D2D1Bitmap.h"

namespace SWApi
{
namespace D2D1
{
	Bitmap::Bitmap(const Bitmap& other)
		: Image(other)
		INITIALIZE_VERSIONED_VARIABLES(D2D1BITMAP_VERSIONS, NUM_D2D1BITMAP_VERSIONS, mBitmap, other.mBitmap)
	{
		ADDREF_TO_VERSIONED_VARIABLES(D2D1BITMAP_VERSIONS, NUM_D2D1BITMAP_VERSIONS, mBitmap)
	}

	Bitmap::Bitmap(Bitmap&& other) noexcept
		: Image(std::forward<Image>(other))
		INITIALIZE_VERSIONED_VARIABLES(D2D1BITMAP_VERSIONS, NUM_D2D1BITMAP_VERSIONS, mBitmap, other.mBitmap)
	{
		ASSIGN_TO_VERSIONED_VARIABLES(D2D1BITMAP_VERSIONS, NUM_D2D1BITMAP_VERSIONS, other.mBitmap, nullptr)
	}

	Bitmap::~Bitmap()
	{
		RELEASE_VERSIONED_VARIABLES(D2D1BITMAP_VERSIONS, NUM_D2D1BITMAP_VERSIONS, mBitmap)
	}
}
}
