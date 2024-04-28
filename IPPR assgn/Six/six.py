import cv2
import numpy as np

def canny_edge_detection(image_path, output_path, low_threshold=100, high_threshold=200):
    # Read the RGB image
    image = cv2.imread(image_path)

    if image is None:
        raise FileNotFoundError("Image not found")

    # Convert the RGB image to grayscale
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Apply Gaussian blur to the grayscale image to reduce noise
    blurred_image = cv2.GaussianBlur(gray_image, (5, 5), 1.5)

    # Apply the Canny edge detection algorithm
    edges = cv2.Canny(blurred_image, low_threshold, high_threshold)

    # Save the edge-detected image
    cv2.imwrite(output_path, edges)

    print(f"Edge-detected image saved to {output_path}")

# Example usage
image_path = 'input_rgb_image.jpg'  # Path to the input 24-bit RGB image
output_path = 'canny_edges.jpg'  # Path to save the edge-detected image

# You can adjust the low and high threshold values as needed
low_threshold = 100
high_threshold = 200

canny_edge_detection(image_path, output_path, low_threshold, high_threshold)
