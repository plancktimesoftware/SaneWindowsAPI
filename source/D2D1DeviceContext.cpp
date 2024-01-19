#include "D2D1DeviceContext.h"
#include "DXGISurface.h"
#include "D2D1Bitmap.h"
#include "D2D1Brush.h"
#include "D2D1Geometry.h"
#include "D2D1SolidColorBrush.h"
#include "D2D1SvgDocument.h"
#include "D2D1Effect.h"
#include "Stream.h"

namespace SWApi
{
namespace D2D1
{
	auto DeviceContext::CreateBitmap(
		D2D1_SIZE_U size, const void* sourceData, UINT32 pitch,
		const D2D1_BITMAP_PROPERTIES1& bitmapProperties)
		-> WinResult<Bitmap>
	{
		if (!mDeviceContextV0) return Err(E_POINTER);

		ID2D1Bitmap1* d2dBitmapV1 = nullptr;
		auto hres = mDeviceContextV0->CreateBitmap(size, sourceData, pitch, bitmapProperties, &d2dBitmapV1);
		if (hres != S_OK) return Err(hres);

		Bitmap bitmap;
		bitmap.SetNative(d2dBitmapV1);
		return bitmap;
	}

	auto DeviceContext::CreateBitmapFromDxgiSurface(
		const DXGI::Surface& dxgiSurface, const D2D1_BITMAP_PROPERTIES1& bitmapProperties)
		-> WinResult<Bitmap>
	{
		if (!mDeviceContextV0) return Err(E_POINTER);

		auto dxgiSurfacePtr = dxgiSurface.GetNative<IDXGISurface>();
		if (!dxgiSurfacePtr) return Err(E_POINTER);

		ID2D1Bitmap1* d2dBitmapV1 = nullptr;
		auto hres = mDeviceContextV0->CreateBitmapFromDxgiSurface(
			dxgiSurfacePtr, bitmapProperties, &d2dBitmapV1);
		if (hres != S_OK)
			return Err(hres);

		Bitmap bitmap;
		bitmap.SetNative(d2dBitmapV1);
		return bitmap;
	}

	void DeviceContext::SetTarget(const Image& target)
	{
		auto targetPtr = target.GetNative();
		if (!targetPtr) return;

		if (mDeviceContextV0) mDeviceContextV0->SetTarget(targetPtr);
	}

	void DeviceContext::BeginDraw()
	{
		if (mDeviceContextV0) mDeviceContextV0->BeginDraw();
	}

	WinResult<void> DeviceContext::EndDraw()
	{
		if (mDeviceContextV0 == nullptr)
			return Err(E_POINTER);
			
		auto hres = mDeviceContextV0->EndDraw();
		if (hres != S_OK) return Err(hres);

		return WinResult<void>();
	}

	void DeviceContext::Clear(const std::optional<D2D1_COLOR_F>& clearColor)
	{
		if (!mDeviceContextV0) return;
		if (clearColor)
			mDeviceContextV0->Clear(clearColor.value());
		else
			mDeviceContextV0->Clear(nullptr);
	}

	auto DeviceContext::CreateSolidColorBrush(const D2D1_COLOR_F& color)
		-> WinResult<SolidColorBrush>
	{
		if (!mDeviceContextV0) return Err(E_POINTER);

		ID2D1SolidColorBrush* solidBrushPtr = nullptr;
		auto hres = mDeviceContextV0->CreateSolidColorBrush(color, &solidBrushPtr);
		if (hres != S_OK)
			return Err(hres);
		
		SolidColorBrush brush;
		brush.SetNative(solidBrushPtr);
		return brush;
	}

	auto DeviceContext::CreateEffect(REFCLSID effectID) -> WinResult<Effect>
	{
		if (!mDeviceContextV0) return Err(E_POINTER);

		ID2D1Effect* d2d1EffectPtr = nullptr;
		auto hres = mDeviceContextV0->CreateEffect(effectID, &d2d1EffectPtr);
		if (hres != S_OK) return Err(hres);

		Effect effect;
		effect.SetNative(d2d1EffectPtr);
		return effect;
	}

	void DeviceContext::DrawBitmap(
		const Bitmap& bitmap, std::optional<D2D1_RECT_F> destRect, FLOAT opacity,
		D2D1_INTERPOLATION_MODE interpolationMode, std::optional<D2D1_RECT_F> sourceRect,
		std::optional<D2D1_MATRIX_4X4_F> perspectiveTransform)
	{
		if (!mDeviceContextV0) return;

		const D2D1_RECT_F* cDestRect = destRect ? &(destRect.value()) : nullptr;
		const D2D1_RECT_F* cSourceRect = sourceRect ? &(sourceRect.value()) : nullptr;
		const D2D1_MATRIX_4X4_F* cPerspectiveTransform =
			perspectiveTransform ? &(perspectiveTransform.value()) : nullptr;

		mDeviceContextV0->DrawBitmap(
			bitmap.GetNative<ID2D1Bitmap>(), cDestRect, opacity, interpolationMode,
			cSourceRect, cPerspectiveTransform);
	}

	void DeviceContext::DrawImage(
		const Image& image,
		std::optional<D2D1_POINT_2F> targetOffset, std::optional<D2D1_RECT_F> imageRectangle,
		D2D1_INTERPOLATION_MODE interpolationMode, D2D1_COMPOSITE_MODE compositeMode)
	{
		if (!mDeviceContextV0) return;

		mDeviceContextV0->DrawImage(
			image.GetNative(),
			targetOffset ? &(targetOffset.value()) : nullptr,
			imageRectangle ? &(imageRectangle.value()) : nullptr,
			interpolationMode, compositeMode);
	}

	void DeviceContext::DrawEffect(
		const Effect& effect,
		std::optional<D2D1_POINT_2F> targetOffset, std::optional<D2D1_RECT_F> imageRectangle,
		D2D1_INTERPOLATION_MODE interpolationMode, D2D1_COMPOSITE_MODE compositeMode)
	{
		if (!mDeviceContextV0) return;

		mDeviceContextV0->DrawImage(
			effect.GetNative(),
			targetOffset ? &(targetOffset.value()) : nullptr,
			imageRectangle ? &(imageRectangle.value()) : nullptr,
			interpolationMode, compositeMode);
	}

	void DeviceContext::FillEllipse(const D2D1_ELLIPSE& ellipse, const Brush& brush)
	{
		auto brushPtr = brush.GetNative();
		if (!brushPtr) return;

		if (mDeviceContextV0) mDeviceContextV0->FillEllipse(ellipse, brushPtr);
	}

	void DeviceContext::FillGeometry(
		const Geometry& geometry, const Brush& brush, std::optional<Brush> opacityBrush)
	{
		if (!mDeviceContextV0) return;

		mDeviceContextV0->FillGeometry(
			geometry.GetNative(), brush.GetNative(), opacityBrush ? opacityBrush->GetNative() : nullptr);
	}

	WinResult<SvgDocument> DeviceContext::CreateSvgDocument(std::optional<Stream> xmlStream, D2D1_SIZE_F size)
	{
		if (mDeviceContextV5 == nullptr) return Err(E_POINTER);

		IStream* streamPtr = xmlStream ? xmlStream->GetNative() : nullptr;

		ID2D1SvgDocument* d2d1SvgDocumentPtr = nullptr;
		auto hres =
			mDeviceContextV5->CreateSvgDocument(streamPtr, size, &d2d1SvgDocumentPtr);

		if (hres != S_OK)
			return Err(hres);

		SvgDocument svgDocument;
		svgDocument.SetNative(d2d1SvgDocumentPtr);
		return svgDocument;
	}

	void DeviceContext::DrawSvgDocument(const SvgDocument& svgDocument)
	{
		if (mDeviceContextV5 == nullptr) return;

		ID2D1SvgDocument* d2d1SvgDocumentPtr = svgDocument.GetNative();
		if (d2d1SvgDocumentPtr == nullptr) return;

		mDeviceContextV5->DrawSvgDocument(d2d1SvgDocumentPtr);
	}

	::D2D1::Matrix3x2F DeviceContext::GetTransform()
	{
		::D2D1::Matrix3x2F transformMatrix = ::D2D1::Matrix3x2F::Identity();
		if (mDeviceContextV0) mDeviceContextV0->GetTransform(&transformMatrix);
		return transformMatrix;
	}

	void DeviceContext::SetTransform(const ::D2D1::Matrix3x2F& transformMatrix)
	{
		if (mDeviceContextV0) mDeviceContextV0->SetTransform(transformMatrix);
	}

	DeviceContext::DeviceContext(const DeviceContext& other)
		: RenderTarget(other)
		INITIALIZE_VERSIONED_VARIABLES(D2D1DEVICECONTEXT_VERSIONS, NUM_D2D1DEVICECONTEXT_VERSIONS, mDeviceContext, other.mDeviceContext)
	{
		ADDREF_TO_VERSIONED_VARIABLES(D2D1DEVICECONTEXT_VERSIONS, NUM_D2D1DEVICECONTEXT_VERSIONS, mDeviceContext)
	}

	DeviceContext::DeviceContext(DeviceContext&& other)
		: RenderTarget(std::forward<RenderTarget>(other))
		INITIALIZE_VERSIONED_VARIABLES(D2D1DEVICECONTEXT_VERSIONS, NUM_D2D1DEVICECONTEXT_VERSIONS, mDeviceContext, other.mDeviceContext)
	{
		ASSIGN_TO_VERSIONED_VARIABLES(D2D1DEVICECONTEXT_VERSIONS, NUM_D2D1DEVICECONTEXT_VERSIONS, other.mDeviceContext, nullptr)
	}

	DeviceContext::~DeviceContext()
	{
		RELEASE_VERSIONED_VARIABLES(D2D1DEVICECONTEXT_VERSIONS, NUM_D2D1DEVICECONTEXT_VERSIONS, mDeviceContext)
	}

}
}
