import cv2
import numpy as np
import matplotlib.pyplot as plt

def plot_histograms(image_path):
    # Read the RGB image
    image = cv2.imread(image_path)

    if image is None:
        raise FileNotFoundError("Image not found")

    # Split the image into the Red, Green, and Blue channels
    blue_channel, green_channel, red_channel = cv2.split(image)

    # Compute histograms for each color channel
    blue_hist = cv2.calcHist([blue_channel], [0], None, [256], [0, 256])
    green_hist = cv2.calcHist([green_channel], [0], None, [256], [0, 256])
    red_hist = cv2.calcHist([red_channel], [0], None, [256], [0, 256])

    # Plot the histograms
    plt.figure()
    plt.title('Histograms for RGB Channels')
    plt.xlabel('Pixel Intensity')
    plt.ylabel('Frequency')

    # Plot histogram for the Blue channel
    plt.plot(blue_hist, color='blue', label='Blue Channel')

    # Plot histogram for the Green channel
    plt.plot(green_hist, color='green', label='Green Channel')

    # Plot histogram for the Red channel
    plt.plot(red_hist, color='red', label='Red Channel')

    # Add a legend
    plt.legend()

    # Show the plot
    plt.show()

# Example usage
image_path = 'input_rgb_image.jpg'  # Path to the input 24-bit RGB image
plot_histograms(image_path)
