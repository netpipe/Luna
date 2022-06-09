	#1st one
import csv
def loadCsv(filename): 
    lines = csv.reader(open(filename, "rt")) 
    dataset = list(lines) 
    for i in range(len(dataset)): 
        dataset[i] = dataset[i] 
    return dataset

attributes = ['Sky','Temp','Humidity','Wind','Water','Forecast'] 
print(attributes) 
num_attributes = len(attributes)

filename = "pg1.csv" 
dataset = loadCsv(filename) 
print(dataset)

target=['Yes','Yes','No','Yes'] 
print(target)
hypothesis=['0'] * num_attributes
print(hypothesis)

print("The Hypothesis are") 
for i in range(len(target)): 
     if(target[i] == 'Yes'):        
         for j in range(num_attributes): 
              if(hypothesis[j]=='0'):               
                  hypothesis[j] = dataset[i][j]
              if(hypothesis[j]!= dataset[i][j]):              
                   hypothesis[j]='?'
     print(i+1,'=',hypothesis)
print("Final Hypothesis") 
print(hypothesis)



#2nd one

import numpy as np
import pandas as pd
data = pd.DataFrame(data=pd.read_csv('pg2.csv'))
concepts = np.array(data.iloc[:,0:-1])
target = np.array(data.iloc[:,-1])
def learn(concepts, target):
    specific_h = concepts[0].copy()
    print("initialization of specific_h and general_h")
    print(specific_h)
    general_h = [["?" for i in range(len(specific_h))] for i in range(len(specific_h))]
    print(general_h)
    for i, h in enumerate(concepts):
        if target[i] == "Yes":
            for x in range(len(specific_h)):
                if h[x] != specific_h[x]:
                    specific_h[x] = '?'
                    general_h[x][x] = '?'
        if target[i] == "No":
            for x in range(len(specific_h)):
                if h[x] != specific_h[x]:
                    general_h[x][x] = specific_h[x]
                else:
                    general_h[x][x] = '?'
        print(" steps of Candidate Elimination Algorithm",i+1)
        print(specific_h)
        print(general_h)
    indices = [i for i, val in enumerate(general_h) if val == ['?', '?', '?', '?', '?', '?']]
    for i in indices:
        general_h.remove(['?', '?', '?', '?', '?', '?'])
    return specific_h, general_h
s_final, g_final = learn(concepts, target)
print("Final Specific_h:", s_final, sep="\n")
print("Final General_h:", g_final, sep="\n")


#3rd one
import pandas as pd
import math

class Node:
	def __init__(self,l):
		self.label=l
		self.branches = {}
	
def entropy(data):
	total_ex = len(data)
	positive_ex = len(data.loc[data["Play Tennis"] == 'Y'])
	negative_ex = len(data.loc[data["Play Tennis"] == 'N'])
	entropy = 0
	if(positive_ex > 0):
		entropy = (-1)*(positive_ex/float(total_ex))*(math.log(positive_ex,2)-math.log(total_ex,2))
	if(negative_ex > 0):
		entropy += (-1)*(negative_ex/float(total_ex))*(math.log(negative_ex,2)-math.log(total_ex,2))
	return entropy

def gain(s,data,attrib):
	values = set(data[attrib])
	print(values)
	gain = s
	for val in values:
		gain -= len(data.loc[data[attrib] == val])/float(len(data))*entropy(data.loc[data[attrib] == val])
	return gain

def get_attrib(data):
	entropy_s = entropy(data)
	attribute =""
	max_gain = 0
	for attr in data.columns[:len(data.columns)-1]:
		g = gain(entropy_s,data,attr)

		if g > max_gain:
			max_gain = g
			attribute = attr

	return attribute

def decision_tree(data):
	
	root = Node("NULL")

	if(entropy(data) == 0):
		if(len(data.loc[data[data.columns[-1]] == 'Y']) == len(data)):
			root.label = "Y"
			return root
		else:
			root.label = "N"
			return root

	if(len(data.columns) == 1):
		return
	else:
		attrib = get_attrib(data)
		root.label = attrib
		values = set(data[attrib])
	
		for val in values:
			root.branches[val] = decision_tree(data.loc[data[attrib] == val].drop(attrib,axis = 1))
		return root	

def get_rules(root,rule,rules):
	if not root.branches:
		rules.append(rule[:-2]+" => "+root.label)
		return rules

	for i in root.branches:
		get_rules(root.branches[i],rule+root.label+"="+i+" ^ ",rules)
	return rules

def test(tree,test_str):
	if not tree.branches:
		return tree.label
	return test(tree.branches[test_str[tree.label]],test_str)


data = pd.read_csv('pg3.csv')

entropy_s = entropy(data)

attrib_count = 0
cols = len(data.columns)-1

tree = decision_tree(data)

rules = get_rules(tree,"",[])
print(rules)

test_str = {}
print("Enter test case input")
for i in data.columns[:-1]:
	test_str[i] = input(i+": ")
print(test_str)
print(test(tree,test_str))



#4th one

import numpy as np
X = np.array(([2, 9], [1, 5], [3, 6]), dtype=float)
y = np.array(([92], [86], [89]), dtype=float)
X = X/np.amax(X,axis=0)
y = y/100


def sigmoid (x):
    return (1/(1 + np.exp(-x)))

def derivatives_sigmoid(x):
    return x * (1 - x)


epoch=7000 
lr=0.2 
inputlayer_neurons = 2
hiddenlayer_neurons = 3
output_neurons = 1 
wh=np.random.uniform(size=(inputlayer_neurons,hiddenlayer_neurons))
bh=np.random.uniform(size=(1,hiddenlayer_neurons))
wout=np.random.uniform(size=(hiddenlayer_neurons,output_neurons))
bout=np.random.uniform(size=(1,output_neurons))


for i in range(epoch):
    hinp=np.dot(X,wh)+bh  
    hlayer_act = sigmoid(hinp)
    outinp=np.dot(hlayer_act,wout)+bout
    output = sigmoid(outinp)



EO = y-output   
outgrad = derivatives_sigmoid(output)
d_output = EO* outgrad


EH = d_output.dot(wout.T)    
hiddengrad = derivatives_sigmoid(hlayer_act)


d_hiddenlayer = EH * hiddengrad
wout += hlayer_act.T.dot(d_output) *lr
wh += X.T.dot(d_hiddenlayer) *lr

print("Input: \n" + str(X))
print("Actual Output: \n" + str(y))
print("Predicted Output: \n" ,output)



    
#5th one

import csv
import math
import random

def loadCsv(filename):
	lines = csv.reader(open(filename, "r"))
	dataset = list(lines)
	for i in range(len(dataset)):
		dataset[i] = [float(x) for x in dataset[i]]
	return dataset


def splitDataset(dataset, splitRatio):
	trainSize = int(len(dataset) * splitRatio)
	trainSet = []
	copy = list(dataset)
	while len(trainSet) < trainSize:
		index = random.randrange(len(copy))
		trainSet.append(copy.pop(index))
	return [trainSet, copy]

def separateByClass(dataset):
	separated = {}
	for i in range(len(dataset)):
		vector = dataset[i]
		if (vector[-1] not in separated):
			separated[vector[-1]] = []
		separated[vector[-1]].append(vector)
	return separated



def mean(numbers):
	return sum(numbers)/float(len(numbers))

def stdev(numbers):
	avg = mean(numbers)
	variance = sum([pow(x-avg,2) for x in numbers])/float(len(numbers)-1)
	return math.sqrt(variance)


def summarize(dataset):
	summaries = [(mean(attribute), stdev(attribute)) for attribute in zip(*dataset)]
	del summaries[-1]
	return summaries


def summarizeByClass(dataset):
	separated = separateByClass(dataset)
	summaries = {}
	for classValue, instances in separated.items():
		summaries[classValue] = summarize(instances)
	return summaries


def calculateProbability(x, mean, stdev):
	exponent = math.exp(-(math.pow(x-mean,2)/(2*math.pow(stdev,2))))
	return (1/(math.sqrt(2*math.pi)*stdev))*exponent

def calculateClassProbabilities(summaries, inputVector):
	probabilities = {}
	for classValue, classSummaries in summaries.items():
		probabilities[classValue] = 1
		for i in range(len(classSummaries)):
			mean, stdev = classSummaries[i]
			x = inputVector[i]
			probabilities[classValue] *= calculateProbability(x, mean, stdev)
		return probabilities

def predict(summaries, inputVector):
	probabilities = calculateClassProbabilities(summaries, inputVector)
	bestLabel, bestProb = None, -1
	for classValue, probability in probabilities.items():
		if bestLabel is None or probability > bestProb:
			bestProb = probability
			bestLabel = classValue
	return bestLabel

def getPredictions(summaries, testSet):
	predictions = []
	for i in range(len(testSet)):
		result = predict(summaries, testSet[i])
		predictions.append(result)
	return predictions
def getAccuracy(testSet, predictions):
	correct = 0
	for x in range(len(testSet)):
		if testSet[x][-1] == predictions[x]:
			correct += 1
	return (correct/float(len(testSet)))*100.0

def main():
	filename = 'pg5.csv'
	splitRatio = 0.68
	dataset = loadCsv(filename)
	trainingSet, testSet = splitDataset(dataset, splitRatio)
	print('Split {0} rows into train = {1} and test = {2} rows'.format(len(dataset),len(trainingSet),len(testSet)))
	
	summaries = summarizeByClass(trainingSet)
	
	predictions = getPredictions(summaries, testSet)
	accuracy = getAccuracy(testSet, predictions)
	print('Accuracy: {0}%'.format(accuracy))

main()



#6th one
from sklearn.datasets import fetch_20newsgroups 
from sklearn.metrics import confusion_matrix 
from sklearn.metrics import classification_report 
import numpy as np
import os
categories=['alt.atheism','soc.religion.christian','comp.graphics','sci.med']
twenty_train=fetch_20newsgroups(subset='train',categories=categories,shuffle=True)
twenty_test=fetch_20newsgroups(subset='test',categories=categories,shuffle=True)
print("Number of Training Examples: ",len(twenty_train.data))
print("Number of Test Examples: ",len(twenty_test.data))
print(twenty_train.target_names)

from sklearn.feature_extraction.text import CountVectorizer
count_vect=CountVectorizer()
X_train_tf=count_vect.fit_transform(twenty_train.data)
from sklearn.feature_extraction.text import TfidfTransformer
tfidf_transformer=TfidfTransformer()
X_train_tfidf=tfidf_transformer.fit_transform(X_train_tf)
X_train_tfidf.shape

from sklearn.naive_bayes import MultinomialNB
from sklearn.metrics import accuracy_score
from sklearn import metrics
mod=MultinomialNB()
mod.fit(X_train_tfidf,twenty_train.target)
X_test_tf=count_vect.transform(twenty_test.data)
X_test_tfidf=tfidf_transformer.transform(X_test_tf)
predicted=mod.predict(X_test_tfidf)

print("Accuracy: ",accuracy_score(twenty_test.target,predicted))
print(classification_report(twenty_test.target,predicted,target_names=twenty_test.target_names))
print("Confusion matrix \n",metrics.confusion_matrix(twenty_test.target,predicted))





#7th one
import numpy as np
import pandas as pd
import csv
from pgmpy.estimators import MaximumLikelihoodEstimator
from pgmpy.models import BayesianModel
from pgmpy.inference import VariableElimination
['age','sex','cp','trestbps','chol','fbs','restecg','thalach','exang','oldpeak',
'slope','ca','thal','heartdisease']

heartDisease = pd.read_csv('pg7.csv')

heartDisease = heartDisease.replace("?",np.nan)

print("Few examples from dataset are given below")
print(heartDisease.head())
print("Attributes and data types")
print(heartDisease.dtypes)

model = BayesianModel([('age','trestbps'),('age','fbs'),('sex','trestbps'),
('sex','trestbps'),('exang','trestbps'),('trestbps','heartdisease'),
('fbs','heartdisease'),('heartdisease','restecg'),('heartdisease','thalach'),
('heartdisease','chol')])

print("Learning CPDs using maximum likelihood estimators...")
model.fit(heartDisease,estimator=MaximumLikelihoodEstimator)

print("\nInferencing the bayesian network:")
HeartDisease_infer = VariableElimination(model)

print("\n1.Probability of heart disease given age=28")
q = HeartDisease_infer.query(variables=['heartdisease'],evidence={'age':28})
print(q)
print("\n2.Probability of heart disease given chol(cholestrol)=100")
q = HeartDisease_infer.query(variables=['heartdisease'],evidence={'chol':130})
print(q)


#8th one
import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.cluster import KMeans
import pandas as pd
import numpy as np
from sklearn import preprocessing
from sklearn.mixture import GaussianMixture 

iris = datasets.load_iris()
X = pd.DataFrame(iris.data)
X.columns = ['Sepal_Length', 'Sepal_Width', 'Petal_Length', 'Petal_Width']
X_norm = preprocessing.normalize(X)
y = pd.DataFrame(iris.target)
y.columns = ['Targets']

# K-Means Model

model = KMeans(n_clusters = 3)
model.fit(X_norm)

#gmm = GMM(n_components = 3) # Used for older versions of sklearn
gmm = GaussianMixture(n_components = 3)
gmm.fit(X_norm)
gmm_y = gmm.predict(X_norm)
plt.figure(figsize = (10, 10))
colormap = np.array(['red', 'lime', 'black'])

# Real Clusters
plt.subplot(2, 2, 1)
plt.scatter(X.Petal_Length, X.Petal_Width, c = colormap[y.Targets.values], s = 100)
plt.title('Real Clusters')
plt.xlabel('Petal Lenght')
plt.ylabel('Petal Width')

# K-Means Output
plt.subplot(2, 2, 2)
plt.scatter(X.Petal_Length, X.Petal_Width, c = colormap[model.labels_], s = 100)
plt.title('K-Means Clustering')
plt.xlabel('Petal Length')
plt.ylabel('Petal Width')

# EM Output
plt.subplot(2, 2, 3)
plt.scatter(X.Petal_Length, X.Petal_Width, c = colormap[gmm_y], s = 300)
plt.title('GMM Clustering')
plt.xlabel('Petal Length')
plt.ylabel('Petal Width')
plt.show()




#9th one

import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split 
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report, confusion_matrix
from sklearn import metrics

names = ['sepal-length', 'sepal-width', 'petal-length', 'petal-width', 'class']
dataset = pd.read_csv("pg9.csv", names = names)
print(dataset.head())

x = dataset.iloc[:, :-1].values 
y = dataset.iloc[:,4].values

x_train, x_test, y_train, y_test = train_test_split(x, y, test_size =20 )

scaler = StandardScaler()
scaler.fit(x_train)

x_train = scaler.transform(x_train)
x_test = scaler.transform(x_test)

classifier = KNeighborsClassifier(n_neighbors = 5)
classifier.fit(x_train, y_train)

y_pred = classifier.predict(x_test)

for i in range(len(y_pred)):
    print ("Training Example : ")
    print(x_test[i])
    print ("Actual Label : ")
    print(y_test[i])
    print ("Predicted Label : ")
    print (y_pred[i])
    print ("--------------------------------------------")
    
print ("Confusion Matrix : ")
print(confusion_matrix(y_test, y_pred))
print ("")
print(metrics.accuracy_score(y_test, y_pred)*100)
print ("Classification Report : ")
print(classification_report(y_test, y_pred))



#10th one

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def kernel(point,xmat, k):
    m,n = np.shape(xmat)
    
    weights = np.mat(np.eye((m))) 
    for j in range(m):
        diff = point - X[j]
        weights[j,j] = np.exp(diff*diff.T/(-2.0*k**2))
    return weights

def localWeight(point,xmat,ymat,k):
    wei = kernel(point,xmat,k)
    W = (X.T*(wei*X)).I*(X.T*(wei*ymat.T))
    return W

def localWeightRegression(xmat,ymat,k):
    m,n = np.shape(xmat)

    ypred = np.zeros(m)

    for i in range(m):
        ypred[i] = xmat[i]*localWeight(xmat[i],xmat,ymat,k)
    return ypred

def graphPlot(X,ypred):
    sortindex = X[:,1].argsort(0) 
    xsort = X[sortindex][:,0]
    fig = plt.figure()
    ax = fig.add_subplot(1,1,1)
    ax.scatter(bill,tip, color='green')
    ax.plot(xsort[:,1],ypred[sortindex], color = 'red', linewidth=5)
    plt.xlabel('Total bill')
    plt.ylabel('Tip')
    plt.show()


data = pd.read_csv('pg10.csv')
bill = np.array(data.total_bill)
tip = np.array(data.tip)

mbill = np.mat(bill)

mtip = np.mat(tip)
m= np.shape(mbill)[1]

one = np.mat(np.ones(m))

X = np.hstack((one.T,mbill.T))
ypred = localWeightRegression(X,mtip,0.8) 
graphPlot(X,ypred)

