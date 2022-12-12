import time
from collections import namedtuple, deque
import math

Monkey = namedtuple('Monkey', ['worry_levels', 'change_worry_level', 'throw_to'])

def solve (filename, part):

    monkeys = []
    product_of_divisors = 1
   
    with open(filename) as f:
        for m in map(lambda x: x.split("\n"), f.read().split("\n\n")): 
            y, op, z = m[1].split()
            divisor, a, b = map(lambda x: int(x), m[2].split())
            product_of_divisors *= divisor
            monkeys.append( 
                Monkey( deque(map(lambda x: int(x), m[0].split(", "))), 
                        lambda x, y=y, op=op, z=z:  (x if y == "old" else int(y)) + (x if z == "old" else int(z)) if op == '+' else
                                                    (x if y == "old" else int(y)) * (x if z == "old" else int(z)),
                        lambda x, divisor=divisor, a=a, b=b:    a if x % divisor == 0 else b) 
            )
    
    inspection_counts = [0] * len(monkeys)
    number_of_rounds = 20 if part == 1 else 10000

    for _ in range(number_of_rounds):
        for i,m in enumerate(monkeys): 

            while len(m.worry_levels) > 0:
                
                x = m.change_worry_level(m.worry_levels.popleft())
                x = math.floor(x / 3) if part == 1 else x % product_of_divisors
                monkeys[m.throw_to(x)].worry_levels.append(x)
                inspection_counts[i] += 1

    inspection_counts = sorted(inspection_counts)
    return inspection_counts[-2] * inspection_counts[-1]


if __name__ == "__main__":

    assert solve("input_11_test_reformatted.txt", 1) == 10605
    assert solve("input_11_test_reformatted.txt", 2) == 2713310158
    
    t = time.process_time()
    result = solve("input_11_reformatted.txt", 1)
    t = time.process_time() - t
    print(f"part1 : {result} , {t * 1000:.02f} ms")
    
    t = time.process_time()
    result = solve("input_11_reformatted.txt", 2)
    t = time.process_time() - t
    print(f"part2 : {result} , {t * 1000:.02f} ms")