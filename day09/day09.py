import time
import collections

Pos = collections.namedtuple('Pos', ['x', 'y'])

def adjacent (p1, p2): 
    return abs(p1.x - p2.x) <= 1 and abs(p1.y - p2.y) <= 1

def check_offsets (p1, p2, offsets):
    return any(p1.x == p2.x + x_offset and p1.y == p2.y + y_offset for x_offset, y_offset in offsets)

def update_point (pos, move): 
    return Pos(pos.x + move[0], pos.y + move[1])

def solve (filename, part):
    
    tail_length = 2 if part == 1 else 10
    rope = [Pos(x = 0, y = 0)] * tail_length
    visited_by_tail = set([rope[-1]])

    offsets_updates_pairs = (
        ([(0,-2)],                  (0,-1)),
        ([(0,2)],                   (0,1)),
        ([(-2,0)],                  (-1,0)),
        ([(2,0)],                   (1,0)),
        ([(-1,-2),(-2,-1),(-2,-2)], (-1,-1)),
        ([(2,1),(1,2),(2,2)],       (1,1)),
        ([(-2,1),(-1,2),(-2,2)],    (-1,1)),
        ([(1,-2),(2,-1),(2,-2)],    (1,-1))
    )

    with open(filename) as f:

        for line in f:

            # line parsing
            dir, number_of_moves = line.strip().split() 
            number_of_moves = int(number_of_moves)

            # moves simulation
            for _ in range(number_of_moves):

                # head update
                match dir:
                    case 'R': rope[0] = Pos(x = rope[0].x, y = rope[0].y + 1)
                    case 'L': rope[0] = Pos(x = rope[0].x, y = rope[0].y - 1)
                    case 'U': rope[0] = Pos(x = rope[0].x - 1, y = rope[0].y)
                    case 'D': rope[0] = Pos(x = rope[0].x + 1, y = rope[0].y)
                    case other: raise AssertionError()

                # tail update
                for i in range(tail_length - 1):

                    if adjacent(rope[i], rope[i+1]): 
                        break

                    for offsets, move in offsets_updates_pairs:
                        
                        if check_offsets(rope[i], rope[i+1], offsets):
                            rope[i+1] = update_point(rope[i+1], move)
                            break

                    else: 
                        raise AssertionError()

                visited_by_tail.add(rope[-1])

    return len(visited_by_tail)

if __name__ == "__main__":

    assert solve("input_09_test_01.txt", 1) == 13

    assert solve("input_09_test_01.txt", 2) == 1
    assert solve("input_09_test_02.txt", 2) == 36

    t = time.process_time()
    result = solve("input_09.txt", 1)
    t = time.process_time() - t
    print(f"part1 : {result} , {t * 1000:.02f} ms")
    
    t = time.process_time()
    result = solve("input_09.txt", 2)
    t = time.process_time() - t
    print(f"part2 : {result} , {t * 1000:.02f} ms")