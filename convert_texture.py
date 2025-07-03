from PIL import Image
import sys

# Output resolution
OUTPUT_SIZE = (1024, 1024)  # or change as needed

def save_color_map(image_path, output_path):
	img = Image.open(image_path).convert("RGB").resize(OUTPUT_SIZE, Image.LANCZOS)
	pixels = list(img.getdata())

	with open(output_path, "w") as f:
		for y in range(OUTPUT_SIZE[1]):
			line = []
			for x in range(OUTPUT_SIZE[0]):
				r, g, b = pixels[y * OUTPUT_SIZE[0] + x]
				line.append(f"{r},{g},{b}")
			f.write(" ".join(line) + "\n")


def save_bump_map(image_path, output_path):
	img = Image.open(image_path).convert("L").resize(OUTPUT_SIZE, Image.LANCZOS)
	pixels = list(img.getdata())

	with open(output_path, "w") as f:
		for y in range(OUTPUT_SIZE[1]):
			line = []
			for x in range(OUTPUT_SIZE[0]):
				val = pixels[y * OUTPUT_SIZE[0] + x]
				line.append(str(val))
			f.write(" ".join(line) + "\n")


if __name__ == "__main__":
	if len(sys.argv) < 3:
		print("Usage: python convert_texture.py <color_image> <output_basename> [<bump_image>]")
		sys.exit(1)

	color_img_path = sys.argv[1]
	output_base = sys.argv[2]
	bump_img_path = sys.argv[3] if len(sys.argv) > 3 else None

	save_color_map(color_img_path, f"{output_base}.ppm")
	if bump_img_path:
		save_bump_map(bump_img_path, f"{output_base}.pgm")

	print("✅ Conversion complete.")
