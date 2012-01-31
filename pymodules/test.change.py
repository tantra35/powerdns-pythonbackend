import mmap;
import random;

def shuffle():
  l_digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'];
  random.shuffle(l_digits);

  return "".join(l_digits);


with open("hello.txt", "r+") as f:
  map = mmap.mmap(f.fileno(), 1000);
  l_i = 0;

  for l_digit in shuffle():
    map[l_i] = l_digit;
    l_i += 1;