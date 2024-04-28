import cv2
import numpy as np

def sobel_edge_detection(image_path, output_path, threshold=100):
    # Read the RGB image
    image = cv2.imread(image_path)

    if image is None:
        raise FileNotFoundError("Image not found")

    # Convert the RGB image to grayscale
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Apply the Sobel operator in the x and y directions
    sobel_x = cv2.Sobel(gray_image, cv2.CV_64F, 1, 0, ksize=3)
    sobel_y = cv2.Sobel(gray_image, cv2.CV_64F, 0, 1, ksize=3)

    # Compute the magnitude of the gradients
    sobel_magnitude = np.sqrt(sobel_x ** 2 + sobel_y ** 2)

    # Normalize the magnitude to range 0-255
    sobel_magnitude = np.uint8((sobel_magnitude / np.max(sobel_magnitude)) * 255)

    # Apply a threshold to create a binary edge map (if needed)
    _, binary_edges = cv2.threshold(sobel_magnitude, threshold, 255, cv2.THRESH_BINARY)

    # Save the edge-detected image
    cv2.imwrite(output_path, binary_edges)

    print(f"Edge-detected image saved to {output_path}")

# Example usage
image_path = 'input_rgb_image.jpg'  # Path to the input 24-bit RGB image
output_path = 'sobel_edges.jpg'  # Path to save the edge-detected image

sobel_edge_detection(image_path, output_path)
