import hid

    # //  Dactyl Manuform
    # // idVendor           0x444d 
    # // idProduct          0x3536 
vid = 0x444d
pid = 0x3536


with hid.Device(vid, pid) as h:
	print(f'Device manufacturer: {h.manufacturer}')
	print(f'Product: {h.product}')
	print(f'Serial Number: {h.serial}')
