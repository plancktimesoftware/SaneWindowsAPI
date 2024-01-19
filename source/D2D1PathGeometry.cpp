
#include "D2D1PathGeometry.h"
#include "D2D1GeometrySink.h"

namespace SWApi
{
namespace D2D1
{
	auto PathGeometry::Open() -> WinResult<GeometrySink>
	{
		if (mPathGeometryV0 == nullptr) return Err(E_POINTER);

		ID2D1GeometrySink* d2d1GeometrySinkPtr = nullptr;
		auto hres = mPathGeometryV0->Open(&d2d1GeometrySinkPtr);
		if (hres != S_OK) return Err(hres);
		
		GeometrySink geometrySink;
		geometrySink.SetNative(d2d1GeometrySinkPtr);
		return geometrySink;
	}

	PathGeometry::PathGeometry(const PathGeometry& other)
		: Geometry(other)
		INITIALIZE_VERSIONED_VARIABLES(
			D2D1PATHGEOMETRY_VERSIONS, NUM_D2D1PATHGEOMETRY_VERSIONS, mPathGeometry, other.mPathGeometry)
	{
		ADDREF_TO_VERSIONED_VARIABLES(
			D2D1PATHGEOMETRY_VERSIONS, NUM_D2D1PATHGEOMETRY_VERSIONS, mPathGeometry)
	}

	PathGeometry::PathGeometry(PathGeometry&& other)
		: Geometry(std::forward<Geometry>(other))
		INITIALIZE_VERSIONED_VARIABLES(
			D2D1PATHGEOMETRY_VERSIONS, NUM_D2D1PATHGEOMETRY_VERSIONS, mPathGeometry, other.mPathGeometry)
	{
		ASSIGN_TO_VERSIONED_VARIABLES(
			D2D1PATHGEOMETRY_VERSIONS, NUM_D2D1PATHGEOMETRY_VERSIONS, other.mPathGeometry, nullptr)
	}


	PathGeometry::~PathGeometry()
	{
		RELEASE_VERSIONED_VARIABLES(
			D2D1PATHGEOMETRY_VERSIONS, NUM_D2D1PATHGEOMETRY_VERSIONS, mPathGeometry)
	}
}
}
