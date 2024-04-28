import cv2

def scale_image(image_path, scale_factor):
    # Read the RGB image
    image = cv2.imread(image_path)
    
    if image is None:
        raise FileNotFoundError("Image not found")

    # Get the dimensions of the original image
    height, width = image.shape[:2]
    
    # Calculate new dimensions based on the scale factor
    new_width = int(width * scale_factor)
    new_height = int(height * scale_factor)

    # Scale the image using the specified scale factor
    # Using interpolation method: cv2.INTER_LINEAR (bilinear interpolation)
    scaled_image = cv2.resize(image, (new_width, new_height), interpolation=cv2.INTER_LINEAR)
    
    # Return the scaled image
    return scaled_image

def save_scaled_image(image_path, scale_factors):
    # Process each scale factor
    for scale_factor in scale_factors:
        # Scale the image
        scaled_image = scale_image(image_path, scale_factor)
        
        # Generate the output file path
        output_path = f'scaled_image_{scale_factor}.jpg'
        
        # Save the scaled image
        cv2.imwrite(output_path, scaled_image)
        
        print(f"Image scaled by factor {scale_factor} saved to {output_path}")

# Example usage
image_path = 'input_rgb_image.jpg'  # Path to the input 24-bit RGB image
scale_factors = [2, 0.5]  # Scaling factors: 2 for doubling the size, 0.5 for halving the size

save_scaled_image(image_path, scale_factors)
