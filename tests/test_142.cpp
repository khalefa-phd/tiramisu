#include <tiramisu/tiramisu.h>

using namespace tiramisu;

int main(int argc, char **argv)
{
    tiramisu::init("test_142");

    var i("i", 0, 100), j("j", 0, 200);

    input A({i, j}, p_uint8);
    computation B({i, j}, A(i, j) * uint8_t(2));
    computation C({i, j}, B(i, j) / uint8_t(2));
    computation D({i, j}, C(i, j) * uint8_t(2));

    B.then(C, j)
     .then(D, j);

    tiramisu::codegen({A.auto_buffer(a_input), D.auto_buffer(a_output)}, "build/generated_fct_test_142.o");

    return 0;
}
