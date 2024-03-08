#pragma once

#include <utility>
#include <dxgi.h>
#include "Wrapper.h"

namespace SWApi
{
namespace DXGI
{
	class Object : public Unknown
	{
	public:
		Object() = default;
		Object(const Object& other);
		Object(Object&& other) noexcept(true);

		~Object();

		void SetNative(IDXGIObject* dxgiObject);
	private:
		IDXGIObject* mIDXGIObject = nullptr;
	};
}
}
