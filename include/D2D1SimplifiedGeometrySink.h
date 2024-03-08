#pragma once

#pragma once
#include <d2d1.h>
#include "Wrapper.h"
#include "WinResult.h"

namespace SWApi
{
namespace D2D1
{
	class SimplifiedGeometrySink : public Unknown
	{
	public:
		void BeginFigure(D2D1_POINT_2F startPoint, D2D1_FIGURE_BEGIN figureBegin);
		void EndFigure(D2D1_FIGURE_END figureEnd);

		auto Close() -> WinResult<void>;


		SimplifiedGeometrySink() = default;
		SimplifiedGeometrySink(const SimplifiedGeometrySink& other);
		SimplifiedGeometrySink(SimplifiedGeometrySink&& other) noexcept(true);

		~SimplifiedGeometrySink();

		void SetNative(ID2D1SimplifiedGeometrySink* d2d1SimplifiedGeometrySinkPtr);
	private:
		ID2D1SimplifiedGeometrySink* mID2D1SimplifiedGeometrySink = nullptr;
	};
}
}

