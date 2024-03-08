
#include "D2D1SimplifiedGeometrySink.h"

namespace SWApi
{
namespace D2D1
{
	void SimplifiedGeometrySink::BeginFigure(D2D1_POINT_2F startPoint, D2D1_FIGURE_BEGIN figureBegin)
	{
		if (mID2D1SimplifiedGeometrySink == nullptr) return;
		mID2D1SimplifiedGeometrySink->BeginFigure(startPoint, figureBegin);
	}

	void SimplifiedGeometrySink::EndFigure(D2D1_FIGURE_END figureEnd)
	{
		if (mID2D1SimplifiedGeometrySink == nullptr) return;
		mID2D1SimplifiedGeometrySink->EndFigure(figureEnd);
	}

	auto SimplifiedGeometrySink::Close() -> WinResult<void>
	{
		if (mID2D1SimplifiedGeometrySink == nullptr) return Err(E_POINTER);

		auto hres = mID2D1SimplifiedGeometrySink->Close();
		return hres == S_OK ? WinResult<void>() : Err(hres);
	}

	SimplifiedGeometrySink::SimplifiedGeometrySink(const SimplifiedGeometrySink& other)
		: Unknown(other)
		, mID2D1SimplifiedGeometrySink{ other.mID2D1SimplifiedGeometrySink }
	{
		if (mID2D1SimplifiedGeometrySink) mID2D1SimplifiedGeometrySink->AddRef();
	}

	SimplifiedGeometrySink::SimplifiedGeometrySink(SimplifiedGeometrySink&& other) noexcept(true)
		: Unknown(std::forward<Unknown>(other))
		, mID2D1SimplifiedGeometrySink{ other.mID2D1SimplifiedGeometrySink }
	{
		other.mID2D1SimplifiedGeometrySink = nullptr;
	}

	SimplifiedGeometrySink::~SimplifiedGeometrySink()
	{
		if (mID2D1SimplifiedGeometrySink == nullptr) return;
		mID2D1SimplifiedGeometrySink->Release();
		mID2D1SimplifiedGeometrySink = nullptr;
	}

	void SimplifiedGeometrySink::SetNative(ID2D1SimplifiedGeometrySink* d2d1SimplifiedGeometrySinkPtr)
	{
		if (mID2D1SimplifiedGeometrySink && mID2D1SimplifiedGeometrySink != d2d1SimplifiedGeometrySinkPtr)
			mID2D1SimplifiedGeometrySink->Release();

		mID2D1SimplifiedGeometrySink = d2d1SimplifiedGeometrySinkPtr;

		IUnknown* unknownNative = nullptr;
		if (mID2D1SimplifiedGeometrySink == nullptr || S_OK != mID2D1SimplifiedGeometrySink->QueryInterface(&unknownNative))
			unknownNative = nullptr;
		Unknown::SetNative(unknownNative);
	}

}
}
