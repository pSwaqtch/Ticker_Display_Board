import sys
import pyfiglet

def generate_ascii_art_and_save(characters, output_file):
    # Create a Figlet font object with the 'banner' font style
    font = pyfiglet.Figlet(font='doom')

    with open(output_file, 'w') as file:
        for char in characters:
            # Write the character to the file
            #file.write(char + '\n')
            file.write(f"'{char}'\n")

            # Generate ASCII art from the character
            ascii_art = font.renderText(char)

            # Write the ASCII art to the file
            file.write(ascii_art + '\n\n')

# Define the characters you want to include
all_characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+[{]};:'\",<.>/?\\| "

# Specify the output file
output_file = "all_ascii_art_output1.txt"

# Generate and save ASCII art for all characters
generate_ascii_art_and_save(all_characters, output_file)

print(f"ASCII art for all characters has been saved to {output_file}")
