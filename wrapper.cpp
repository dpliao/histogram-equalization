#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "histEq.hpp"

namespace py = pybind11;

py::array_t<int> histEq(py::array_t<int> input)
{
    py::buffer_info buf = input.request();

    if (buf.ndim != 2)
        throw std::runtime_error("Number of dimensions must be 2");

    int *img = static_cast<int *>(buf.ptr);
    int size = buf.shape[0] * buf.shape[1];
    int *hist = new int[size];
    histEqSerial(hist, img, size, 1);

    auto result = py::array_t<int>(size);
    int *result_buf = static_cast<int *>(result.request().ptr);
    for (int idx = 0; idx < size; idx++)
        result_buf[idx] = hist[idx];

    result.resize({buf.shape[0], buf.shape[1]});
    return result;
}

PYBIND11_MODULE(myHist, m)
{
    m.def("histEq", &histEq, "Histogram Equalization for 1D np array");
}