import time
import collections

Dir = collections.namedtuple('Dir', ['name', 'parent'])
File = collections.namedtuple('File', ['name', 'size'])

def solve(filename, part):

    FS = {}
    cur_dir = None

    with open(filename) as f:

        for line in f:
            line = line.strip()

            if line.startswith("$ cd"):

                dir_name = line[5:]
                if dir_name == "..": 
                    cur_dir = cur_dir.parent
                else: 
                    new_dir = Dir(name = dir_name, parent = cur_dir)
                    FS[new_dir] = []
                    cur_dir = new_dir

            elif line != "$ ls": 

                if line.startswith("dir "): 
                    dir_name = line[4:]
                    new_dir = Dir(name = dir_name, parent = cur_dir)
                    FS[new_dir] = []
                    FS[cur_dir].append(new_dir)
                else:
                    file_size, file_name = line.split()
                    FS[cur_dir].append(File(name = file_name, size = int(file_size)))

    size = lambda x : x.size if isinstance(x, File) else sum(size(item) for item in FS[x])

    if part == 1:
        return sum(filter(lambda x: x <= 100000, (size(k) for k in FS.keys())))
    else:
        residual_needed_space = size(Dir(name = '/', parent = None)) - 40000000
        return min(filter(lambda x: x >= residual_needed_space, (size(k) for k in FS.keys())))


if __name__ == "__main__":

    assert solve("input_07_test.txt", 1) == 95437
    assert solve("input_07_test.txt", 2) == 24933642

    t = time.process_time()
    result = solve("input_07.txt", 1)
    t = time.process_time() - t
    print(f"part1 : {result} , {t * 1000:.02f} ms")
    
    t = time.process_time()
    result = solve("input_07.txt", 2)
    t = time.process_time() - t
    print(f"part2 : {result} , {t * 1000:.02f} ms")