

#include "DXGIOutput.h"

namespace SWApi
{
namespace DXGI
{

	Output::Output(const Output& other)
		: Object(other)
		INITIALIZE_VERSIONED_VARIABLES(DXGIOUTPUT_VERSIONS, NUM_DXGIOUTPUT_VERSIONS, mOutput, other.mOutput)
	{
		ADDREF_TO_VERSIONED_VARIABLES(DXGIOUTPUT_VERSIONS, NUM_DXGIOUTPUT_VERSIONS, mOutput);
	}
	Output::Output(Output&& other) noexcept(true)
		: Object(std::forward<Object>(other))
		INITIALIZE_VERSIONED_VARIABLES(DXGIOUTPUT_VERSIONS, NUM_DXGIOUTPUT_VERSIONS, mOutput, other.mOutput)
	{
		ASSIGN_TO_VERSIONED_VARIABLES(DXGIOUTPUT_VERSIONS, NUM_DXGIOUTPUT_VERSIONS, other.mOutput, nullptr)
	}

	Output::~Output()
	{
		RELEASE_VERSIONED_VARIABLES(DXGIOUTPUT_VERSIONS, NUM_DXGIOUTPUT_VERSIONS, mOutput)
	}

}
}

