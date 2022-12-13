import time


def ordered(left, right):

    if isinstance(left, int) and isinstance(right, list):
        left = [left]

    elif isinstance(left, list) and isinstance(right, int):
        right = [right]

    elif isinstance(left, int) and isinstance(right, int):
        return -1 if left == right else left < right
    
    if isinstance(left, list) and isinstance(right, list):
        for i in range(min(len(left), len(right))):
            res = ordered(left[i], right[i]) 
            if res != -1: return res
        return -1 if len(left) == len(right) else len(left) < len(right)

    raise AssertionError("unreachable")  


def part1 (filename):

    with open(filename) as f:
        pairs = map(lambda x: x.split("\n"), f.read().split("\n\n"))
        pairs = map(lambda x: tuple([eval(x[0]), eval(x[1])]) , pairs)

    return sum(i+1 for i, p in enumerate(pairs) if ordered(p[0], p[1]))


def part2 (filename):

    packets = []

    with open(filename) as f:
        for p in map(lambda x: x.split("\n"), f.read().split("\n\n")):
            packets += p
        packets = tuple(map(lambda x: eval(x), packets))

    return (sum(1 for p in packets if ordered(p, [[2]])) + 1) * \
            (sum(1 for p in packets if ordered(p, [[6]])) + 2)


if __name__ == "__main__":

    assert part1("input_13_test.txt") == 13
    assert part2("input_13_test.txt")== 140
    
    t = time.process_time()
    result = part1("input_13.txt")
    t = time.process_time() - t
    print(f"part1 : {result} , {t * 1000:.02f} ms")
    
    t = time.process_time()
    result = part2("input_13.txt")
    t = time.process_time() - t
    print(f"part2 : {result} , {t * 1000:.02f} ms")