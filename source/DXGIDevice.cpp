#include "DXGIDevice.h"

namespace SWApi
{
namespace DXGI
{
    Device::Device(const Device& other)
        : Unknown(other)
        INITIALIZE_VERSIONED_VARIABLES(DXGIDEVICE_VERSIONS, NUM_DXGIDEVICE_VERSIONS, mDevice, other.mDevice)
    {
        ADDREF_TO_VERSIONED_VARIABLES(DXGIDEVICE_VERSIONS, NUM_DXGIDEVICE_VERSIONS, mDevice)
    }

    Device::Device(Device&& other) noexcept
        : Unknown(std::forward<Unknown>(other))
        INITIALIZE_VERSIONED_VARIABLES(DXGIDEVICE_VERSIONS, NUM_DXGIDEVICE_VERSIONS, mDevice, other.mDevice)
    {
        ASSIGN_TO_VERSIONED_VARIABLES(DXGIDEVICE_VERSIONS, NUM_DXGIDEVICE_VERSIONS, other.mDevice, nullptr)
    }

    Device::~Device()
    {
        RELEASE_VERSIONED_VARIABLES(DXGIDEVICE_VERSIONS, NUM_DXGIDEVICE_VERSIONS, mDevice)
    }
}
}
