import numpy as np
import cv2
import time
import myHist

filename = 'img/berry.jpg'
img = cv2.imread(filename)
ycbcr = cv2.cvtColor(img, cv2.COLOR_BGR2YCrCb)

# compare the performance of myHist.histEq() and cv2.equalizeHist()
start = time.time()
myHist_output = myHist.histEq(ycbcr[:, :, 0])
myHist_time = (time.time() - start) * 1000
print(f'myHist.histEq() takes {myHist_time:.3f}ms')

start = time.time()
openCV_output = cv2.equalizeHist(ycbcr[:, :, 0])
openCV_time = (time.time() - start) * 1000
print(f'cv2.equalizeHist() takes {openCV_time:.3f} ms')

# print the speedup of myHist.histEq()
print(f'myHist.histEq() is {openCV_time / myHist_time:.3f}X faster than cv2.equalizeHist()')

ycbcr[:, :, 0] = cv2.equalizeHist(ycbcr[:, :, 0])
img[:, :, 0] = cv2.equalizeHist(img[:, :, 0])
result = cv2.cvtColor(ycbcr, cv2.COLOR_YCrCb2BGR)

cv2.imwrite('output/origin.jpg', img)
cv2.imwrite('output/hist.jpg', result)