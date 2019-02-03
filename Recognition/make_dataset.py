import os
from PIL import Image
import numpy as np
import csv


def make_dataset(flag):
    cwd = r'data\\'
    classes = os.listdir(cwd)
    f = open(flag + ".csv", "w", newline="")
    writer = csv.writer(f)
    if flag == "train":
        column_name = ["label"]
    else:
        column_name = []
    column_name.extend(["pixel%d" % i for i in range(30 * 30)])
    writer.writerow(column_name)

    for index, name in enumerate(classes):
        class_path = cwd + name + '\\'
        cnt = 0
        for img_name in os.listdir(class_path):
            if flag == "test" and cnt <= 30:
                cnt = cnt + 1
                continue
            if flag == "train" and cnt >= 30:
                break
            img_path = class_path + img_name
            img = Image.open(img_path)
            img = img.convert('L')
            img = img.resize((30, 30), Image.ANTIALIAS)
            img_raw = np.array(img)
            img_raw = 255 - np.reshape(img_raw, -1)
            if flag == "train":
                row_data = [index]
            else:
                row_data = []
            row_data.extend(img_raw)
            writer.writerow(row_data)
            cnt = cnt + 1
            if flag == "test" and cnt > 33:
                break


if __name__ == "__main__":
    make_dataset("test")
    make_dataset("train")
