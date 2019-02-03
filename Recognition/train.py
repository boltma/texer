import numpy as np
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split
from sklearn.externals import joblib
import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from time import time

data = pd.read_csv('train.csv', header=0, dtype=np.int)
x, y = data.iloc[:, 1:], data['label']
x_train, x_valid, y_train, y_valid = train_test_split(x, y, test_size=0.2, random_state=1)
data_test = pd.read_csv('test.csv', header=0, dtype=np.int)
# model = SVC(C=1000, kernel='rbf', gamma=1e-10)
model = RandomForestClassifier(n_estimators=100, criterion='gini', min_samples_split=2, min_impurity_decrease=1e-10)
model.fit(x_train, y_train)
y_train_pred = model.predict(x_train)
print('training set accuracy: %.3f%%' % (accuracy_score(y_train, y_train_pred) * 100))
t = time()
y_valid_pred = model.predict(x_valid)
t = time() - t
print('test set accuracy: %.3f%%' % (accuracy_score(y_valid, y_valid_pred) * 100))
joblib.dump(model, "my_model.m")
