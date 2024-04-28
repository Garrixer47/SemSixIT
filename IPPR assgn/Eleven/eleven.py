import cv2

# Load the image
image = cv2.imread('input_image.jpg')

# Function to rotate image clockwise by 90 degrees
def rotate_clockwise(image):
    # Get image height and width
    height, width = image.shape[:2]
    # Rotate the image
    rotated_image = cv2.rotate(image, cv2.ROTATE_90_CLOCKWISE)
    return rotated_image

# Function to rotate image anti-clockwise by 90 degrees
def rotate_anticlockwise(image):
    # Get image height and width
    height, width = image.shape[:2]
    # Rotate the image
    rotated_image = cv2.rotate(image, cv2.ROTATE_90_COUNTERCLOCKWISE)
    return rotated_image

# Rotate image clockwise by 90 degrees
clockwise_rotated_image = rotate_clockwise(image)

# Rotate image anti-clockwise by 90 degrees
anticlockwise_rotated_image = rotate_anticlockwise(image)

# Save the rotated images
cv2.imwrite('clockwise_rotated_image.jpg', clockwise_rotated_image)
cv2.imwrite('anticlockwise_rotated_image.jpg', anticlockwise_rotated_image)

# Display the rotated images
cv2.imshow('Clockwise Rotated Image', clockwise_rotated_image)
cv2.imshow('Anti-clockwise Rotated Image', anticlockwise_rotated_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
