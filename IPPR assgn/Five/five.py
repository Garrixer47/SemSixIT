import cv2
import numpy as np

def prewitt_edge_detection(image_path, output_path, threshold=100):
    # Read the RGB image
    image = cv2.imread(image_path)

    if image is None:
        raise FileNotFoundError("Image not found")

    # Convert the RGB image to grayscale
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Define the Prewitt kernels for x and y directions
    prewitt_kernel_x = np.array([[1, 0, -1],
                                [1, 0, -1],
                                [1, 0, -1]])

    prewitt_kernel_y = np.array([[1, 1, 1],
                                [0, 0, 0],
                                [-1, -1, -1]])

    # Apply the Prewitt operator using convolution
    prewitt_x = cv2.filter2D(gray_image, -1, prewitt_kernel_x)
    prewitt_y = cv2.filter2D(gray_image, -1, prewitt_kernel_y)

    # Compute the magnitude of the gradients
    prewitt_magnitude = np.sqrt(prewitt_x ** 2 + prewitt_y ** 2)

    # Normalize the magnitude to range 0-255
    prewitt_magnitude = np.uint8((prewitt_magnitude / np.max(prewitt_magnitude)) * 255)

    # Apply a threshold to create a binary edge map (if needed)
    _, binary_edges = cv2.threshold(prewitt_magnitude, threshold, 255, cv2.THRESH_BINARY)

    # Save the edge-detected image
    cv2.imwrite(output_path, binary_edges)

    print(f"Edge-detected image saved to {output_path}")

# Example usage
image_path = 'input_rgb_image.jpg'  # Path to the input 24-bit RGB image
output_path = 'prewitt_edges.jpg'  # Path to save the edge-detected image

prewitt_edge_detection(image_path, output_path)
