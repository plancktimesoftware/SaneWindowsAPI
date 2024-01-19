#pragma once

#include <d2d1.h>
#include "D2D1Resource.h"

namespace SWApi
{
namespace D2D1
{
	class Image : public Resource
	{
	public:
		Image() = default;
		Image(const Image& other);
		Image(Image&& other);

		~Image();

		auto GetNative() const -> ID2D1Image* { return mID2D1Image; }

		void SetNative(ID2D1Image* d2d1ImagePtr);
	private:
		ID2D1Image* mID2D1Image = nullptr;
	};
}
}
