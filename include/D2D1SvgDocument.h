#pragma once

#include "D2D1Resource.h"
#include <d2d1svg.h>

namespace SWApi
{
namespace D2D1
{
	class SvgDocument : public Resource
	{
	public:
		SvgDocument() = default;
		SvgDocument(const SvgDocument& other);
		SvgDocument(SvgDocument&& other) noexcept(true);

		~SvgDocument();

		auto GetNative() const -> ID2D1SvgDocument* { return mID2D1SvgDocument; }
		void SetNative(ID2D1SvgDocument* d2d1SvgDocumentPtr);
	private:
		ID2D1SvgDocument* mID2D1SvgDocument = nullptr;
	};
}
}
