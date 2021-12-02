import numpy as np

def gen_random_numbers(height=10, width=20):
    return np.floor(np.random.rand(height, width) * 10).astype(int)

def calc_accuracy(input, output):
    diff = input - output
    num_wrong = np.count_nonzero(diff)
    num_right = diff.shape[1] - num_wrong
    return num_right / diff.shape[1]

def calc_itr(input, output):
    acc = calc_accuracy(input, output)
    num_targets = 10
    itr = np.log2(num_targets) + (acc * np.log2(acc)) + ((1 - acc) * np.log2((1 - acc) / (num_targets - 1)))
    avg_time_per_trial = input.shape[1] / (time / 60)
    return itr * avg_time_per_trial
    
