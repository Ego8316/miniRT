from PIL import Image
import sys

OUTPUT_SIZE = (1024, 1024)

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
	if len(sys.argv) < 4:
		print("Usage: python3 convert_texture.py <output_basename> <color_image> <bump_image>")
		sys.exit(1)

	output_base = sys.argv[1]
	color_img_path = sys.argv[2]
	bump_img_path = sys.argv[3]

	save_color_map(color_img_path, f"{output_base}.ppm")
	if bump_img_path:
		save_bump_map(bump_img_path, f"{output_base}.pgm")

	print("✅ Conversion complete.")
