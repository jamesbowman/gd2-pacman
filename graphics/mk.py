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

        def embiggen(im):
            return im.resize((80, 100), Image.NEAREST).resize((14, 18), Image.ANTIALIAS).transpose(Image.ROTATE_90)

        b = [embiggen(im) for im in ims]

        preview = Image.new("RGBA", (16 * 14, 6 * 18))
        for im,(x,y) in zip(b, [(x, y) for y in range(6) for x in range(16)]):
            preview.paste(im.transpose(Image.ROTATE_270), (14 * x, 18 * y))
        preview.convert("RGB").save("preview.png")
            
        self.load_handle("FONT2", b, gd2.ARGB4)

if __name__ == '__main__':
    Pacman().make()
