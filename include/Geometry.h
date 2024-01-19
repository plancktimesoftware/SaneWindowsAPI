#pragma once

#include <algorithm>

namespace SWApi
{
	/// Represents a point in the x-y plane.
	struct Point
	{
		LONG x, y; ///< X and Y coordinates.

		Point() = default;
		constexpr Point(const Point& other) = default;
		constexpr Point(Point&& other) = default;
		constexpr Point(LONG x_, LONG y_)
			: x(x_), y(y_) {}
		constexpr Point(const POINT& nativePOINT)
			: x(nativePOINT.x), y(nativePOINT.y) {}

		/// Operator for converting into a native POINT.
		operator POINT() const;

		///@{ Arithmetic Operators
		Point operator+(Point& otherPoint) const;
		Point operator+(Point&& otherPoint) const;
		Point operator+(LONG offset) const;
		Point operator-(Point& otherPoint) const;
		Point operator-(Point&& otherPoint) const;
		Point operator-(LONG offset) const;
		Point operator*(float multiplier) const;
		Point operator/(float divisor) const;
		Point& operator+=(Point& otherPoint);
		Point& operator+=(Point&& otherPoint);
		Point& operator+=(LONG offset);
		Point& operator-=(Point& otherPoint);
		Point& operator-=(Point&& otherPoint);
		Point& operator-=(LONG offset);
		Point& operator*=(float multiplier);
		Point& operator/=(float divisor);
		///@}

		///@{ Comparison Operators
		bool operator==(const Point& other) const;
		///@}
	};

	/// Represents the size of an object in the x-y plane.
	struct Size
	{
		LONG w, h; ///< Width and Height.

		Size() = default;
		constexpr Size(const Size& other) = default;
		constexpr Size(Size&& other) = default;
		constexpr Size(LONG w_, LONG h_)
			: w(w_), h(h_) {}
		constexpr Size(const SIZE& nativeSIZE)
			: w(nativeSIZE.cx), h(nativeSIZE.cy) {}

		/// Operator for converting into a native POINT.
		operator SIZE() const;

		static Size FromRECT(const RECT& rect);

		///@{ Arithmetic Operators
		Size operator+(Size& otherSize) const;
		Size operator+(Size&& otherSize) const;
		Size operator+(LONG outset) const;
		Size operator-(Size& otherSize) const;
		Size operator-(Size&& otherSize) const;
		Size operator-(LONG inset) const;
		Size operator*(float multiplier) const;
		Size operator/(float divisor) const;
		Size& operator+=(Size& otherSize);
		Size& operator+=(Size&& otherSize);
		Size& operator+=(LONG outset);
		Size& operator-=(Size& otherSize);
		Size& operator-=(Size&& otherSize);
		Size& operator-=(LONG inset);
		Size& operator*=(float multiplier);
		Size& operator/=(float divisor);
		///@}

		///@{ Comparison Operators
		bool operator==(const Size& other) const;
		///@}
	};

	/**
	 * Enum containing all types of anchor points for Rect.
	 *          kTopLeft    kTopCenter   kTopRight
	 *              +-----------+-----------+
	 *              |           |           |
	 *              |           |           |
	 *              |           |kCenter    |
	 *  kLeftCenter +-----------+-----------+ kRightCenter
	 *              |           |           |
	 *              |           |           |
	 *              |           |           |
	 *              +-----------+-----------+
	 *       kBottomLeft  kBottomCenter  kBottomRight
	 */
	enum class RectAnchor
	{
		///@{ Corners
		kTopLeft,
		kTopRight,
		kBottomLeft,
		kBottomRight,
		///@}
		kCenter, ///< Center point
		///@{ Midpoints of sides
		kLeftCenter,
		kTopCenter,
		kRightCenter,
		kBottomCenter
		///@}
	};

	/// Represents a rectangle in the x-y plane.
	struct Rect
	{
		LONG left, top, right, bottom; ///< Coordinates of all 4 edges of the rect.

		Rect() = default;
		constexpr Rect(const Rect& other) = default;
		constexpr Rect(Rect&& other) = default;

		/// Ctor. Takes in coordinates of each edge of the rect.
		constexpr Rect(LONG left, LONG top, LONG right, LONG bottom)
			: left(left), top(top), right(right), bottom(bottom) {}

		/// Ctor. Takes an origin point object and a size object.
		constexpr Rect(const Point& origin, const Size& size)
			: left(origin.x), top(origin.y), right(left + size.w), bottom(top + size.h) {}

		/**
		 * Ctor. Constructs a rect starting from an anchor point.
		 * \see RectAnchor
		 * \param anchorType  The type of anchor whose coordinates are provided.
		 * \param anchorPoint The coordinates of the anchor point.
		 * \param size        The size of the rect.
		 */
		Rect(const RectAnchor anchorType, const Point& anchorPoint, const Size& size);

		/// Ctor. Takes a native RECT.
		constexpr Rect(const RECT& legacyRect)
			: left(legacyRect.left), top(legacyRect.top)
			, right(legacyRect.right), bottom(legacyRect.bottom)
		{}

		/// \return The origin { left, top } of the rect.
		Point Origin() const;
		/// \return The size { width, height } of the rect.
		Size GetSize() const;
		/// \return The width of the rect.
		LONG Width() const;
		/// \return The height of the rect.
		LONG Height() const;
		/// \return The coordinates of the specified anchor.
		Point Anchor(const RectAnchor anchorType) const;

		/// Operator for converting into a native RECT.
		operator RECT() const;

		///@{ Offset methods. Can be chained.
		Rect& Offset(LONG offset);
		Rect& Offset(const Size& offset);
		Rect& Offset(const Rect& offset);
		///@

		///@{ Inset methods. Can be chained.
		Rect& Inset(LONG inset);
		Rect& Inset(const Size& inset);
		Rect& Inset(const Rect& inset);
		///@}

		///@{ Outset methods. Can be chained.
		Rect& Outset(LONG outset);
		Rect& Outset(const Size& outset);
		Rect& Outset(const Rect& outset);
		///@}

		///@{ Arithmetic Operators
		Rect operator*(float multiplier) const;
		Rect operator/(float divisor) const;
		Rect& operator*=(float multiplier);
		Rect& operator/=(float divisor);
		///@}

		///@{ Comparison Operators
		bool operator==(const Rect& other) const;
		bool operator==(const RECT& other) const;
		bool operator!=(const Rect& other) const;
		bool operator!=(const RECT& other) const;
		///@}

		/// Checks whether the specified point lies inside the rect.
		bool ContainsPoint(const Point& point);
		/// Finds the intersection with another rect. Returns empty rect if there if the rects do not intersect.
		Rect FindIntersectionWith(const Rect& otherRect);
		/// Checks if the rect intersects with another rect.
		bool IntersectsWith(const Rect& otherRect);
		/// Creates a new rect of the specifed size at the center of this rect.
		Rect CreateCenteredRect(Size rectSize) const;
	};

	/// Utility function to check if 2 floats are equal within a certain tolerance.
	inline bool FloatIsEqual(FLOAT f1, FLOAT f2)
	{
		const FLOAT epsilon = 1e-5f;
		return std::abs(f1 - f2) <= epsilon * std::abs(f1);
	}
}

