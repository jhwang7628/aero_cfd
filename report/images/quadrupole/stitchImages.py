from PIL import Image 
import glob 
import math

listing = sorted(glob.glob('*sequence*.png'))

images = map(Image.open, listing)

cols = 5
rows = math.ceil(len(listing)/cols)

for ii in range(0,len(images)): 
    images[ii] = images[ii].crop( (240, 120, 840, 480) )

w = images[0].size[0]*cols
h = images[0].size[1]*rows

result = Image.new("RGBA", (int(w), int(h)))

x=0
y=0
count=0

for i in images: 
    if (count % cols == 0):
        print("ii=%u" %(count))

    print('%u %u' %(i.size[0], i.size[1]));
    result.paste(i, (x,y))
    count+=1
    if (count % cols == 0): 
        y+=i.size[1]
        x =0
    else: 
        x+=i.size[0]


result.save("./concatHead_opt.png", "PNG",optimize=True,quality=85)
