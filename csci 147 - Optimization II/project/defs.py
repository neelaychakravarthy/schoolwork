import random
import sys
import numpy as np
from numba import jit
import matplotlib.pyplot as plt
import math
import time

# distance between city_i and city_j
def dist(city_i,city_j):
    return math.sqrt((city_i[0]-city_j[0])**2 + (city_i[1]-city_j[1])**2)

# assuming tour is a permutation of the integers {0,...,N-1}, calculate associated tour length
def tour_length(cities,tour):
    n = len(cities)
    length = 0
    for i in range(1,n): # add dist(i-1,i)
        length += dist(cities[tour[i-1],:],cities[tour[i],:])
    return length + dist(cities[tour[0],:],cities[tour[n-1],:])

# return cities sorted by the indices specified in tour, e.g., (c0,c1,c2,c3),(0,2,1,3) --> (c0,c2,c1,c3)
def sorted_by_tour(cities,tour):
    n = len(cities)
    city_tour = np.zeros((n,2))
    for i in range(n):
        city_tour[i,:] = cities[tour[i],:]
    return city_tour

# swaps two values in arr, based on the indices specified by pair
def swap(arr,pair):
    o_i = arr[pair[0]]
    arr[pair[0]]=arr[pair[1]]
    arr[pair[1]]=o_i

# returns a uniformly random pair of distinct indices 1,...,n-1
def random_pair(n):
    i = j = np.random.randint(1,n)
    while i==j:
        j = np.random.randint(1,n)
    return i,j

# checks that no single swap improves the given tour
def is_local_opt(cities,tour):
    curr = tour_length(cities,tour)
    for i in range(1,len(cities)):
        for j in range(1,i):
            p=(i,j)
            swap(tour,p)
            if tour_length(cities,tour)<curr:
                return False
            swap(tour,p)
    return True

import random
# from multiprocessing import Process
from threading import Thread

import defs #in order for multiprocessing to work using native libraries on jupyter notebook, need to import the parallelized function from a seperate file

#given a start city, alpha and beta, and the existing pheromones, returns a tour chosen by an ant with the given alpha beta
def traverse_graph(cities, pheromone_alpha, distance_beta, pheromone_map):
    visited = [] #acts both as cities visited and tour for ant
    visited.append(0) #the ant starts at the starting city (the first city)
    current = 0
    while len(visited) < len(cities): #while the tour hasn't reached every city
        neighbors = [] #feasible neighbors (neighbors we haven't already visited)
        neighbor_weights = [] #probability weight that ant chooses corresponding neighbor
        for i in range(0, len(cities)): #visit all possible cities
            if i not in visited: #if the city hasn't been visited
                pheromone = max(pheromone_map[current, i], 1e-5) #retrieve the pheromone along that edge, retrieving a minimal amount to encourage exploration
                weight = (pheromone**pheromone_alpha)/(dist(cities[current], cities[i])**distance_beta) #and use it and the distance to calculate the weight that the ant picks this city
                #add feasible neighbor and it's calculated weight to the list of possible next cities
                neighbors.append(i)
                neighbor_weights.append(weight)
        #randomly choose the next city
        next = random.choices(neighbors, weights = neighbor_weights)[0] #uses the normalized weights
        #update tour
        visited.append(next)
        current=next
    assert len(cities) == len(visited)
    return visited

def parallel_traverse(cities, pheromone_alpha, distance_beta, pheromone_map, ants, j):
    ant = traverse_graph(cities, pheromone_alpha, distance_beta, pheromone_map)
    ants[j] = ant