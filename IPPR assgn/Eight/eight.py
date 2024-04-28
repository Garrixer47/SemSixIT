import cv2
import numpy as np
import matplotlib.pyplot as plt

def histogram_equalization_rgb(image_path):
    # Read the RGB image
    image = cv2.imread(image_path)

    if image is None:
        raise FileNotFoundError("Image not found")

    # Split the image into Red, Green, and Blue channels
    blue_channel, green_channel, red_channel = cv2.split(image)

    # Equalize the histogram of each color channel separately
    equalized_blue = cv2.equalizeHist(blue_channel)
    equalized_green = cv2.equalizeHist(green_channel)
    equalized_red = cv2.equalizeHist(red_channel)

    # Merge the equalized channels back into a 24-bit RGB image
    equalized_image = cv2.merge([equalized_blue, equalized_green, equalized_red])

    # Save the equalized image
    equalized_image_path = 'equalized_rgb_image.jpg'
    cv2.imwrite(equalized_image_path, equalized_image)

    # Compute histograms for original and equalized images
    def compute_histograms(image):
        blue, green, red = cv2.split(image)
        blue_hist = cv2.calcHist([blue], [0], None, [256], [0, 256])
        green_hist = cv2.calcHist([green], [0], None, [256], [0, 256])
        red_hist = cv2.calcHist([red], [0], None, [256], [0, 256])
        return blue_hist, green_hist, red_hist

    original_histograms = compute_histograms(image)
    equalized_histograms = compute_histograms(equalized_image)

    # Plot histograms
    def plot_histograms(original_histograms, equalized_histograms):
        plt.figure(figsize=(12, 8))

        # Plot histograms for the original image
        plt.subplot(2, 2, 1)
        plt.plot(original_histograms[0], color='blue')
        plt.plot(original_histograms[1], color='green')
        plt.plot(original_histograms[2], color='red')
        plt.title('Original Image Histograms')
        plt.xlabel('Pixel Intensity')
        plt.ylabel('Frequency')

        # Plot histograms for the equalized image
        plt.subplot(2, 2, 2)
        plt.plot(equalized_histograms[0], color='blue')
        plt.plot(equalized_histograms[1], color='green')
        plt.plot(equalized_histograms[2], color='red')
        plt.title('Equalized Image Histograms')
        plt.xlabel('Pixel Intensity')
        plt.ylabel('Frequency')

        plt.tight_layout()
        plt.show()

    plot_histograms(original_histograms, equalized_histograms)

    print(f"Equalized RGB image saved to {equalized_image_path}")

# Example usage
image_path = 'input_rgb_image.jpg'  # Path to the input 24-bit RGB image
histogram_equalization_rgb(image_path)
