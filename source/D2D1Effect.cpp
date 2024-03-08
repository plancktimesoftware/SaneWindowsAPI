#include "D2D1Effect.h"
#include "D2D1Image.h"

namespace SWApi
{
namespace D2D1
{
	void Effect::SetInput(UINT32 index, std::optional<Image> input, BOOL invalidate)
	{
		if (mID2D1Effect == nullptr) return;

		mID2D1Effect->SetInput(index, input ? input->GetNative() : nullptr, invalidate);
	}

	Effect::Effect(const Effect& other)
		: Properties(other)
		, mID2D1Effect{ other.mID2D1Effect }
	{
		if (mID2D1Effect) mID2D1Effect->AddRef();
	}
	Effect::Effect(Effect&& other) noexcept(true)
		: Properties(std::forward<Properties>(other))
		, mID2D1Effect{ other.mID2D1Effect }
	{
		other.mID2D1Effect = nullptr;
	}

	Effect::~Effect()
	{
		if (mID2D1Effect == nullptr) return;
		mID2D1Effect->Release();
		mID2D1Effect = nullptr;
	}

	void Effect::SetNative(ID2D1Effect* d2d1EffectPtr)
	{
		if (mID2D1Effect && mID2D1Effect != d2d1EffectPtr)
			mID2D1Effect->Release();

		mID2D1Effect = d2d1EffectPtr;

		ID2D1Properties* d2d1PropertiesPtr = nullptr;
		if (mID2D1Effect == nullptr || S_OK != mID2D1Effect->QueryInterface(&d2d1PropertiesPtr))
			d2d1PropertiesPtr = nullptr;
		Properties::SetNative(d2d1PropertiesPtr);
	}

}
}

