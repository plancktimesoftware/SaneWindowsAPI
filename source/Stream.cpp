#include "Stream.h"
#include <Shlwapi.h>

namespace SWApi
{
	WinResult<Stream> Stream::FromFile(const std::wstring& filePath, DWORD mode)
	{
		IStream* streamPtr = nullptr;
		auto hres = SHCreateStreamOnFileW(filePath.c_str(), mode, &streamPtr);
		if (hres != S_OK)
			return Err(hres);
		Stream stream;
		stream.SetNative(streamPtr);
		return stream;
	}

	Stream::Stream(const Stream& other)
		: SequentialStream(other)
		, mIStream(other.mIStream)
	{
		if (mIStream)
			mIStream->AddRef();
	}

	Stream::Stream(Stream&& other) noexcept(true)
		: SequentialStream(std::forward<SequentialStream>(other))
		, mIStream(other.mIStream)
	{
		other.mIStream = nullptr;
	}

	Stream::~Stream()
	{
		if (mIStream == nullptr) return;
		mIStream->Release();
		mIStream = nullptr;
	}

	void Stream::SetNative(IStream* streamPtr)
	{
		if (mIStream && mIStream != streamPtr)
			mIStream->Release();

		mIStream = streamPtr;

		ISequentialStream* sequentialStreamPtr = nullptr;
		if (mIStream == nullptr || S_OK != mIStream->QueryInterface(&sequentialStreamPtr))
			sequentialStreamPtr = nullptr;
		SequentialStream::SetNative(sequentialStreamPtr);
	}
}
