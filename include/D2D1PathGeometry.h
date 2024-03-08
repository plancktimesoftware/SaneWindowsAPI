#pragma once

#include <d2d1_1.h>
#include "D2D1Geometry.h"
#include "CommonMacros.h"
#include "WinResult.h"

namespace SWApi
{
namespace D2D1
{
	class GeometrySink;

#define D2D1PATHGEOMETRY_VERSIONS (0, 1)
#define NUM_D2D1PATHGEOMETRY_VERSIONS 2

	class PathGeometry : public Geometry
	{
	public:
		auto Open() -> WinResult<GeometrySink>;

		PathGeometry() = default;
		PathGeometry(const PathGeometry& other);
		PathGeometry(PathGeometry&& other) noexcept(true);

		~PathGeometry();

		template<typename D2D1PathGeometryT>
		void SetNative(D2D1PathGeometryT* d2d1PathGeometryPtr);
	private:
		DECLARE_VERSIONED_POINTER_VARIABLES(
			D2D1PATHGEOMETRY_VERSIONS, NUM_D2D1PATHGEOMETRY_VERSIONS,
			ID2D1PathGeometry, mPathGeometry, nullptr)
	};

	template<typename D2D1PathGeometryT>
	inline void PathGeometry::SetNative(D2D1PathGeometryT* d2d1PathGeometryPtr)
	{
		ID2D1Geometry* d2d1GeometryPtr = nullptr;
		if (d2d1PathGeometryPtr == nullptr || S_OK != d2d1PathGeometryPtr->QueryInterface(&d2d1GeometryPtr))
			d2d1GeometryPtr = nullptr;
		Geometry::SetNative(d2d1GeometryPtr);

		RELEASE_VERSIONED_VARIABLES(
			D2D1PATHGEOMETRY_VERSIONS, NUM_D2D1PATHGEOMETRY_VERSIONS, mPathGeometry)

		if (d2d1PathGeometryPtr == nullptr) return;
		HRESULT hres = S_OK;
		QUERY_INTERFACE_VERSIONED_VARIABLES(
			D2D1PATHGEOMETRY_VERSIONS, NUM_D2D1PATHGEOMETRY_VERSIONS, mPathGeometry,
			d2d1PathGeometryPtr, /*no return*/);
		d2d1PathGeometryPtr->Release();
	}
}
}
