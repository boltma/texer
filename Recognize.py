import os
import numpy as np
from sklearn.externals import joblib
from PIL import Image


def recognize():
    model = joblib.load("my_model.m")
    cwd = os.getcwd()
    img_path = cwd + r'\\temp.png'
    img = Image.open(img_path)
    img = img.convert('L')
    img = img.resize((30, 30), Image.ANTIALIAS)
    test_x = np.array(img)
    test_x = 255 - np.reshape(test_x, (1, -1))
    label = model.predict(test_x)[0]
    return label


if __name__ == "__main__":
    print(recognize())
