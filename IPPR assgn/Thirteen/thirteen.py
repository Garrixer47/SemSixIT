import cv2
import numpy as np

# Load the image
image = cv2.imread('input_image.jpg')

# Convert image to grayscale
gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Convert grayscale image to float32
gray_image_float32 = np.float32(gray_image)

# Perform Discrete Cosine Transform (DCT)
dct_image = cv2.dct(gray_image_float32)

# Inverse DCT to retrieve the original image
retrieved_image = cv2.idct(dct_image)

# Convert the retrieved image back to uint8
retrieved_image_uint8 = np.uint8(retrieved_image)

# Save the original image for comparison
cv2.imwrite('original_image.jpg', gray_image)

# Save the retrieved image after inverse DCT
cv2.imwrite('retrieved_image.jpg', retrieved_image_uint8)

# Calculate PSNR (Peak Signal-to-Noise Ratio)
psnr = cv2.PSNR(gray_image, retrieved_image_uint8)

# Display the original and retrieved images
cv2.imshow('Original Image', gray_image)
cv2.imshow('Retrieved Image', retrieved_image_uint8)
cv2.waitKey(0)
cv2.destroyAllWindows()

print("PSNR value:", psnr)
