#pragma once
#include <d2d1.h>
#include "Wrapper.h"

namespace SWApi
{
namespace D2D1
{
	class Resource : public Unknown
	{
	public:
		Resource() = default;
		Resource(const Resource& other);
		Resource(Resource&& other);

		~Resource();

		void SetNative(ID2D1Resource* d2d1ResourcePtr);
	private:
		ID2D1Resource* mID2D1Resource = nullptr;
	};
}
}
