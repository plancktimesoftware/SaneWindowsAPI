#pragma once

#include "D2D1Resource.h"

namespace SWApi
{
namespace D2D1
{
	class Geometry : public Resource
	{
	public:
		Geometry() = default;
		Geometry(const Geometry& other);
		Geometry(Geometry&& other);

		~Geometry();

		auto GetNative() const -> ID2D1Geometry* { return mID2D1Geometry; }
		void SetNative(ID2D1Geometry* d2d1GeometryPtr);
	private:
		ID2D1Geometry* mID2D1Geometry = nullptr;
	};
}
}

