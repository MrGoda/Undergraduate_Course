## Package import
import pandas as pd
from lightgbm import LGBMClassifier
from sklearn.model_selection import GridSearchCV
from sklearn.model_selection import train_test_split


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    x_col = ['Rev', 'GP', 'SGA', 'OE', 'OI', 'EBT', 'NI', 'EPS', 'DEPS', 'WOS', 'GM',
             'OM', 'EBITDA', 'EBIT', 'CI', 'PPM', 'NPM', 'CCE', 'PPE', 'TA', 'TL',
             'RE', 'SE', 'DDA', 'OCF', 'CapEx', 'ICF', 'FinCF', 'NCF', 'FCF', 'AT',
             'QIR', 'TAV', 'GPG', 'OIG', 'OCFG']
    # Fill missing values
    data_file = 'dataTotal.csv'
    clean_data = pd.read_csv(data_file)
    stock_name = clean_data['Stock']
    del clean_data['Unnamed: 0']
    Y = clean_data['Class']

    x_train, x_test, y_train, y_test = train_test_split(clean_data, Y, test_size=0.33)

    clf = LGBMClassifier(boosting_type='gbdt', learning_rate=0.1,
                         subsample_for_bin=200000, objective=None, class_weight=None,
                         min_child_weight=0.001, subsample=1.0, subsample_freq=0,
                         colsample_bytree=1.0, reg_alpha=0.0, reg_lambda=0.0, random_state=None, n_jobs=- 1,
                         importance_type='split')


    params_grid = {'num_leaves': [30],
                   'max_depth': [2, 3, 5, 10, 50],
                   'n_estimators': [2, 3, 5, 10, 50],
                   'min_split_gain': [0.0, 0.01]}

    GridCV = GridSearchCV(estimator=clf, param_grid=params_grid, scoring='f1', cv=None)

    GridCV.fit(x_train[x_col], y_train)
    print("The best set of hyperparameters are: ")
    print(GridCV.best_estimator_)
    res = pd.Series(GridCV.predict(x_test[x_col]), index=x_test.index, name='pred')
    corr = pd.concat([y_test, res], axis=1)
    sum = corr[corr['Class'] == corr['pred']]
    print('Accuracy is: ' + str(len(sum) / len(corr)))

    clean_data2 = pd.get_dummies(clean_data[x_col + ['Sector']])
    x_train2, x_test2, y_train2, y_test2 = train_test_split(clean_data2, Y, test_size=0.33)
    GridCV.fit(x_train2, y_train2)
    res = pd.Series(GridCV.predict(x_test2), index=x_test2.index, name='pred')
    corr2 = pd.concat([y_test2, res], axis=1)
    sum2 = corr2[corr2['Class'] == corr2['pred']]
    print('Accuracy is: ' + str(len(sum2) / len(corr2)))

