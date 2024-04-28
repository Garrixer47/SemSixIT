import cv2
import numpy as np

def invert_image(image_path, output_path):
    # Read the image
    image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)

    if image is None:
        raise FileNotFoundError("Image not found")

    # Invert the image by subtracting each pixel value from 255
    negative_image = 255 - image

    # Save the negative image
    cv2.imwrite(output_path, negative_image)

    print(f"Negative image saved to {output_path}")

# Example usage
image_path = 'input_image.jpg'  # Path to the input grayscale 8-bit image
output_path = 'negative_image.jpg'  # Path to save the negative image

invert_image(image_path, output_path)
