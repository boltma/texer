from io import BytesIO
import sys
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import rcParams

rcParams['text.latex.preamble'] = r'\usepackage{amsmath}'
matplotlib.rcParams['text.usetex'] = True
matplotlib.rcParams['text.latex.unicode'] = True


def render_latex(formula, fontsize=18, dpi=300, format_='png'):
    fig = plt.figure(figsize=(0.01, 0.01))
    fig.text(0, 0, u'${}$'.format(formula), fontsize=fontsize)
    buffer_ = BytesIO()
    fig.savefig(buffer_, dpi=dpi, transparent=False,
                format=format_, bbox_inches='tight', pad_inches=0.1)
    return buffer_.getvalue()


def tex2img_offline(formula, fontsize=18, dpi=300, format_='png'):
    f = open("tmp.png", "wb")
    f.write(render_latex(formula, fontsize, dpi, format_))
    f.seek(0)
    f.close()


if __name__ == "__main__":
    tex2img_offline(sys.argv[1])
