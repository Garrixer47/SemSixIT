import cv2

# Load the grayscale image
gray_image = cv2.imread('input_image.jpg', cv2.IMREAD_GRAYSCALE)

# Threshold value
threshold_value = 128  # Adjust this value as needed (0-255)

# Apply thresholding
_, binary_image = cv2.threshold(gray_image, threshold_value, 255, cv2.THRESH_BINARY)

# Save the binary image
cv2.imwrite('binary_image.jpg', binary_image)

# Display the binary image
cv2.imshow('Binary Image', binary_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
