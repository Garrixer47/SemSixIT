import cv2
import numpy as np
import pywt

# Load the image
image = cv2.imread('input_image.jpg')

# Convert image to grayscale
gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Perform Discrete Wavelet Transform (DWT)
coeffs = pywt.dwt2(gray_image, 'haar')

# Apply thresholding (optional)
coeffs_thresh = [pywt.threshold(c, 0.1 * max(c.flatten()), mode='soft') for c in coeffs]

# Reconstruct the image using inverse DWT
retrieved_image = pywt.idwt2(coeffs_thresh, 'haar')

# Convert retrieved image to uint8
retrieved_image_uint8 = np.uint8(retrieved_image)

# Save the original image for comparison
cv2.imwrite('original_image.jpg', gray_image)

# Save the retrieved image after inverse DWT
cv2.imwrite('retrieved_image.jpg', retrieved_image_uint8)

# Calculate PSNR (Peak Signal-to-Noise Ratio)
psnr = cv2.PSNR(gray_image, retrieved_image_uint8)

# Display the original and retrieved images
cv2.imshow('Original Image', gray_image)
cv2.imshow('Retrieved Image', retrieved_image_uint8)
cv2.waitKey(0)
cv2.destroyAllWindows()

print("PSNR value:", psnr)
