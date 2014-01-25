import Image

import gameduino2 as gd2

class Pacman(gd2.prep.AssetBin):

    def addall(self):

        im = Image.open("graphics.png")

        ims = [None for i in range(96)]
        for y in range(6):
            for x in range(16):
                tile = im.crop((1 + 9 * x, 1 + 11 * y, 9 + 9 * x, 11 + 11 * y))
                ims[16 * y + x] = tile
        widths = [8 for i in range(128)]

        self.load_font("FONT", ims, widths, gd2.ARGB2)

if __name__ == '__main__':
    Pacman().make()
