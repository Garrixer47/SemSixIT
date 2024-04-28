import cv2

# Load the two grayscale images
image1 = cv2.imread('input_image1.jpg', cv2.IMREAD_GRAYSCALE)
image2 = cv2.imread('input_image2.jpg', cv2.IMREAD_GRAYSCALE)

# Check if the images have the same dimensions
if image1.shape != image2.shape:
    print("Error: Images must have the same dimensions.")
    exit()

# Perform addition of the two images
addition_result = cv2.add(image1, image2)

# Perform subtraction of the two images
subtraction_result = cv2.subtract(image1, image2)

# Save the result images
cv2.imwrite('addition_result.jpg', addition_result)
cv2.imwrite('subtraction_result.jpg', subtraction_result)

# Display the result images
cv2.imshow('Addition Result', addition_result)
cv2.imshow('Subtraction Result', subtraction_result)
cv2.waitKey(0)
cv2.destroyAllWindows()

