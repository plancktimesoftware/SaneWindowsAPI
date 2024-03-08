#include "DXGIObject.h"

namespace SWApi
{
namespace DXGI
{
	Object::Object(const Object& other)
		: Unknown(other)
		, mIDXGIObject{ other.mIDXGIObject }
	{
		if (mIDXGIObject) mIDXGIObject->AddRef();
	}
	Object::Object(Object&& other) noexcept(true)
		: Unknown(std::forward<Unknown>(other))
		, mIDXGIObject{ other.mIDXGIObject }
	{
		other.mIDXGIObject = nullptr;
	}

	Object::~Object()
	{
		if (mIDXGIObject == nullptr) return;
		mIDXGIObject->Release();
		mIDXGIObject = nullptr;
	}

	void Object::SetNative(IDXGIObject* dxgiObject)
	{
		if (mIDXGIObject && mIDXGIObject != dxgiObject)
			mIDXGIObject->Release();
		mIDXGIObject = dxgiObject;

		IUnknown* unknownNative = nullptr;
		if (mIDXGIObject == nullptr
			|| S_OK != mIDXGIObject->QueryInterface(&unknownNative))
			unknownNative = nullptr;
		Unknown::SetNative(unknownNative);
	}
}
}
