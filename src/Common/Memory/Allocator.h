#pragma once


#include "Common/Tags/Devices.h"
#include "Common/Policies/CreationPolicy.h"
#include <memory>

CYDL_BEGIN_LIB_NAMESPACE

CYDL_BEGIN_LIB_DETAILS_NAMESPACE
template < typename Device, template < typename > class AllocPolicy >
struct CYDL_DEFAULT_AFLAG Allocator_ CYDL_FINAL
{};

/// \CPU Specialization for CPU allocator
template < template < typename > class AllocPolicy >
struct CYDL_DEFAULT_AFLAG Allocator_< DeviceTags::CPU, AllocPolicy > CYDL_FINAL
{
	template < typename Element >
	static CYDL_FORCE_INLINE std::shared_ptr< Element > Allocate ( CYDL_SIZET elementSize )
	{
		return std::shared_ptr< Element >(
			AllocPolicy<Element>::Create(elementSize) ,
			AllocPolicy<Element>::Delete(elementSize)
			);
	}
};

/// \GPU Specialization for GPU allocator
template < template < typename > class AllocPolicy >
struct CYDL_DEFAULT_AFLAG Allocator_< DeviceTags::GPU, AllocPolicy > CYDL_FINAL
{
	// TODO: Implementation specific to GPU allocation
};

/// \FPGA Specialization for FPGA allocator
template < template < typename > class AllocPolicy >
struct CYDL_DEFAULT_AFLAG Allocator_< DeviceTags::FPGA, AllocPolicy > CYDL_FINAL
{
	// TODO: Implementation specific to FPGA allocation
};

/// \TPU Specialization for TPU allocator
template <template <typename> class AllocPolicy>
struct CYDL_DEFAULT_AFLAG Allocator_< DeviceTags::TPU, AllocPolicy> CYDL_FINAL
{
	// TODO: Implementation specific to TPU allocation
};

/// \DSP Specialization for DSP allocator
template <template <typename> class AllocPolicy>
struct CYDL_DEFAULT_AFLAG Allocator_< DeviceTags::DSP, AllocPolicy> CYDL_FINAL
{
	// TODO: Implementation specific to DSP allocation
};

/// \ASIC Specialization for ASIC allocator
template <template <typename> class AllocPolicy>
struct CYDL_DEFAULT_AFLAG Allocator_< DeviceTags::ASIC, AllocPolicy> CYDL_FINAL
{
	// TODO: Implementation specific to ASIC allocation
};

/// \Neuromorphic Specialization for Neuromorphic hardware allocator
template <template <typename> class AllocPolicy>
struct CYDL_DEFAULT_AFLAG Allocator_< DeviceTags::Neuromorphic, AllocPolicy> CYDL_FINAL
{
	// TODO: Implementation specific to neuromorphic hardware allocation
};

/// \Quantum Specialization for Quantum computing devices allocator
template <template <typename> class AllocPolicy>
struct CYDL_DEFAULT_AFLAG Allocator_< DeviceTags::Quantum, AllocPolicy> CYDL_FINAL
{
	// TODO: Implementation specific to quantum computing devices allocation
};

/// \IoT Specialization for IoT devices allocator
template <template <typename> class AllocPolicy>
struct CYDL_DEFAULT_AFLAG Allocator_< DeviceTags::IoT, AllocPolicy> CYDL_FINAL
{
	// TODO: Implementation specific to IoT devices allocation
};

/// \Mobile Specialization for Mobile devices allocator
template <template <typename> class AllocPolicy>
struct CYDL_DEFAULT_AFLAG Allocator_< DeviceTags::Mobile, AllocPolicy> CYDL_FINAL
{
	// TODO: Implementation specific to mobile devices allocation
};

/// \Edge Specialization for Edge computing devices allocator
template <template <typename> class AllocPolicy>
struct CYDL_DEFAULT_AFLAG Allocator_< DeviceTags::Edge, AllocPolicy> CYDL_FINAL
{
	// TODO: Implementation specific to edge computing devices allocation
};

CYDL_END_LIB_DETAILS_NAMESPACE

template < typename Device, template < typename > class AllocPolicy = CYDL_VPOLICIES::MallocCreator >
using Allocator = CYDL_VDETAILS::Allocator_<Device, AllocPolicy>;

CYDL_END_LIB_NAMESPACE