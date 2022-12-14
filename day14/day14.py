import time


def down_step (p, rock_positions, sand_positions):

    y, x = p[0], p[1] 
    if (y, x + 1) not in rock_positions and (y, x + 1) not in sand_positions:
        return (y, x + 1)   
    elif (y - 1, x + 1) not in rock_positions and (y - 1, x + 1) not in sand_positions:
        return (y - 1, x + 1)      
    elif (y + 1, x + 1) not in rock_positions and (y + 1, x + 1) not in sand_positions:
        return (y + 1, x + 1)
    return False
    

def part1 (rock_positions):

    sand_positions = set()
    max_point = max(el[1] for el in rock_positions)
    p = (500,0)
    while True:
        if p[1] >= max_point: 
            return len(sand_positions)
        result = down_step(p, rock_positions, sand_positions)
        if not result:
            sand_positions.add(p)
            p = (500,0)
        else: 
            p = result
        

def part2 (rock_positions):

    sand_positions = set()
    max_point = max(el[1] for el in rock_positions) + 2
    p = (500,0)
    while True:
        if p[1] + 1 == max_point:
            sand_positions.add(p)
            p = (500,0)
        result = down_step(p, rock_positions, sand_positions)
        if not result:
            sand_positions.add(p)
            if p[0] == 500 and p[1] == 0: 
                return len(sand_positions)
            else:                       
                p = (500,0)
        else: 
            p = result

def solve (filename, part):

    rock_positions = set()
    with open(filename) as f:
        for line in f:

            seq = list(map(lambda x: tuple(map(lambda x: int(x), x.split(","))), 
                           line.strip().split(" -> ")))

            for i in range(len(seq)-1):
                cond = (seq[i][0] == seq[i+1][0])
                start = seq[i][1] if cond else seq[i][0]
                end = seq[i+1][1] if cond else seq[i+1][0]
                if start > end: 
                    start, end = end, start
                for j in range (start, end+1):
                    rock_positions.add((seq[i][0] if cond else j, 
                                                j if cond else seq[i][1]))

    return part1(rock_positions) if part == 1 else part2(rock_positions)


if __name__ == "__main__":

    assert solve("input_14_test.txt", 1) == 24
    assert solve("input_14_test.txt", 2) == 93
    
    t = time.process_time()
    result = solve("input_14.txt", 1)
    t = time.process_time() - t
    print(f"part1 : {result} , {t * 1000:.02f} ms")
    
    t = time.process_time()
    result = solve("input_14.txt", 2)
    t = time.process_time() - t
    print(f"part2 : {result} , {t * 1000:.02f} ms")