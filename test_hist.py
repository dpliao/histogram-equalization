import numpy as np
import cv2
import myHist
import pytest

def test_histEq():
    filename = 'img/image0.jpg'
    img = cv2.imread(filename, 0)

    myHist_output = myHist.histEq(img)
    openCV_output = cv2.equalizeHist(img)

    assert np.array_equal(myHist_output, openCV_output)
