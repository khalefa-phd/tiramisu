#include "Halide.h"
#include "wrapper_test_142.h"

#include <tiramisu/utils.h>

int main(int, char **) {
    Halide::Buffer<uint8_t> input(200, 100);
    Halide::Buffer<uint8_t> output(200, 100);
    Halide::Buffer<uint8_t> reference(200, 100);
    // Initialize buffers
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 100; j++) {
            input(i, j) = i % 7 + 2 * j % 13;
            output(i, j) = 123;
            reference(i, j) = (i % 7 + 2 * j % 13) * 2;
        }
    }

    test_142(input.raw_buffer(), output.raw_buffer());
    compare_buffers("init", output, reference);

    return 0;
}
