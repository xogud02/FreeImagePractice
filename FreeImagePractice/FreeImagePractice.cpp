#include <iostream>
#include <filesystem>
#include <FreeImagePlus.h>
#include <cassert>

using namespace std;
using namespace filesystem;

bool isSameColor(const RGBQUAD& c1, const RGBQUAD& c2) {
	return c1.rgbRed == c2.rgbRed && c1.rgbGreen == c2.rgbGreen && c1.rgbBlue == c2.rgbBlue;
}

bool isEmpty(const fipImage& image) {
	fipImage tmp(image);
	if (!tmp.convertTo32Bits()) {
		cout << "convert failed ";
		return true;
	}

	RGBQUAD original;
	if (!tmp.getPixelColor(0, 0, &original)) {
		cout << "getPixelColor failed ";
		return true;
	}
	

	RGBQUAD test;
	
	auto width = image.getWidth(), height = image.getHeight();
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			tmp.getPixelColor(x, y, &test);
			if (!isSameColor(original, test)) {
				return false;
			}
		}
	}

	return true;
}

int main() {
	constexpr int unitInPixel = 16;
	string monsters = "C:\\Users\\xogud02\\Desktop\\Monsters";
	path src(monsters);
	path dest = src.parent_path() / "Monsters2";
	create_directory(dest);
	directory_iterator itr(src);
	while (itr != end(itr)) {
		fipImage spriteSheet;
		auto spriteSheetPath = itr->path();
		spriteSheet.load(spriteSheetPath.string().c_str());
		auto splitedSpritesDirectory = dest / spriteSheetPath.filename();
		create_directory(splitedSpritesDirectory);
		int i = 0;
		cout << "sprite sheet " << spriteSheetPath.filename() << " opened" << endl;
		for (int y = 0; y < spriteSheet.getHeight(); y += unitInPixel) {
			for (int x = 0; x < spriteSheet.getWidth(); x += unitInPixel) {
				fipImage sprite;

				spriteSheet.copySubImage(sprite, x, y, x + unitInPixel, y + unitInPixel);

				if (isEmpty(sprite)) {
					cout << "empty at " << spriteSheetPath.filename() << " at (" << x <<','<<y<<')'<< endl;
					continue;
				}

				auto spritePath = splitedSpritesDirectory / (to_string(i++) + ".png");
				sprite.save(spritePath.string().c_str());
			}
		}

		++itr;
	}

}
