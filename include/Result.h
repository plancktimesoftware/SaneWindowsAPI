#pragma once

#if _HAS_CXX23

#include <expected>
namespace SWApi
{
	template<typename ValT, typename ErrT>
	using Result = std::expected<ValT, ErrT>;
	template<typename ErrT>
	using Err = std::unexpected<ErrT>;
}
#else

#include <utility>
#include <exception>
namespace SWApi
{
	template<typename ErrT>
	class Err
	{
	public:
		constexpr Err(ErrT&& error) : mError{ std::forward<ErrT>(error) } {}
		constexpr Err(const ErrT& error) : mError{ error } {}
		constexpr Err(const Err& other) : mError{ other.mError } {}
		constexpr Err(Err&& other) : mError{ std::move(other.mError) } {}

		constexpr const ErrT& error() const& noexcept { return mError; }
		constexpr ErrT& error() & noexcept { return mError; }
		constexpr const ErrT&& error() const&& noexcept { return std::move(mError); }
		constexpr ErrT&& error() && noexcept { return std::move(mError); }

	private:
		ErrT mError;
	};

	class BadResultAccessException : public std::exception
	{
	public:
		enum class Missing
		{
			ValueMissing,
			ErrorMissing
		};

		BadResultAccessException(Missing whatIsMissing)
			: std::exception(), mMissing{ whatIsMissing } {}

		const char* what() const override
		{
			if (mMissing == Missing::ValueMissing)
				return "Bad Result access. Result does not contain a success value.";
			else
				return "Bad Result access. Result does not contain an error.";
		}
	private:
		Missing mMissing;
	};

	template<typename ValT, typename ErrT>
	class Result
	{
	public:
		constexpr Result(ValT&& value) : mValue{ std::forward<ValT>(value) }, mHasValue{ true } {}
		constexpr Result(const Err<ErrT>& error) : mError{ error.error() }, mHasValue{ false } {}
		constexpr Result(Err<ErrT>&& error) : mError{ std::move(error.error()) }, mHasValue{ false } {}

		constexpr Result(const Result<ValT, ErrT>& other)
			: mHasValue(other.mHasValue) {
			CopyConstruct(other);
		}

		constexpr Result(Result<ValT, ErrT>&& other)
			: mHasValue(other.mHasValue) {
			MoveConstruct(std::forward<Result<ValT, ErrT>>(other));
		}

		~Result() { Destroy(); }

		constexpr Result& operator=(const Result<ValT, ErrT>& other)
		{
			if (mHasValue != other.mHasValue)
			{
				Destroy();
				CopyConstruct(other);
			}
			else
			{
				if (mHasValue)
					mValue = other.mValue;
				else
					mError = other.mError;
			}
			return *this;
		}

		constexpr Result& operator=(Result<ValT, ErrT>&& other)
		{
			if (mHasValue != other.mHasValue)
			{
				Destroy();
				MoveConstruct(std::forward<Result<ValT, ErrT>>(other));
			}
			else
			{
				if (mHasValue)
					mValue = std::move(other.mValue);
				else
					mError = std::move(other.mError);
			}
			return *this;
		}

		constexpr Result& operator=(ValT&& value)
		{
			if (!mHasValue)
			{
				mError.~ErrT();
				new(&mValue) ValT(std::forward<ValT>(value));
			}
			else
				mValue = std::forward<ValT>(value);
			return *this;
		}
		constexpr Result& operator=(const Err<ErrT>& error)
		{
			if (mHasValue)
			{
				mValue.~ValT();
				new(&mError) ErrT(error.error());
			}
			else
				mError = error.error();
			return *this;
		}
		constexpr Result& operator=(Err<ErrT>&& error)
		{
			if (mHasValue)
			{
				mValue.~ValT();
				new(&mError) ErrT(std::forward<ErrT>(error.error()));
			}
			else
				mError = std::forward<ErrT>(error.error());
			return *this;
		}

		constexpr const ValT* operator->() const noexcept { return &mValue; }
		constexpr ValT* operator->() noexcept { return &mValue; }
		constexpr const ValT& operator*() const& noexcept { return &mValue; }
		constexpr ValT& operator*() & noexcept { return mValue; }
		constexpr const ValT&& operator*() const&& noexcept { return std::move(mValue); }
		constexpr ValT&& operator*() && noexcept { return std::move(mValue); }

		constexpr operator bool() const { return mHasValue; }
		constexpr bool has_value() const { return mHasValue; }

		constexpr ValT& value()&
		{
			if (!mHasValue)
				throw BadResultAccessException(BadResultAccessException::Missing::ValueMissing);
			return mValue;
		}
		constexpr const ValT& value() const&
		{
			if (!mHasValue)
				throw BadResultAccessException(BadResultAccessException::Missing::ValueMissing);
			return mValue;
		}
		constexpr ValT&& value()&&
		{
			if (!mHasValue)
				throw BadResultAccessException(BadResultAccessException::Missing::ValueMissing);
			return std::move(mValue);
		}
		constexpr const ValT&& value() const&&
		{
			if (!mHasValue)
				throw BadResultAccessException(BadResultAccessException::Missing::ValueMissing);
			return std::move(mValue);
		}

		constexpr const ErrT& error() const&
		{
			if (mHasValue)
				throw BadResultAccessException(BadResultAccessException::Missing::ErrorMissing);
			return mError;
		}
		constexpr ErrT& error()&
		{
			if (mHasValue)
				throw BadResultAccessException(BadResultAccessException::Missing::ErrorMissing);
			return mError;
		}
		constexpr const ErrT&& error() const&&
		{
			if (mHasValue)
				throw BadResultAccessException(BadResultAccessException::Missing::ErrorMissing);
			return std::move(mError);
		}
		constexpr ErrT&& error()&&
		{
			if (mHasValue)
				throw BadResultAccessException(BadResultAccessException::Missing::ErrorMissing);
			return std::move(mError);
		}

		constexpr ValT value_or(ValT&& defaultValue) const
		{
			if (mHasValue) return mValue;
			else return std::forward<ValT>(defaultValue);
		}
		constexpr ValT value_or(ValT&& defaultValue)
		{
			if (mHasValue) return mValue;
			else return std::forward<ValT>(defaultValue);
		}

	private:
		void Destroy()
		{
			if (mHasValue)
				mValue.~ValT();
			else
				mError.~ErrT();
		}

		void CopyConstruct(const Result& other)
		{
			if (other.mHasValue)
				new(&mValue) ValT(other.mValue);
			else
				new(&mError) ErrT(other.mError);
		}

		void MoveConstruct(Result&& other)
		{
			if (other.mHasValue)
				new(&mValue) ValT(std::move(other.mValue));
			else
				new(&mError) ErrT(std::move(other.mError));
		}

	private:
		union
		{
			ValT mValue;
			ErrT mError;
		};
		bool mHasValue;
	};


	template<typename ErrT>
	class Result<void, ErrT>
	{
	public:
		constexpr Result() : mHasValue{ true } {}
		constexpr Result(const Err<ErrT>& error) : mError{ error.error() }, mHasValue{ false } {}
		constexpr Result(Err<ErrT>&& error) : mError{ std::move(error.error()) }, mHasValue{ false } {}

		constexpr Result(const Result<void, ErrT>& other)
			: mHasValue(other.mHasValue) {
			CopyConstruct(other);
		}

		constexpr Result(Result<void, ErrT>&& other)
			: mHasValue(other.mHasValue) {
			MoveConstruct(std::forward<Result<void, ErrT>>(other));
		}

		~Result() { Destroy(); }

		constexpr Result& operator=(const Result<void, ErrT>& other)
		{
			if (mHasValue != other.mHasValue)
			{
				Destroy();
				CopyConstruct(other);
			}
			else if (!mHasValue)
				mError = other.mError;
			return *this;
		}

		constexpr Result& operator=(Result<void, ErrT>&& other)
		{
			if (mHasValue != other.mHasValue)
			{
				Destroy();
				MoveConstruct(std::forward<Result<void, ErrT>>(other));
			}
			else if (!mHasValue)
				mError = std::move(other.mError);
			return *this;
		}

		constexpr Result& operator=(const Err<ErrT>& error)
		{
			if (mHasValue)
				new(&mError) ErrT(error.error());
			else
				mError = error.error();
			return *this;
		}
		constexpr Result& operator=(Err<ErrT>&& error)
		{
			if (mHasValue)
				new(&mError) ErrT(std::forward<ErrT>(error.error()));
			else
				mError = std::forward<ErrT>(error.error());
			return *this;
		}

		constexpr void operator*() const noexcept {}

		constexpr operator bool() const { return mHasValue; }
		constexpr bool has_value() const { return mHasValue; }

		constexpr void value() const
		{
			if (!mHasValue)
				throw BadResultAccessException(BadResultAccessException::Missing::ValueMissing);
		}

		constexpr const ErrT& error() const&
		{
			if (mHasValue)
				throw BadResultAccessException(BadResultAccessException::Missing::ErrorMissing);
			return mError;
		}
		constexpr ErrT& error()&
		{
			if (mHasValue)
				throw BadResultAccessException(BadResultAccessException::Missing::ErrorMissing);
			return mError;
		}
		constexpr const ErrT&& error() const&&
		{
			if (mHasValue)
				throw BadResultAccessException(BadResultAccessException::Missing::ErrorMissing);
			return std::move(mError);
		}
		constexpr ErrT&& error()&&
		{
			if (mHasValue)
				throw BadResultAccessException(BadResultAccessException::Missing::ErrorMissing);
			return std::move(mError);
		}

	private:
		void Destroy()
		{
			if (!mHasValue)
				mError.~ErrT();
		}

		void CopyConstruct(const Result& other)
		{
			if (!other.mHasValue)
				new(&mError) ErrT(other.mError);
		}

		void MoveConstruct(Result&& other)
		{
			if (!other.mHasValue)
				new(&mError) ErrT(std::move(other.mError));
		}

	private:
		union
		{
			ErrT mError;
		};
		bool mHasValue;
	};
}
#endif

