#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "histEqSerial.h"

namespace py = pybind11;

py::array_t<int> RGBtoYCbCr(py::array_t<int> input)
{
    py::buffer_info input_buf = input.request();
    if (input_buf.ndim != 3)
        throw std::runtime_error("Number of dimensions must be 3");
    int *input_ptr = static_cast<int *>(input_buf.ptr);

    int row = input_buf.shape[0], col = input_buf.shape[1], channel = input_buf.shape[2];
    auto result = py::array_t<int>(row * col * channel);
    py::buffer_info result_buf = result.request();
    int *result_ptr = static_cast<int *>(result_buf.ptr);

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            int B = input_ptr[(i * col + j) * channel + 0];
            int G = input_ptr[(i * col + j) * channel + 1];
            int R = input_ptr[(i * col + j) * channel + 2];

            result_ptr[(i * col + j) * channel + 0] = std::round(0.299 * R + 0.587 * G + 0.114 * B);
            result_ptr[(i * col + j) * channel + 1] = std::round(0.5 * R - 0.4187 * G - 0.0813 * B + 128);
            result_ptr[(i * col + j) * channel + 2] = std::round(-0.1687 * R - 0.3313 * G + 0.5 * B + 128);
        }

    result.resize({row, col, channel});
    return result;
}

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

py::array_t<int> YCbCrtoRGB(py::array_t<int> input)
{
    py::buffer_info input_buf = input.request();
    if (input_buf.ndim != 3)
        throw std::runtime_error("Number of dimensions must be 3");
    int *input_ptr = static_cast<int *>(input_buf.ptr);

    int row = input_buf.shape[0], col = input_buf.shape[1], channel = input_buf.shape[2];
    auto result = py::array_t<int>(row * col * channel);
    py::buffer_info result_buf = result.request();
    int *result_ptr = static_cast<int *>(result_buf.ptr);

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            int Y = input_ptr[(i * col + j) * channel + 0];
            int Cr = input_ptr[(i * col + j) * channel + 1];
            int Cb = input_ptr[(i * col + j) * channel + 2];

            result_ptr[(i * col + j) * channel + 0] = std::round(Y + 1.772 * (Cb - 128));
            result_ptr[(i * col + j) * channel + 1] = std::round(Y - 0.34414 * (Cb - 128) - 0.71414 * (Cr - 128));
            result_ptr[(i * col + j) * channel + 2] = std::round(Y + 1.402 * (Cr - 128));
        }

    result.resize({row, col, channel});
    return result;
}

// py::array_t<int> bilateralFilter(py::array_t<int> input, int kernel_size, double sigma_d, double sigma_r)
// {
//     py::buffer_info input_buf = input.request();
//     if (input_buf.ndim != 3)
//         throw std::runtime_error("Number of dimensions must be 3");

//     int width = input_buf.shape[0], height = input_buf.shape[1], channels = input_buf.shape[2];
//     int *image = static_cast<int *>(input_buf.ptr);

//     auto result = py::array_t<int>(width * height * channels);
//     py::buffer_info result_buf = result.request();
//     int *output = static_cast<int *>(result_buf.ptr);

//     // Make sure the kernel size is odd
//     if (kernel_size % 2 == 0)
//         kernel_size++;

//     // Clamp the kernel size to the maximum allowed
//     kernel_size = std::min(kernel_size, MAX_KERNEL_SIZE);

//     // Half of the kernel size
//     int half_size = kernel_size / 2;

//     // For each pixel in the image
//     for (int y = 0; y < height; y++)
//     {
//         for (int x = 0; x < width; x++)
//         {
//             // For each channel (e.g. red, green, blue)
//             for (int c = 0; c < channels; c++)
//             {
//                 double sum = 0;
//                 double weight_sum = 0;

//                 // For each pixel in the kernel
//                 for (int j = -half_size; j <= half_size; j++)
//                 {
//                     for (int i = -half_size; i <= half_size; i++)
//                     {
//                         // Calculate the indices of the current pixel in the kernel
//                         int x_pos = x + i;
//                         int y_pos = y + j;

//                         // Make sure the pixel is within the bounds of the image
//                         if (x_pos >= 0 && x_pos < width && y_pos >= 0 && y_pos < height)
//                         {
//                             // Calculate the weight for this pixel
//                             double w = weight(i, j, sigma_d, sigma_r);

//                             // Get the intensity of the current pixel
//                             int intensity = image[y_pos * width * channels + x_pos * channels + c];

//                             // Add the intensity and weight to the sums
//                             sum += intensity * w;
//                             weight_sum += w;
//                         }
//                     }
//                 }
//                 // Set the output pixel to the weighted average intensity
//                 output[y * width * channels + x * channels + c] = (int)sum;
//             }
//         }
//     }

//     result.resize({width, height, channels});
//     return result;
// }