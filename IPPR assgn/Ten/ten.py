import cv2
import numpy as np

def translate_image(image_path, shift_x, shift_y):
    # Read the RGB image
    image = cv2.imread(image_path)
    
    if image is None:
        raise FileNotFoundError("Image not found")

    # Get the dimensions of the image
    height, width = image.shape[:2]

    # Create a transformation matrix for translation
    # The matrix format is: [1, 0, shift_x; 0, 1, shift_y]
    translation_matrix = np.float32([[1, 0, shift_x], [0, 1, shift_y]])

    # Perform the translation using the transformation matrix
    translated_image = cv2.warpAffine(image, translation_matrix, (width, height))
    
    # Return the translated image
    return translated_image

def save_translated_image(image_path, shift_x, shift_y):
    # Translate the image
    translated_image = translate_image(image_path, shift_x, shift_y)
    
    # Generate the output file path
    output_path = f'translated_image_{shift_x}_{shift_y}.jpg'
    
    # Save the translated image
    cv2.imwrite(output_path, translated_image)
    
    print(f"Image shifted to right by {shift_x} units and downwards by {shift_y} units saved to {output_path}")

# Example usage
image_path = 'input_rgb_image.jpg'  # Path to the input 24-bit RGB image
shift_x = 20  # Shift image to the right by 20 units
shift_y = 10  # Shift image downwards by 10 units

save_translated_image(image_path, shift_x, shift_y)
