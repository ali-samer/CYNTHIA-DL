#pragma once

CYDL_BEGIN_LIB_NAMESPACE

struct CYDL_DEFAULT_AFLAG DeviceTags
{
	struct CPU;
	struct GPU;
	struct FPGA;
	struct TPU;          // Tensor Processing Unit for AI acceleration
	struct DSP;          // Digital Signal Processor for high-speed numeric processing
	struct ASIC;         // Application-Specific Integrated Circuit, custom hardware for specific tasks
	struct Neuromorphic; // Hardware inspired by the neural structure of the brain
	struct Quantum;      // For quantum computing devices
	struct IoT;          // Internet of Things devices with computation capabilities
	struct Mobile;       // Smartphones, tablets, and other mobile devices
	struct Edge;         // Edge computing devices for low-latency, location-aware processing
	// ... potentially more device categories
};


CYDL_END_LIB_NAMESPACE
