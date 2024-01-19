#pragma once
#include "D2D1Resource.h"

namespace SWApi
{
namespace D2D1
{
	class RenderTarget : public Resource
	{
	public:
		auto GetSize() -> D2D1_SIZE_F;

		RenderTarget() = default;
		RenderTarget(const RenderTarget& other);
		RenderTarget(RenderTarget&& other);

		~RenderTarget();

		void SetNative(ID2D1RenderTarget* d2d1RenderTargetPtr);
	private:
		ID2D1RenderTarget* mID2D1RenderTarget = nullptr;
	};
}
}
