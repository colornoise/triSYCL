/* RUN: %{execute}%s
*/
#include <CL/sycl.hpp>
#include <iostream>
#include "test-helpers.hpp"

using namespace cl::sycl;

// Size of the buffers
constexpr size_t N = 20;
constexpr size_t M = 30;
constexpr size_t P = 40;

int main() {
    // Create some 2D buffers of float for our matrices
    cl::sycl::buffer<int, 1> a(N);
    cl::sycl::buffer<int, 2> b({ N, M });
    cl::sycl::buffer<int, 3> c({ N, M, P });

    // Test from the host
    auto A = a.get_access<cl::sycl::access::read_write,
                          cl::sycl::access::host_buffer>();
    auto B = b.get_access<cl::sycl::access::read_write,
                          cl::sycl::access::host_buffer>();
    auto C = c.get_access<cl::sycl::access::read_write,
                          cl::sycl::access::host_buffer>();

    A[3]= 57;
    VERIFY_READ_WRITE_VALUE(A[3], 57);
    VERIFY_READ_WRITE_VALUE(A[id<1> { 18 }], 7);
    VERIFY_READ_WRITE_VALUE(A[item<1> (N, 2)], 75);
    VERIFY_READ_WRITE_VALUE(A[item<1> (N, 13, 0)], 57);
    VERIFY_READ_WRITE_VALUE(A[item<1> (N, 10, 2)], 5);
    VERIFY_READ_WRITE_VALUE(A[nd_item<1> (7, 2, nd_range<1>{ N, 3 })], 15);

    VERIFY_READ_WRITE_VALUE((B[3][8]), 17);
    VERIFY_READ_WRITE_VALUE(B[id<2> (8, 7)], 87);
    VERIFY_READ_WRITE_VALUE(B[item<2> ({ N, M }, { 2, 3 })], 175);
    VERIFY_READ_WRITE_VALUE(B[item<2> ({ N, M }, { 12, 13 }, { 0, 0 })], 527);
    VERIFY_READ_WRITE_VALUE(B[item<2> ({ N, M }, { 19, 23 }, { 50, 40 })], 5);
    VERIFY_READ_WRITE_VALUE(B[nd_item<2> ({ 7, 5 }, { 2, 2 },
                                          nd_range<2>{ { N, M },
                                              { 4, 4 } })], 9);

  return 0;
}
