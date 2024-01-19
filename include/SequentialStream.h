#pragma once

#include "Wrapper.h"
#include <objidl.h>

namespace SWApi
{
	class SequentialStream : public Unknown
	{
	public:
		SequentialStream() = default;
		SequentialStream(const SequentialStream& other);
		SequentialStream(SequentialStream&& other);

		~SequentialStream();

		void SetNative(ISequentialStream* sequentialStreamPtr);
	private:
		ISequentialStream* mISequentialStream = nullptr;
	};
}
