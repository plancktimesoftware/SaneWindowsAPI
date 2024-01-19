
#include "Geometry.h"

namespace SWApi
{
	Point::operator POINT() const
	{
		return POINT{ x, y };
	}

	Point Point::operator+(Point& otherPoint) const
	{
		return { x + otherPoint.x, y + otherPoint.y };
	}

	Point Point::operator+(Point&& otherPoint) const
	{
		return { x + otherPoint.x, y + otherPoint.y };
	}

	Point Point::operator+(LONG offset) const
	{
		return { x + offset, y + offset };
	}

	Point Point::operator-(Point& otherPoint) const
	{
		return { x - otherPoint.x, y - otherPoint.y };
	}

	Point Point::operator-(Point&& otherPoint) const
	{
		return { x - otherPoint.x, y - otherPoint.y };
	}

	Point Point::operator-(LONG offset) const
	{
		return { x - offset, y - offset };
	}

	Point Point::operator*(float multiplier) const
	{
		return { static_cast<LONG>(multiplier * x), static_cast<LONG>(multiplier * y) };
	}

	Point Point::operator/(float divisor) const
	{
		if (FloatIsEqual(divisor, 0.0f))
			return *this;
		else
			return { static_cast<LONG>(x / divisor), static_cast<LONG>(y / divisor) };
	}

	Point& Point::operator+=(Point& otherPoint)
	{
		x += otherPoint.x;
		y += otherPoint.y;
		return *this;
	}

	Point& Point::operator+=(Point&& otherPoint)
	{
		x += otherPoint.x;
		y += otherPoint.y;
		return *this;
	}

	Point& Point::operator+=(LONG offset)
	{
		x += offset;
		y += offset;
		return *this;
	}

	Point& Point::operator-=(Point& otherPoint)
	{
		x -= otherPoint.x;
		y -= otherPoint.y;
		return *this;
	}

	Point& Point::operator-=(Point&& otherPoint)
	{
		x -= otherPoint.x;
		y -= otherPoint.y;
		return *this;
	}

	Point& Point::operator-=(LONG offset)
	{
		x -= offset;
		y -= offset;
		return *this;
	}

	Point& Point::operator*=(float multiplier)
	{
		x = static_cast<LONG>(multiplier * x);
		y = static_cast<LONG>(multiplier * y);
		return *this;
	}

	Point& Point::operator/=(float divisor)
	{
		if (!FloatIsEqual(divisor, 0.0f))
		{
			x = static_cast<LONG>(x / divisor);
			y = static_cast<LONG>(y / divisor);
		}
		return *this;
	}

	bool Point::operator==(const Point& other) const
	{
		return x == other.x && y == other.y;
	}

	///////////////////////////////////////////////////////////////////////////

	Size::operator SIZE() const
	{
		return SIZE{ w, h };
	}

	Size Size::FromRECT(const RECT& rect)
	{
		return { rect.right - rect.left, rect.bottom - rect.top };
	}

	Size Size::operator+(Size& otherSize) const
	{
		return { w + otherSize.w, h + otherSize.h };
	}

	Size Size::operator+(Size&& otherSize) const
	{
		return { w + otherSize.w, h + otherSize.h };
	}

	Size Size::operator+(LONG outset) const
	{
		return { w + outset, h + outset };
	}

	Size Size::operator-(Size& otherSize) const
	{
		return { w - otherSize.w, h - otherSize.h };
	}

	Size Size::operator-(Size&& otherSize) const
	{
		return { w - otherSize.w, h - otherSize.h };
	}

	Size Size::operator-(LONG inset) const
	{
		return { w - inset, h - inset };
	}

	Size Size::operator*(float multiplier) const
	{
		return { static_cast<LONG>(multiplier * w), static_cast<LONG>(multiplier * h) };
	}

	Size Size::operator/(float divisor) const
	{
		if (FloatIsEqual(divisor, 0.0f))
			return *this;
		else
			return { static_cast<LONG>(w / divisor), static_cast<LONG>(h / divisor) };
	}

	Size& Size::operator+=(Size& otherSize)
	{
		w += otherSize.w;
		h += otherSize.h;
		return *this;
	}

	Size& Size::operator+=(Size&& otherSize)
	{
		w += otherSize.w;
		h += otherSize.h;
		return *this;
	}

	Size& Size::operator+=(LONG outset)
	{
		w += outset;
		h += outset;
		return *this;
	}

	Size& Size::operator-=(Size& otherSize)
	{
		w -= otherSize.w;
		h -= otherSize.h;
		return *this;
	}

	Size& Size::operator-=(Size&& otherSize)
	{
		w -= otherSize.w;
		h -= otherSize.h;
		return *this;
	}

	Size& Size::operator-=(LONG inset)
	{
		w -= inset;
		h -= inset;
		return *this;
	}

	Size& Size::operator*=(float multiplier)
	{
		w = static_cast<LONG>(multiplier * w);
		h = static_cast<LONG>(multiplier * h);
		return *this;
	}

	Size& Size::operator/=(float divisor)
	{
		if (!FloatIsEqual(divisor, 0.0f))
		{
			w = static_cast<LONG>(w / divisor);
			h = static_cast<LONG>(h / divisor);
		}
		return *this;
	}

	bool Size::operator==(const Size& other) const
	{
		return w == other.w && h == other.h;
	}

	///////////////////////////////////////////////////////////////////////////

	Rect::Rect(const RectAnchor anchorType, const Point& anchorPoint, const Size& size)
	{
		switch (anchorType)
		{
		case RectAnchor::kTopLeft:
			left = anchorPoint.x, top = anchorPoint.y, right = left + size.w, bottom = top + size.h;
			break;
		case RectAnchor::kTopRight:
			right = anchorPoint.x, top = anchorPoint.y, left = right - size.w, bottom = top + size.h;
			break;
		case RectAnchor::kBottomLeft:
			left = anchorPoint.x, bottom = anchorPoint.y, right = left + size.w, top = bottom - size.h;
			break;
		case RectAnchor::kBottomRight:
			right = anchorPoint.x, bottom = anchorPoint.y, left = right - size.w, top = bottom - size.h;
			break;
		case RectAnchor::kCenter:
			left = anchorPoint.x - (size.w / 2), top = anchorPoint.y - (size.h / 2), right = left + size.w, bottom = top + size.h;
			break;
		case RectAnchor::kLeftCenter:
			left = anchorPoint.x, top = anchorPoint.y - (size.h / 2), right = left + size.w, bottom = top + size.h;
			break;
		case RectAnchor::kTopCenter:
			left = anchorPoint.x - (size.w / 2), top = anchorPoint.y, right = left + size.w, bottom = top + size.h;
			break;
		case RectAnchor::kRightCenter:
			right = anchorPoint.x, top = anchorPoint.y - (size.h / 2), left = right - size.w, bottom = top + size.h;
			break;
		case RectAnchor::kBottomCenter:
			left = anchorPoint.x - (size.w / 2), bottom = anchorPoint.y, right = left + size.w, top = bottom - size.h;
			break;
		default:
			left = top = right = bottom = 0;
			break;
		}
	}

	Point Rect::Origin() const
	{
		return { left, top };
	}

	Size Rect::GetSize() const
	{
		return { Width(), Height() };
	}

	LONG Rect::Width() const
	{
		return right - left;
	}

	LONG Rect::Height() const
	{
		return bottom - top;
	}

	Point Rect::Anchor(const RectAnchor anchorType) const
	{
		switch (anchorType)
		{
		case RectAnchor::kTopLeft:
			return { left, top };
		case RectAnchor::kTopRight:
			return { right, top };
		case RectAnchor::kBottomLeft:
			return { left, bottom };
		case RectAnchor::kBottomRight:
			return { right, bottom };
		case RectAnchor::kCenter:
			return { left + (Width() / 2), top + (Height() / 2) };
		case RectAnchor::kLeftCenter:
			return { left, top + (Height() / 2) };
		case RectAnchor::kTopCenter:
			return { left + (Width() / 2), top };
		case RectAnchor::kRightCenter:
			return { right, top + (Height() / 2) };
		case RectAnchor::kBottomCenter:
			return { left + (Width() / 2), bottom };
		default:
			return {};
		}
	}

	Rect::operator RECT() const
	{
		return { left, top, right, bottom };
	}

	Rect& Rect::Offset(LONG offset)
	{
		left += offset;
		top += offset;
		right += offset;
		bottom += offset;
		return *this;
	}

	Rect& Rect::Offset(const Size& offset)
	{
		left += offset.w;
		top += offset.h;
		right += offset.w;
		bottom += offset.h;
		return *this;
	}

	Rect& Rect::Offset(const Rect& offset)
	{
		left += offset.left;
		top += offset.top;
		right += offset.right;
		bottom += offset.bottom;
		return *this;
	}

	Rect& Rect::Inset(LONG inset)
	{
		left += inset;
		top += inset;
		right -= inset;
		bottom -= inset;
		return *this;
	}

	Rect& Rect::Inset(const Size& inset)
	{
		left += inset.w;
		top += inset.h;
		right -= inset.w;
		bottom -= inset.h;
		return *this;
	}

	Rect& Rect::Inset(const Rect& inset)
	{
		left += inset.left;
		top += inset.top;
		right -= inset.right;
		bottom -= inset.bottom;
		return *this;
	}

	Rect& Rect::Outset(LONG outset)
	{
		left -= outset;
		top -= outset;
		right += outset;
		bottom += outset;
		return *this;
	}

	Rect& Rect::Outset(const Size& outset)
	{
		left -= outset.w;
		top -= outset.h;
		right += outset.w;
		bottom += outset.h;
		return *this;
	}

	Rect& Rect::Outset(const Rect& outset)
	{
		left -= outset.left;
		top -= outset.top;
		right += outset.right;
		bottom += outset.bottom;
		return *this;
	}

	Rect Rect::operator*(float multiplier) const
	{
		return {
			static_cast<LONG>(multiplier * left),
			static_cast<LONG>(multiplier * top),
			static_cast<LONG>(multiplier * right),
			static_cast<LONG>(multiplier * bottom)
		};
	}

	Rect Rect::operator/(float divisor) const
	{
		if (FloatIsEqual(divisor, 0.0f))
			return *this;
		else
			return {
				static_cast<LONG>(left / divisor),
				static_cast<LONG>(top / divisor),
				static_cast<LONG>(right / divisor),
				static_cast<LONG>(bottom / divisor)
		};
	}

	Rect& Rect::operator*=(float multiplier)
	{
		left = static_cast<LONG>(multiplier * left);
		top = static_cast<LONG>(multiplier * top);
		right = static_cast<LONG>(multiplier * right);
		bottom = static_cast<LONG>(multiplier * bottom);
		return *this;
	}

	Rect& Rect::operator/=(float divisor)
	{
		if (!FloatIsEqual(divisor, 0.0f))
		{
			left = static_cast<LONG>(left / divisor);
			top = static_cast<LONG>(top / divisor);
			right = static_cast<LONG>(right / divisor);
			bottom = static_cast<LONG>(bottom / divisor);
		}
		return *this;
	}

	bool Rect::operator==(const Rect& other) const
	{
		return left == other.left
			&& top == other.top
			&& right == other.right
			&& bottom == other.bottom;
	}

	bool Rect::operator==(const RECT& other) const
	{
		return left == other.left
			&& top == other.top
			&& right == other.right
			&& bottom == other.bottom;
	}

	bool Rect::operator!=(const Rect& other) const
	{
		return left != other.left
			|| top != other.top
			|| right != other.right
			|| bottom != other.bottom;
	}

	bool Rect::operator!=(const RECT& other) const
	{
		return left != other.left
			|| top != other.top
			|| right != other.right
			|| bottom != other.bottom;
	}

	bool Rect::ContainsPoint(const Point& point)
	{
		return point.x >= left && point.x < right
			&& point.y >= top && point.y < bottom;
	}

	Rect Rect::FindIntersectionWith(const Rect& otherRect)
	{
		if (!IntersectsWith(otherRect))
			return Rect(); // Return empty rect.

		return {
			max(left, otherRect.left),
			max(top, otherRect.top),
			min(right, otherRect.right),
			min(bottom, otherRect.bottom)
		};
	}

	bool Rect::IntersectsWith(const Rect& otherRect)
	{
		// If one rect is on left side of the other.
		if (right <= otherRect.left || otherRect.right <= left)
			return false;

		// If one rect is above the other.
		if (bottom <= otherRect.top || otherRect.bottom <= top)
			return false;

		return true;
	}

	Rect Rect::CreateCenteredRect(Size rectSize) const
	{
		LONG x = left + ((Width() - rectSize.w) / 2);
		LONG y = top + ((Height() - rectSize.h) / 2);
		return { x, y, x + rectSize.w, y + rectSize.h };
	}
}

