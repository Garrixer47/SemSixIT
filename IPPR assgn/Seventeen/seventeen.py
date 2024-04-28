import cv2
import numpy as np

# Load the grayscale image
gray_image = cv2.imread('input_image.jpg', cv2.IMREAD_GRAYSCALE)

# Define intensity ranges
lower_threshold = 100
upper_threshold = 200

# Method 1: With preserving the background
def intensity_slicing_preserve_background(image, lower_thresh, upper_thresh):
    # Create a mask for the specified intensity range
    mask = cv2.inRange(image, lower_thresh, upper_thresh)
    # Apply the mask to the original image to preserve the background
    result_image = cv2.bitwise_and(image, image, mask=~mask)
    return result_image

# Method 2: Without preserving the background
def intensity_slicing_nonpreserve_background(image, lower_thresh, upper_thresh):
    # Create a mask for the specified intensity range
    mask = cv2.inRange(image, lower_thresh, upper_thresh)
    # Apply the mask to the original image without preserving the background
    result_image = cv2.bitwise_and(image, image, mask=mask)
    return result_image

# Apply intensity slicing with preserving the background
result_preserve_bg = intensity_slicing_preserve_background(gray_image, lower_threshold, upper_threshold)

# Apply intensity slicing without preserving the background
result_nonpreserve_bg = intensity_slicing_nonpreserve_background(gray_image, lower_threshold, upper_threshold)

# Save the result images
cv2.imwrite('result_preserve_bg.jpg', result_preserve_bg)
cv2.imwrite('result_nonpreserve_bg.jpg', result_nonpreserve_bg)

# Display the result images
cv2.imshow('With Preserving Background', result_preserve_bg)
cv2.imshow('Without Preserving Background', result_nonpreserve_bg)
cv2.waitKey(0)
cv2.destroyAllWindows()
