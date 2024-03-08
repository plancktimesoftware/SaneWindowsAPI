#pragma once

#include <utility>
#include <d2d1_3.h>
#include "Wrapper.h"
#include "D2D1Brush.h"

namespace SWApi
{
namespace D2D1
{
	class SolidColorBrush : public Brush
	{
	public:
		SolidColorBrush() = default;
		SolidColorBrush(const SolidColorBrush& other);
		SolidColorBrush(SolidColorBrush&& other) noexcept(true);

		~SolidColorBrush();

		void SetNative(ID2D1SolidColorBrush* d2d1SolidBrushPtr);
	private:
		ID2D1SolidColorBrush* mID2D1SolidColorBrush = nullptr;
	};
}
}
