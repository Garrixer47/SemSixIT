import cv2

def convert_rgb_to_cmy(image_path, output_path):
    # Read the RGB image
    image = cv2.imread(image_path)

    if image is None:
        raise FileNotFoundError("Image not found")

    # Convert RGB image to CMY by subtracting each channel value from 255
    # CMY is simply the complement of RGB
    cmy_image = 255 - image

    # Save the CMY image
    cv2.imwrite(output_path, cmy_image)

    print(f"CMY image saved to {output_path}")

# Example usage
image_path = 'input_rgb_image.jpg'  # Path to the input 24-bit RGB image
output_path = 'output_cmy_image.jpg'  # Path to save the CMY image

convert_rgb_to_cmy(image_path, output_path)
