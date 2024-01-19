#pragma once

#include "D2D1SimplifiedGeometrySink.h"

namespace SWApi
{
namespace D2D1
{
	class GeometrySink : public SimplifiedGeometrySink
	{
	public:
		void AddArc(const D2D1_ARC_SEGMENT& arc);
		void AddBezier(const D2D1_BEZIER_SEGMENT& bezier);
		void AddLine(D2D1_POINT_2F point);

		GeometrySink() = default;
		GeometrySink(const GeometrySink& other);
		GeometrySink(GeometrySink&& other);

		~GeometrySink();

		void SetNative(ID2D1GeometrySink* d2d1GeometrySinkPtr);
	private:
		ID2D1GeometrySink* mID2D1GeometrySink = nullptr;
	};
}
}
