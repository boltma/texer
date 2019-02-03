import sys
import requests


def tex2img(formula):
    tmp = 'tmp.png'
    r = requests.get(r'http://latex.codecogs.com/png.latex?\dpi{300} \huge %s' % formula)
    f = open(tmp, 'wb')
    f.write(r.content)
    f.close()


if __name__ == "__main__":
    tex2img(sys.argv[1])
