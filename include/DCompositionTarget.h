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

#if NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
		auto GetNative() const -> IDCompositionTarget* { return mIDCompositionTarget; }

		void SetNative(IDCompositionTarget* dCompTargetPtr);
	private:
		IDCompositionTarget* mIDCompositionTarget = nullptr;
#endif NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
	};
}
}
