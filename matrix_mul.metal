#include <metal_stdlib>
using namespace metal;

kernel void matrix_multiply(device const float* A,
                            device const float* B,
                            device float* C,
                            uint rowsA,
                            uint colsA,
                            uint colsB,
                            uint id [[thread_position_in_grid]]) {
	uint row = id / colsB;
	uint col = id % colsB;

	if (row < rowsA && col < colsB) {
		float value = 0.0;
		for (uint i = 0; i < colsA; ++i) {
			value += A[row * colsA + i] * B[i * colsB + col];
		}
		C[row * colsB + col] = value;
	}
}
