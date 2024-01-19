#include "SequentialStream.h"

namespace SWApi
{
	SequentialStream::SequentialStream(const SequentialStream& other)
		: Unknown(other)
		, mISequentialStream{ other.mISequentialStream }
	{
		if (mISequentialStream) mISequentialStream->AddRef();
	}

	SequentialStream::SequentialStream(SequentialStream&& other)
		: Unknown(std::forward<Unknown>(other))
		, mISequentialStream{ other.mISequentialStream }
	{
		other.mISequentialStream = nullptr;
	}

	SequentialStream::~SequentialStream()
	{
		if (mISequentialStream == nullptr) return;
		mISequentialStream->Release();
		mISequentialStream = nullptr;
	}

	void SequentialStream::SetNative(ISequentialStream* sequentialStreamPtr)
	{
		if (mISequentialStream && mISequentialStream != sequentialStreamPtr)
			mISequentialStream->Release();
		mISequentialStream = sequentialStreamPtr;

		IUnknown* unknownNative = nullptr;
		if (mISequentialStream == nullptr
			|| S_OK != mISequentialStream->QueryInterface(&unknownNative))
			unknownNative = nullptr;
		Unknown::SetNative(unknownNative);
	}
}

