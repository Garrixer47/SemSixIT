import cv2

# Load the image
image = cv2.imread('input_image.jpg')

# Compression quality factor
compression_quality = 90  # Adjust this value as needed (0-100)

# Save the original image for comparison
original_image = image.copy()

# Save the original image
cv2.imwrite('original_image.jpg', original_image)

# Compress the image using JPEG
cv2.imwrite('compressed_image.jpg', image, [cv2.IMWRITE_JPEG_QUALITY, compression_quality])

# Load the compressed image
compressed_image = cv2.imread('compressed_image.jpg')

# Decompress the compressed image
decompressed_image = cv2.imread('compressed_image.jpg', cv2.IMREAD_UNCHANGED)

# Calculate PSNR (Peak Signal-to-Noise Ratio)
psnr = cv2.PSNR(original_image, decompressed_image)

# Display the original and decompressed images
cv2.imshow('Original Image', original_image)
cv2.imshow('Decompressed Image', decompressed_image)
cv2.waitKey(0)
cv2.destroyAllWindows()

print("PSNR value:", psnr)
