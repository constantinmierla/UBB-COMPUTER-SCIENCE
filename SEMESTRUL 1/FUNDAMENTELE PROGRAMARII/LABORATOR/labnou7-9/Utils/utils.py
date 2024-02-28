import string
import random

def random_string(size):
    return random.choice(string.ascii_uppercase)+''.join(random.choice(string.ascii_lowercase) for _ in range(size-1))

def random_number(size):
    return ''.join(random.choice(string.digits) for _ in range(size))