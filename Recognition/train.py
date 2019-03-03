import numpy as np
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.neural_network import MLPClassifier
from sklearn.externals import joblib
import pandas as pd


def train(classifier, symbol_only):
    name = 'train_' + str(int(symbol_only is True)) + '.csv'
    data = pd.read_csv(name, header=0, dtype=np.int)
    x, y = data.iloc[:, 1:], data['label']
    x_train, x_valid, y_train, y_valid = train_test_split(x, y, test_size=0.2, random_state=1)
    # data_test = pd.read_csv('test.csv', header=0, dtype=np.int)
    if classifier == 'RF':
        if symbol_only:
            model = RandomForestClassifier(n_estimators=100, criterion='entropy', min_samples_split=2,
                                           min_impurity_decrease=1e-7)
        else:
            model = RandomForestClassifier(n_estimators=100, criterion='entropy', min_samples_split=2,
                                           min_impurity_decrease=1e-10)
    elif classifier == 'NN':
        if symbol_only:
            model = MLPClassifier(solver='adam', alpha=1e-3, max_iter=1000, activation='logistic', verbose=True,
                                  hidden_layer_sizes=(200, 100), random_state=1)
        else:
            model = MLPClassifier(solver='adam', alpha=1e-4, max_iter=1000, activation='logistic', verbose=True,
                                  hidden_layer_sizes=(500, 200), random_state=1)
    model.fit(x_train, y_train)
    y_train_pred = model.predict(x_train)
    print('training set accuracy: %.3f%%' % (accuracy_score(y_train, y_train_pred) * 100))
    y_valid_pred = model.predict(x_valid)
    print('test set accuracy: %.3f%%' % (accuracy_score(y_valid, y_valid_pred) * 100))
    name = classifier + '_model_' + str(int(symbol_only is True)) + '.m'
    joblib.dump(model, name)


if __name__ == "__main__":
    for classifier in ['RF', 'NN']:
        for symbol_only in [True, False]:
            train(classifier, symbol_only)
