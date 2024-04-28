import cv2

# Load the noisy image
noisy_image = cv2.imread('input_image.jpg')

# Apply Gaussian blur to smoothen the image
smooth_image = cv2.GaussianBlur(noisy_image, (5, 5), 0)  # Adjust kernel size as needed

# Save the smooth image
cv2.imwrite('smooth_image.jpg', smooth_image)

# Display the smooth image
cv2.imshow('Smooth Image', smooth_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
