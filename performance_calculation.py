import numpy as np

# Generates a matrix with random numbers between 0 and 10.
# The height and width parameters are mainly for readability.
# Number of generated numbers = height * width
# Parameters:
#   height = the number of rows in the matrix.
#   width = the length of each row in the matrix.
def gen_random_numbers(height=10, width=20):
    return np.floor(np.random.rand(height, width) * 10).astype(int)

# Calculates the accuracy between two arrays.
# This is done by calculating the difference
# and perceiving every nonzero instance as incorrect.
# NOTE: Unintuitively, this requires a 1D array,
# you can call .flatten() on a matrix.
# Parameters:
#   input: the reference list presented on the screen.
#   output: the output perceived by the user.
def calc_accuracy(input, output):
    diff = input - output
    num_wrong = np.count_nonzero(diff)
    num_right = diff.shape[1] - num_wrong
    return num_right / diff.shape[1]

# Calculates the information transfer rate.
# Uses the calculation as given by:
# https://bci-lab.hochschule-rhein-waal.de/en/itr.html
# Parameters:
#   input: the reference list presented on the screen.
#   output: the output perceived by the user.
#   time: the total time spent on all trials in seconds.
def calc_itr(input, output, time):
    acc = calc_accuracy(input, output)
    num_targets = 10
    itr = np.log2(num_targets) + (acc * np.log2(acc)) + ((1 - acc) * np.log2((1 - acc) / (num_targets - 1)))
    avg_time_per_trial = input.shape[1] / (time / 60)
    return itr * avg_time_per_trial
    
