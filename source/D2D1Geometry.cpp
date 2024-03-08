
#include "D2D1Geometry.h"

namespace SWApi
{
namespace D2D1
{
	Geometry::Geometry(const Geometry& other)
		: Resource(other)
		, mID2D1Geometry{ other.mID2D1Geometry }
	{
		if (mID2D1Geometry) mID2D1Geometry->AddRef();
	}

	Geometry::Geometry(Geometry&& other) noexcept(true)
		: Resource(std::forward<Resource>(other))
		, mID2D1Geometry{ other.mID2D1Geometry }
	{
		other.mID2D1Geometry = nullptr;
	}

	Geometry::~Geometry()
	{
		if (mID2D1Geometry == nullptr) return;
		mID2D1Geometry->Release();
		mID2D1Geometry = nullptr;
	}

	void Geometry::SetNative(ID2D1Geometry* d2d1GeometryPtr)
	{
		if (mID2D1Geometry && mID2D1Geometry != d2d1GeometryPtr)
			mID2D1Geometry->Release();

		mID2D1Geometry = d2d1GeometryPtr;

		ID2D1Resource* d2d1ResourcePtr = nullptr;
		if (mID2D1Geometry == nullptr || S_OK != mID2D1Geometry->QueryInterface(&d2d1ResourcePtr))
			d2d1ResourcePtr = nullptr;
		Resource::SetNative(d2d1ResourcePtr);
	}
}
}
