import numpy as np
import cv2
import myHist
import pytest
import time

filename = 'img/lake.jpg'

def test_histEq():
    myHist_output = openCV_output = cv2.imread(filename)

    myHist_output[:, :, 0] = myHist.histEq(myHist_output[:, :, 0])
    openCV_output[:, :, 0] = cv2.equalizeHist(openCV_output[:, :, 0])

    assert np.array_equal(myHist_output, openCV_output)

def test_RGB_performance():
    my_RGB = opencv_RGB = cv2.imread(filename)

    old_time = time.time()
    my_RGB = myHist.RGBtoYCbCr(my_RGB)
    my_RGB_time = time.time() - old_time

    old_time = time.time()
    opencv_RGB = cv2.cvtColor(opencv_RGB, cv2.COLOR_BGR2YCrCb)
    opencv_RGB_time = time.time() - old_time

    performance =  my_RGB_time / opencv_RGB_time
    assert performance < 1

def test_histEq_performance():
    my_img = opencv_img = cv2.imread(filename)

    old_time = time.time()
    my_img[:, :, 0] = myHist.histEq(my_img[:, :, 0])
    my_hist_time = time.time() - old_time

    old_time = time.time()
    opencv_img[:, :, 0] = cv2.equalizeHist(opencv_img[:, :, 0])
    opencv_hist_time = time.time() - old_time

    performance = my_hist_time / opencv_hist_time
    assert performance < 1

def test_YCbCr_performance():
    my_YCbCr = opencv_YCbCr = cv2.imread(filename)

    old_time = time.time()
    my_YCbCr = myHist.YCbCrtoRGB(my_YCbCr)
    my_YCbCr_time = time.time() - old_time

    old_time = time.time()
    opencv_YCbCr = cv2.cvtColor(opencv_YCbCr, cv2.COLOR_YCrCb2BGR)
    opencv_YCbCr_time = time.time() - old_time

    performance = my_YCbCr_time / opencv_YCbCr_time
    assert performance < 1

# def test_RGBtoYCbCr():
#     img = cv2.imread(filename)
#     print(type(img))

#     myHist_output = myHist.RGBtoYCbCr(img)
#     openCV_output = cv2.cvtColor(img, cv2.COLOR_BGR2YCrCb)

#     diff = myHist_output - openCV_output
#     count = np.count_nonzero(diff)

#     assert count == 0

# def test_YCbCrtoRGB():
#     img = cv2.imread(filename)
#     ycbcr = cv2.cvtColor(img, cv2.COLOR_BGR2YCrCb)

#     my_RGB_output = myHist.YCbCrtoRGB(ycbcr)
#     openCV_RGB_output = cv2.cvtColor(ycbcr, cv2.COLOR_YCrCb2BGR)

#     cv2.imwrite('img/output_myRGB.jpg', my_RGB_output)
#     cv2.imwrite('img/output_openCV_RGB.jpg', openCV_RGB_output)

#     diff = my_RGB_output - openCV_RGB_output
#     count = np.count_nonzero(diff)
#     assert count == 0
