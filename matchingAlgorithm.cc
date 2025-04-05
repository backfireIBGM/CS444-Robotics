#include <stdio.h>
#include <stdlib.h>

/**
 * Extract brightness values from a black and white image.
 * 
 * @param image Pointer to image data (assumed to be 8-bit grayscale)
 * @param width Width of the image in pixels
 * @param height Height of the image in pixels
 * @param pitch Number of bytes per row (may include padding)
 * @return Dynamically allocated 2D array of brightness values (0-255)
 *         The caller is responsible for freeing this memory
 */
unsigned char** extract_brightness(unsigned char* image, int width, int height, int pitch) {
    // Allocate memory for the 2D array
    unsigned char** brightness = (unsigned char**)malloc(height * sizeof(unsigned char*));
    if (!brightness) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    
    // Allocate memory for each row and copy pixel values
    for (int y = 0; y < height; y++) {
        brightness[y] = (unsigned char*)malloc(width * sizeof(unsigned char));
        if (!brightness[y]) {
            // Clean up already allocated rows
            for (int i = 0; i < y; i++) {
                free(brightness[i]);
            }
            free(brightness);
            fprintf(stderr, "Memory allocation failed\n");
            return NULL;
        }
        
        // Copy pixel values for this row
        for (int x = 0; x < width; x++) {
            // Get pixel value from image data (handle pitch if necessary)
            brightness[y][x] = image[y * pitch + x];
        }
    }
    
    return brightness;
}

/**
 * Free the memory allocated for the brightness array
 */
void free_brightness_array(unsigned char** brightness, int height) {
    if (brightness) {
        for (int y = 0; y < height; y++) {
            if (brightness[y]) {
                free(brightness[y]);
            }
        }
        free(brightness);
    }
}

// Example usage
int main() {
    // This would typically come from loading an image file
    // For this example, we'll create a small test image
    int width = 4;
    int height = 3;
    int pitch = width; // No padding in our example
    
    // Sample 4x3 grayscale image data (values 0-255)
    unsigned char test_image[] = {
        255, 200, 150, 100,  // Row 0: white to gray gradient
        90,  80,  70,  60,   // Row 1: darker grays
        50,  30,  10,  0     // Row 2: dark gray to black
    };
    
    // Extract brightness values
    unsigned char** brightness = extract_brightness(test_image, width, height, pitch);
    if (!brightness) {
        fprintf(stderr, "Failed to extract brightness values\n");
        return 1;
    }
    
    // Print the brightness values
    printf("Brightness values:\n");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%3d ", brightness[y][x]);
        }
        printf("\n");
    }
    
    // Free the memory
    free_brightness_array(brightness, height);
    
    return 0;
}