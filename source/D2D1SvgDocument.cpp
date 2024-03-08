
#include "D2D1SvgDocument.h"

namespace SWApi
{
namespace D2D1
{
	SvgDocument::SvgDocument(const SvgDocument& other)
		: Resource(other)
		, mID2D1SvgDocument(other.mID2D1SvgDocument)
	{
		if (mID2D1SvgDocument)
			mID2D1SvgDocument->AddRef();
	}

	SvgDocument::SvgDocument(SvgDocument&& other) noexcept(true)
		: Resource(std::forward<Resource>(other))
		, mID2D1SvgDocument(other.mID2D1SvgDocument)
	{
		other.mID2D1SvgDocument = nullptr;
	}

	SvgDocument::~SvgDocument()
	{
		if (mID2D1SvgDocument == nullptr) return;

		mID2D1SvgDocument->Release();
		mID2D1SvgDocument = nullptr;
	}

	void SvgDocument::SetNative(ID2D1SvgDocument* d2d1SvgDocumentPtr)
	{
		if (mID2D1SvgDocument && mID2D1SvgDocument != d2d1SvgDocumentPtr)
			mID2D1SvgDocument->Release();

		mID2D1SvgDocument = d2d1SvgDocumentPtr;

		ID2D1Resource* d2d1ResourcePtr = nullptr;
		if (mID2D1SvgDocument == nullptr
			|| S_OK != mID2D1SvgDocument->QueryInterface(&d2d1ResourcePtr))
			d2d1ResourcePtr = nullptr;
		Resource::SetNative(d2d1ResourcePtr);
	}
}
}
