import cv2

def invert_color_image(image_path, output_path):
    # Read the image
    image = cv2.imread(image_path)

    if image is None:
        raise FileNotFoundError("Image not found")

    # Invert the color channels by subtracting each channel value from 255
    negative_image = 255 - image

    # Save the negative image
    cv2.imwrite(output_path, negative_image)

    print(f"Negative image saved to {output_path}")

# Example usage
image_path = 'input_color_image.jpg'  # Path to the input 24-bit color image
output_path = 'negative_color_image.jpg'  # Path to save the negative image

invert_color_image(image_path, output_path)
