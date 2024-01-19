#pragma once

#include <d2d1.h>
#include "D2D1Resource.h"

namespace SWApi
{
namespace D2D1
{
	class Brush : public Resource
	{
	public:
		Brush() = default;
		Brush(const Brush& other);
		Brush(Brush&& other);

		~Brush();

		auto GetNative() const -> ID2D1Brush* { return mID2D1Brush; }

		void SetNative(ID2D1Brush* d2d1BrushPtr);
	private:
		ID2D1Brush* mID2D1Brush = nullptr;
	};
}
}
