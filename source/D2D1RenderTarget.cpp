#include "D2D1RenderTarget.h"

namespace SWApi
{
namespace D2D1
{
	auto RenderTarget::GetSize() -> D2D1_SIZE_F
	{
		if (mID2D1RenderTarget)
			return mID2D1RenderTarget->GetSize();
		
		return {};
	}

	RenderTarget::RenderTarget(const RenderTarget& other)
		: Resource(other)
		, mID2D1RenderTarget{ other.mID2D1RenderTarget }
	{
		if (mID2D1RenderTarget) mID2D1RenderTarget->AddRef();
	}
	RenderTarget::RenderTarget(RenderTarget&& other) noexcept(true)
		: Resource(std::forward<Resource>(other))
		, mID2D1RenderTarget{ other.mID2D1RenderTarget }
	{
		other.mID2D1RenderTarget = nullptr;
	}

	RenderTarget::~RenderTarget()
	{
		if (mID2D1RenderTarget == nullptr) return;
		mID2D1RenderTarget->Release();
		mID2D1RenderTarget = nullptr;
	}

	void RenderTarget::SetNative(ID2D1RenderTarget* d2d1RenderTargetPtr)
	{
		if (mID2D1RenderTarget && mID2D1RenderTarget != d2d1RenderTargetPtr)
			mID2D1RenderTarget->Release();

		mID2D1RenderTarget = d2d1RenderTargetPtr;

		ID2D1Resource* d2d1ResourcePtr = nullptr;
		if (mID2D1RenderTarget == nullptr || S_OK != mID2D1RenderTarget->QueryInterface(&d2d1ResourcePtr))
			d2d1ResourcePtr = nullptr;
		Resource::SetNative(d2d1ResourcePtr);
	}

}
}
