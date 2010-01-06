# Copyright (c) 2008 the authors listed at the following URL, and/or
# the authors of referenced articles or incorporated external code:
# http://en.literateprograms.org/Photo_to_drawing_(Python)?action=history&offset=20070404131120
# 
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
# 
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
# 
# Retrieved from: http://en.literateprograms.org/Photo_to_drawing_(Python)?oldid=9651

import Image
import ImageFilter
import ImageOps
import ImageDraw


# TODO: Add comments in the code
def dodge(a, b, alpha):
    return min(int(a*255/(256-b*alpha)), 255)

def drawing(infile, outfile, blur=25, alpha=1.0):
    im1 = Image.open(infile).convert("L")
    im2 = im1.copy()

    im2 = ImageOps.invert(im2)

    for i in range(blur):
        im2 = im2.filter(ImageFilter.BLUR)

    width, height = im1.size
    for x in range(width):
        for y in range(height):
            a = im1.getpixel((x, y))
            b = im2.getpixel((x, y))
            im1.putpixel((x, y), dodge(a, b, alpha))

    im1.save(outfile)

# FIXME: Blue
drawing("003.jpg", "003_2.jpg")
drawing("011.jpg", "011_2.jpg")


