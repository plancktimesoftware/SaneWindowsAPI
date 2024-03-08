#pragma once

#include <string>
#include "SequentialStream.h"
#include "WinResult.h"

namespace SWApi
{
	class Stream : public SequentialStream
	{
	public:
		static WinResult<Stream> FromFile(const std::wstring& filePath, DWORD mode);

		Stream() = default;
		Stream(const Stream& other);
		Stream(Stream&& other) noexcept(true);

		~Stream();

		auto GetNative() const -> IStream* { return mIStream; }
		void SetNative(IStream* streamPtr);
	private:
		IStream* mIStream = nullptr;
	};
}
