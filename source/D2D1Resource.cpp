#include "D2D1Resource.h"

namespace SWApi
{
namespace D2D1
{
	Resource::Resource(const Resource& other)
		: Unknown(other)
		, mID2D1Resource{ other.mID2D1Resource }
	{
		if (mID2D1Resource) mID2D1Resource->AddRef();
	}
	Resource::Resource(Resource&& other)
		: Unknown(std::forward<Unknown>(other))
		, mID2D1Resource{ other.mID2D1Resource }
	{
		other.mID2D1Resource = nullptr;
	}

	Resource::~Resource()
	{
		if (mID2D1Resource == nullptr) return;
		mID2D1Resource->Release();
		mID2D1Resource = nullptr;
	}

	void Resource::SetNative(ID2D1Resource* d2d1ResourcePtr)
	{
		if (mID2D1Resource && mID2D1Resource != d2d1ResourcePtr)
			mID2D1Resource->Release();

		mID2D1Resource = d2d1ResourcePtr;

		IUnknown* unknownNative = nullptr;
		if (mID2D1Resource == nullptr || S_OK != mID2D1Resource->QueryInterface(&unknownNative))
			unknownNative = nullptr;
		Unknown::SetNative(unknownNative);
	}
}
}

