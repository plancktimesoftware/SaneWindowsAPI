#include "D2D1GeometrySink.h"

namespace SWApi
{
namespace D2D1
{
	void GeometrySink::AddArc(const D2D1_ARC_SEGMENT& arc)
	{
		if (mID2D1GeometrySink == nullptr) return;

		mID2D1GeometrySink->AddArc(arc);
	}

	void GeometrySink::AddBezier(const D2D1_BEZIER_SEGMENT& bezier)
	{
		if (mID2D1GeometrySink == nullptr) return;

		mID2D1GeometrySink->AddBezier(bezier);
	}

	void GeometrySink::AddLine(D2D1_POINT_2F point)
	{
		if (mID2D1GeometrySink == nullptr) return;

		mID2D1GeometrySink->AddLine(point);
	}

	GeometrySink::GeometrySink(const GeometrySink& other)
		: SimplifiedGeometrySink(other)
		, mID2D1GeometrySink{ other.mID2D1GeometrySink }
	{
		if (mID2D1GeometrySink) mID2D1GeometrySink->AddRef();
	}
	GeometrySink::GeometrySink(GeometrySink&& other) noexcept(true)
		: SimplifiedGeometrySink(std::forward<SimplifiedGeometrySink>(other))
		, mID2D1GeometrySink{ other.mID2D1GeometrySink }
	{
		other.mID2D1GeometrySink = nullptr;
	}

	GeometrySink::~GeometrySink()
	{
		if (mID2D1GeometrySink == nullptr) return;
		mID2D1GeometrySink->Release();
		mID2D1GeometrySink = nullptr;
	}

	void GeometrySink::SetNative(ID2D1GeometrySink* d2d1GeometrySinkPtr)
	{
		if (mID2D1GeometrySink && mID2D1GeometrySink != d2d1GeometrySinkPtr)
			mID2D1GeometrySink->Release();

		mID2D1GeometrySink = d2d1GeometrySinkPtr;

		ID2D1SimplifiedGeometrySink* d2d1SimplifiedGeometrySinkPtr = nullptr;
		if (mID2D1GeometrySink == nullptr || S_OK != mID2D1GeometrySink->QueryInterface(&d2d1SimplifiedGeometrySinkPtr))
			d2d1SimplifiedGeometrySinkPtr = nullptr;
		SimplifiedGeometrySink::SetNative(d2d1SimplifiedGeometrySinkPtr);
	}
}
}


