#pragma once

#include <utility>
#include <unknwn.h>

namespace SWApi
{
class Unknown
{
public:
	Unknown() = default;
	Unknown(const Unknown& other)
		: mIUnknown{ other.mIUnknown }
	{
		if (mIUnknown) mIUnknown->AddRef();
	}
	Unknown(Unknown&& other) noexcept
		: mIUnknown{ other.mIUnknown }
	{
		other.mIUnknown = nullptr;
	}

	virtual ~Unknown()
	{
		if (mIUnknown == nullptr) return;
		mIUnknown->Release();
		mIUnknown = nullptr;
	}

	template<typename T>
	auto GetNative() const -> T* { return nullptr; }

	template<>
	auto GetNative<IUnknown>() const -> IUnknown* { return mIUnknown; }

	void SetNative(IUnknown* unknownPtr)
	{
		if (mIUnknown && mIUnknown != unknownPtr)
			mIUnknown->Release();
		mIUnknown = unknownPtr;
	}

private:
	IUnknown* mIUnknown = nullptr;
};
}
