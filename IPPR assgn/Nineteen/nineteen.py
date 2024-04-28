import cv2
import numpy as np

# Load the 24-bit RGB image
image = cv2.imread('input_image.jpg')

# Define the enhancement factor for the channel you want to enhance
enhancement_factor = 1.5  # Adjust this value as needed

# Choose the color channel to enhance: 0 for Blue, 1 for Green, 2 for Red
channel_to_enhance = 2  # Enhancing the Red channel in this example

# Split the image into its color channels
b, g, r = cv2.split(image)

# Apply enhancement factor to the chosen channel
if channel_to_enhance == 0:
    enhanced_b = np.clip(b * enhancement_factor, 0, 255).astype(np.uint8)
    enhanced_image = cv2.merge((enhanced_b, g, r))
elif channel_to_enhance == 1:
    enhanced_g = np.clip(g * enhancement_factor, 0, 255).astype(np.uint8)
    enhanced_image = cv2.merge((b, enhanced_g, r))
elif channel_to_enhance == 2:
    enhanced_r = np.clip(r * enhancement_factor, 0, 255).astype(np.uint8)
    enhanced_image = cv2.merge((b, g, enhanced_r))
else:
    print("Invalid channel choice. Please choose 0 (Blue), 1 (Green), or 2 (Red).")
    exit()

# Save the enhanced image
cv2.imwrite('enhanced_image.jpg', enhanced_image)

# Display the enhanced image
cv2.imshow('Enhanced Image', enhanced_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
