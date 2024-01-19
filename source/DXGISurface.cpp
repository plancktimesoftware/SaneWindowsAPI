#include "DXGISurface.h"

namespace SWApi
{
namespace DXGI
{
	Surface::Surface(const Surface& other)
		: DeviceSubObject(other)
		INITIALIZE_VERSIONED_VARIABLES(DXGISURFACE_VERSIONS, NUM_DXGISURFACE_VERSIONS, mSurface, other.mSurface)
	{
		ADDREF_TO_VERSIONED_VARIABLES(DXGISURFACE_VERSIONS, NUM_DXGISURFACE_VERSIONS, mSurface)
	}

	Surface::Surface(Surface&& other)
		: DeviceSubObject(std::forward<DeviceSubObject>(other))
		INITIALIZE_VERSIONED_VARIABLES(DXGISURFACE_VERSIONS, NUM_DXGISURFACE_VERSIONS, mSurface, other.mSurface)
	{
		ASSIGN_TO_VERSIONED_VARIABLES(DXGISURFACE_VERSIONS, NUM_DXGISURFACE_VERSIONS, other.mSurface, nullptr)
	}

	Surface::~Surface()
	{
		RELEASE_VERSIONED_VARIABLES(DXGISURFACE_VERSIONS, NUM_DXGISURFACE_VERSIONS, mSurface)
	}
}
}
