#pragma once

#include "D2D1Properties.h"
#include <optional>

namespace SWApi
{
namespace D2D1
{
	class Image;

	class Effect : public Properties
	{
	public:
		void SetInput(UINT32 index, std::optional<Image> input, BOOL invalidate);

		Effect() = default;
		Effect(const Effect& other);
		Effect(Effect&& other) noexcept(true);

		~Effect();

		auto GetNative() const ->ID2D1Effect* { return mID2D1Effect; }
		void SetNative(ID2D1Effect* d2d1EffectPtr);
	private:
		ID2D1Effect* mID2D1Effect = nullptr;
	};
}
}
