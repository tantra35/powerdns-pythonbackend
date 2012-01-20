import mmap;
import time;

with open("hello.txt", "r+") as f:
  while True:
    map = mmap.mmap(f.fileno(), 1000);
    print map[0:9];

    time.sleep(1);

