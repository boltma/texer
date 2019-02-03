import os
import numpy as np
from sklearn.externals import joblib
from PIL import Image

model = joblib.load("my_model.m")
cwd = r'Recognition\\data\\'
classes = os.listdir(cwd)
cwd = os.getcwd()
img_path = cwd + r'\\temp.png'
img = Image.open(img_path)
img = img.convert('L')
img = img.resize((30, 30), Image.ANTIALIAS)
test_X = np.array(img)
test_X = 255 - np.reshape(test_X, (1, -1))

label = model.predict(test_X)[0]
print(label)
