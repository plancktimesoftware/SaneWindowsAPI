#include "DCompositionTarget.h"
#include "DCompositionVisual.h"

namespace SWApi
{
namespace DComposition
{
	auto Target::SetRoot(const Visual& rootVisual) -> WinResult<void>
	{
#if NTDDI_VERSION >= 0x06020000//NTDDI_WIN8

		if (mIDCompositionTarget == nullptr) return Err(E_POINTER);

		auto dCompVisualV0 = rootVisual.GetNative<IDCompositionVisual>();
		if (dCompVisualV0 == nullptr) return Err(E_POINTER);

		auto hres = mIDCompositionTarget->SetRoot(dCompVisualV0);
		return (hres == S_OK) ? WinResult<void>() : Err(hres);

#else //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
		return Err(E_NOINTERFACE);
#endif //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
	}

#if NTDDI_VERSION >= 0x06020000//NTDDI_WIN8

	Target::Target(const Target& other)
		: Unknown(other)
		, mIDCompositionTarget{ other.mIDCompositionTarget }
	{
		if (mIDCompositionTarget) mIDCompositionTarget->AddRef();
	}

	Target::Target(Target&& other) noexcept(true)
		: Unknown(std::forward<Unknown>(other))
		, mIDCompositionTarget{ other.mIDCompositionTarget }
	{
		other.mIDCompositionTarget = nullptr;
	}

	Target::~Target()
	{
		if (mIDCompositionTarget == nullptr) return;
		mIDCompositionTarget->Release();
		mIDCompositionTarget = nullptr;
	}

	void Target::SetNative(IDCompositionTarget* dCompTargetPtr)
	{
		if (mIDCompositionTarget && mIDCompositionTarget != dCompTargetPtr)
			mIDCompositionTarget->Release();

		mIDCompositionTarget = dCompTargetPtr;

		IUnknown* unknownPtr = nullptr;
		if (mIDCompositionTarget == nullptr
			|| S_OK != mIDCompositionTarget->QueryInterface(&unknownPtr))
			unknownPtr = nullptr;
		Unknown::SetNative(unknownPtr);
	}

#else //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8

	Target::Target(const Target& other)
		: Unknown(other)
	{}

	Target::Target(Target&& other) noexcept(true)
		: Unknown(std::forward<Unknown>(other))
	{}

	Target::~Target()
	{}

#endif //NTDDI_VERSION >= 0x06020000//NTDDI_WIN8
}
}
