#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

matsel = sys.argv[1] if len(sys.argv) > 1 else 4

print('\n\n#material')
print({
        'white': 'images/white.png  images/grey70.png  12.0',
        'black': 'images/black.png  images/grey55.png  12.0',
        'grey30': 'images/grey30.png  images/grey55.png  12.0',
        'grey55': 'images/grey55.png  images/grey55.png  12.0',
        'grey70': 'images/grey70.png  images/grey55.png  12.0',
        'wall': 'images/wall.jpg  images/wall.jpg  12.0',
        'container': 'images/container.png  images/container.png  12.0',
        'container2': 'images/container.png  images/container2_specular.png  32.0',
}[matsel])
print('\n\n#end')
