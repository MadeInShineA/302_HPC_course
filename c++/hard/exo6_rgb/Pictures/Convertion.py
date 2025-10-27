from PIL import Image

# Function to convert PNG image to RGB and write RGB values to a text file
def convert_png_to_rgb_and_write(image_path, output_txt_path):
    # Open the image
    img = Image.open(image_path)

    # Convert the image to RGB
    rgb_img = img.convert('RGB')

    # Write RGB values to a text file
    with open(output_txt_path, 'w') as f:
        width, height = rgb_img.size
        for y in range(height):
            for x in range(width):
                r, g, b = rgb_img.getpixel((x, y))
                f.write(f"{r},{g},{b}\n")

# Example usage

for i in ["Black_Hole", "Blue_Whirl", "Brinicle", "Bubble_Simulating_Earth", "Drop_Impact_1", "Drop_Impact_2", "Fire_Tornado_1", "Fire_Tornado_2",
          "Lighting_Balls", "Magnetosphere", "Mammatus_Clouds", "Plasma_Vortex", "Plateau_Rayleigh_Instability", "Plunging_Breaking_Wave", "Quasar", "Sonoluminescence", "Tornado"]:

    convert_png_to_rgb_and_write(i+'.png',  i+'_RGB.txt')

