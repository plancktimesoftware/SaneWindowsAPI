#pragma once

#include <dcomp.h>
#include "WinResult.h"
#include "Wrapper.h"

namespace SWApi
{
namespace DComposition
{
	class Visual;

	class Target : public Unknown
	{
	public:
		auto SetRoot(const Visual& rootVisual) -> WinResult<void>;

		Target() = default;
		Target(const Target& other);
		Target(Target&& other) noexcept(true);

		~Target();

		auto GetNative() const -> IDCompositionTarget* { return mIDCompositionTarget; }

		void SetNative(IDCompositionTarget* dCompTargetPtr);
	private:
		IDCompositionTarget* mIDCompositionTarget = nullptr;
	};
}
}
