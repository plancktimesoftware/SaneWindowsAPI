#pragma once

#include <optional>
#include <d2d1helper.h>
#include "WinResult.h"
#include "D2D1RenderTarget.h"
#include "CommonMacros.h"

namespace SWApi
{
namespace DXGI
{
	class Surface;
}

class Stream;

namespace D2D1
{
	class Image;
	class Bitmap;
	class Brush;
	class SolidColorBrush;
	class Geometry;
	class SvgDocument;
	class Effect;

#define D2D1DEVICECONTEXT_VERSIONS (0, 1, 2, 3, 4, 5, 6)
#define NUM_D2D1DEVICECONTEXT_VERSIONS 7

	class DeviceContext : public RenderTarget
	{
	public:
		auto CreateBitmap(
			D2D1_SIZE_U size, const void* sourceData, UINT32 pitch,
			const D2D1_BITMAP_PROPERTIES1& bitmapProperties)
			-> WinResult<Bitmap>;

		auto CreateBitmapFromDxgiSurface(
			const DXGI::Surface& dxgiSurface, const D2D1_BITMAP_PROPERTIES1& bitmapProperties)
			-> WinResult<Bitmap>;

		void SetTarget(const Image& target);
		void BeginDraw();
		WinResult<void> EndDraw();
		void Clear(const std::optional<D2D1_COLOR_F>& clearColor = std::nullopt);

		auto CreateSolidColorBrush(const D2D1_COLOR_F& color) -> WinResult<SolidColorBrush>;

		auto CreateEffect(REFCLSID effectID) -> WinResult<Effect>;

		void DrawBitmap(
			const Bitmap& bitmap, std::optional<D2D1_RECT_F> destRect, FLOAT opacity,
			D2D1_INTERPOLATION_MODE interpolationMode, std::optional<D2D1_RECT_F> sourceRect,
			std::optional<D2D1_MATRIX_4X4_F> perspectiveTransform);

		void DrawImage(
			const Image& image,
			std::optional<D2D1_POINT_2F> targetOffset, std::optional<D2D1_RECT_F> imageRectangle,
			D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
			D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER);

		void DrawEffect(
			const Effect& effect,
			std::optional<D2D1_POINT_2F> targetOffset, std::optional<D2D1_RECT_F> imageRectangle,
			D2D1_INTERPOLATION_MODE interpolationMode = D2D1_INTERPOLATION_MODE_LINEAR,
			D2D1_COMPOSITE_MODE compositeMode = D2D1_COMPOSITE_MODE_SOURCE_OVER);

		void FillEllipse(const D2D1_ELLIPSE& ellipse, const Brush& brush);

		void FillGeometry(const Geometry& geometry, const Brush& brush, std::optional<Brush> opacityBrush);

		WinResult<SvgDocument> CreateSvgDocument(std::optional<Stream> xmlStream, D2D1_SIZE_F size);

		void DrawSvgDocument(const SvgDocument& svgDocument);

		::D2D1::Matrix3x2F GetTransform();

		void SetTransform(const ::D2D1::Matrix3x2F& transformMatrix);

		DeviceContext() = default;
		DeviceContext(const DeviceContext& other);
		DeviceContext(DeviceContext&& other);

		~DeviceContext();

		template<typename D2D1DeviceContextT>
		void SetNative(D2D1DeviceContextT* dcPtr);

	private:
		DECLARE_VERSIONED_POINTER_VARIABLES(D2D1DEVICECONTEXT_VERSIONS, NUM_D2D1DEVICECONTEXT_VERSIONS, ID2D1DeviceContext, mDeviceContext, nullptr)
	};

	template<typename D2D1DeviceContextT>
	inline void DeviceContext::SetNative(D2D1DeviceContextT* dcPtr)
	{
		if (dcPtr == nullptr) return;

		ID2D1RenderTarget* d2d1RenderTargetPtr = nullptr;
		auto hres = dcPtr->QueryInterface(&d2d1RenderTargetPtr);
		if (hres != S_OK) return;
		RenderTarget::SetNative(d2d1RenderTargetPtr);

		RELEASE_VERSIONED_VARIABLES(D2D1DEVICECONTEXT_VERSIONS, NUM_D2D1DEVICECONTEXT_VERSIONS, mDeviceContext)

		QUERY_INTERFACE_VERSIONED_VARIABLES(D2D1DEVICECONTEXT_VERSIONS, NUM_D2D1DEVICECONTEXT_VERSIONS, mDeviceContext, dcPtr, /*no return*/);
		dcPtr->Release();
	}
}
}

