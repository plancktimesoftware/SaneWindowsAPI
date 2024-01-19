#pragma once

#include <winnt.h>
#include "Result.h"

namespace SWApi
{
	template<typename ValT>
	using WinResult = Result<ValT, HRESULT>;
}
