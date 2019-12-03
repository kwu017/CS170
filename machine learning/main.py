#[libraries]
from array import *
import numpy as np
import csv
import random
import copy
import math
import os.path
from os import path

#=================================================================================#

#[nearest neighbor algorithm]
def nearest_neighbor(curr_features, fake, real):
	number = 0.0
	#distance formula
	for i in range(len(curr_features)):
		number = number + ((float(all_features[curr_features[i] - 1][real]) - float(all_features[curr_features[i] - 1][fake]))**2)
	return number	#returns the distance

#================================================================================#

#[leave one out cross validation for forward selection]
def k_fold_forward(x, j):	#passes in current set of features along with one added
	num_correct = 0
	x.append(j)	#temporarily appends j to the current set of features
	for i in range(len(all_classes)):	#big loop for comparisons
		closest = 999999999999999		#random big number for the distance <-- might need to change to infinity
		closest_index = 99999999999999	#random big number for the closest index <-- might need to change to infinity
		for k in range(len(all_classes)):
			if not(i == k):		#check only if the indexes don't match
				distance = nearest_neighbor(x, i, k)#random.uniform(1, 10)
				if distance < closest:
					closest = distance	#update closest if distance is smaller
					closest_index = k 	#update closest index because closest changed
		if all_classes[i] == all_classes[closest_index]:
			num_correct = num_correct + 1 	#only count number of correct classifications
	accuracy = num_correct/len(all_classes)	#calculating accuracy
	return accuracy

#================================================================================#

#[leave one out cross validation for backward elimination (basically same as forward but temporarily deleting instead of adding)]
def k_fold_backward(x, j):
	num_correct = 0
	x = x[x != j] 	#temporarily deleting
	for i in range(len(all_classes)):	#big loop for comparisons
		closest = 999999999999999		#random big number for the distance <-- might need to change to infinity
		closest_index = 99999999999999	#random big number for the closest index <-- might need to change to infinity
		for k in range(len(all_classes)):
			if not(i == k):		#check only if the indexes don't match
				distance = nearest_neighbor(x, i, k)#random.uniform(1, 10)
				if distance < closest:
					closest = distance	#update closest if distance is smaller
					closest_index = k 	#update closest index because closest changed
		if all_classes[i] == all_classes[closest_index]:
			num_correct = num_correct + 1	#only count number of correct classifications
	accuracy = num_correct/len(all_classes)	#calculating accuracy
	return accuracy

#==============================================================================#

#[leave one out cross validation for kim's shady algorithm]
def k_fold_kim(x, j, least_num_wrong):
	# print(str(least_num_wrong))
	num_correct = 0
	num_wrong = 0	#now keeping track of the number I get wrong
	x.append(j)
	# print(str(least_num_wrong))
	for i in range(len(all_classes)):	#big loop for comparisons
		closest = 999999999999999		#random big number for the distance <-- might need to change to infinity
		closest_index = 99999999999999	#random big number for the closest index <-- might need to change to infinity
		for k in range(len(all_classes)):
			if not(i == k):		#check only if the indexes don't match
				distance = nearest_neighbor(x, i, k)
				if distance < closest:
					closest = distance	#update closest if distance is smaller
					closest_index = k 	#update closest index because closest changed
		if all_classes[i] == all_classes[closest_index]:
			num_correct = num_correct + 1	#count number of correct classifications
		else:
			num_wrong = num_wrong + 1	#counts number of wrong classifications
			# print(str(num_wrong))
			if num_wrong >= least_num_wrong:	#if the incorrect classifications are greater than the best one
				# print("hi")
				accuracy = 0	#no need to calculate the percentage
				return (accuracy, least_num_wrong)
	least_num_wrong = num_wrong 	#woot! This has the best accuracy so far
	accuracy = num_correct/len(all_classes)	#therefore, calculate the accuracy and return
	return (accuracy, least_num_wrong)

#===============================================================================#

#[printing out accuracy with no features]
def no_features():
	print("On the level 0 of the search tree")
	print("--Considering no features")
	if all_classes.count('1.0000000e+00') > all_classes.count('2.0000000e+00'):
		accuracy = all_classes.count('1.0000000e+00')/len(all_classes)

	else:
		accuracy = all_classes.count('2.0000000e+00')/len(all_classes)

	print("accuracy: " + str(accuracy) + "\n")

#==============================================================================#

#[foward_selection search tree algorithm]
def forward_selection():
	# with open(file) as f:
	# 	reader = csv.reader(f, delimiter = ' ', skipinitialspace = True)
	# 	first_row = next(reader)
	# 	num_cols = len(first_row)
	# print(str(num_cols))
	no_features()	#prints accuracy with no features
	curr_set_features = []
	good_accuracies = []
	more_features = []
	for i in range(1, num_cols):
		print("On the " + str(i) + " level of the search tree")
		feature_to_add_at_level = 0
		best_accuracy = 0
		for j in range(1, num_cols):
			x = copy.deepcopy(curr_set_features)
			# least_num_wrong = 1000
			if j not in curr_set_features:
				print("--Considering adding the " + str(j) + " feature")
				accuracy = k_fold_forward(x, j) #random.uniform(0.0, 1.0)
				print("accuracy: " + str(accuracy))
				if accuracy > best_accuracy:
					best_accuracy = accuracy
					feature_to_add_at_level = j
		curr_set_features.append(feature_to_add_at_level)
		good_accuracies.append(best_accuracy)
		y = copy.deepcopy(curr_set_features)
		more_features.append(y)
		# print(more_features)
		maxpos = good_accuracies.index(max(good_accuracies))
		print("On level " + str(i) + " I added feature " + str(feature_to_add_at_level) + " to current set\n")
	print("The best accuracy is " + str(max(good_accuracies)))
	print("It had features " + str(more_features[maxpos]))


def backward_elimination():
	# print(str(num_cols))
	curr_set_features = np.arange(1, num_cols, 1) #has every feature pushed on curr_set_features
	good_accuracies = []
	more_features = []
	for i in range(1, num_cols):
		print("On the " + str(i) + " level of the search tree")
		feature_to_sub_at_level = 0
		best_accuracy = 0
		for j in range(1, num_cols):
			x = copy.deepcopy(curr_set_features)
			# print(x)
			if j in curr_set_features:
				print("--Considering removing the " + str(j) + " feature")
				accuracy = k_fold_backward(x, j) #random.uniform(0.0, 1.0)
				print("accuracy: " + str(accuracy))
				if accuracy > best_accuracy:
					best_accuracy = accuracy
					feature_to_sub_at_level = j
		curr_set_features = curr_set_features[curr_set_features != feature_to_sub_at_level]
		good_accuracies.append(best_accuracy)
		y = copy.deepcopy(curr_set_features)
		more_features.append(y)
		maxpos = good_accuracies.index(max(good_accuracies))
		print("On level " + str(i) + " I removed feature " + str(feature_to_sub_at_level) + " to current set\n")
	print("The best accuracy is " + str(max(good_accuracies)))
	print("It had features " + str(more_features[maxpos]))

def kims_shadey():
	no_features()
	curr_set_features = []
	good_accuracies = []
	more_features = []
	for i in range(1, num_cols):
		print("On the " + str(i) + " level of the search tree")
		feature_to_add_at_level = 0
		best_accuracy = 0
		accuracy = (0, 1000)
		for j in range(1, num_cols):
			x = copy.deepcopy(curr_set_features)
			if j not in curr_set_features:
				print("--Considering adding the " + str(j) + " feature")
				accuracy = k_fold_kim(x, j, accuracy[1])
				# print("least_num_wrong: " + str(least_num_wrong))
				print("accuracy: " + str(accuracy[0]))
				if accuracy[0] > best_accuracy:
					best_accuracy = accuracy[0]
					feature_to_add_at_level = j
		curr_set_features.append(feature_to_add_at_level)
		good_accuracies.append(best_accuracy)
		y = copy.deepcopy(curr_set_features)
		more_features.append(y)
		maxpos = good_accuracies.index(max(good_accuracies))
		print("On level " + str(i) + " I added feature " + str(feature_to_add_at_level) + " to current set\n")
	print("The best accuracy is " + str(max(good_accuracies)))
	print("It had features " + str(more_features[maxpos]))

print("Welcome to Kim's Feature Selection Algorithm!")
file = input("Type the name of the file to test: ")
while not path.exists(file):
	print("That file does not exist. Please try again.")
	file = input("Type the name of the file to test: ")

with open(file) as f:
	reader = csv.reader(f, delimiter = ' ', skipinitialspace = True)
	first_row = next(reader)
	num_cols = len(first_row)

yes = open(file, 'r')
lines = yes.readlines()
all_classes = []
for i in lines:
	all_classes.append(i.split()[0])
print(all_classes)

all_features = []
for i in range(1, num_cols):
	f = open(file,'r')
	lines = f.readlines()
	result = []
	for x in lines:
		result.append(x.split()[i])
	all_features.append(result)
f.close()

# for i in range(len(all_features)):
# 	print(all_features[i])

# f = open(file,'r')
# lines = f.readlines()
# result = []
# for x in lines:
# 	result.append(x.split(' ')[1])
# f.close()
# print(all_features[0][0])

print("Type the number of the algorithm you want to run: ")
print("	1) Forward Selection")
print("	2) Backward Elimination")
algorithm = input("	3) Kim's Special Algorithm (might be shady sorry)\n")

if (algorithm == str(1)):
	#print("will eventually do forward selection")
	forward_selection()

elif (algorithm == str(2)):
	#print("will eventually do backward elimination")
	backward_elimination()

elif (algorithm == str(3)):
	# print("will eventually do kim's shady algorithm")
	kims_shadey()

else:
	print("restart this program cuz that wasn't a real option k thx bye") 