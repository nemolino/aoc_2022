import time

def part1 (filename):

    cycle = 1
    x = 1
    signal_strength = 0

    def update_routine (cycle, signal_strength, x):
        if ((cycle - 20) % 40 == 0):
            signal_strength += cycle * x
        cycle += 1
        return (cycle, signal_strength)
    
    with open(filename) as f:
        for command in f:
            match command.strip().split():
                case ['addx', n]: 
                    cycle, signal_strength = update_routine (cycle, signal_strength, x)
                    cycle, signal_strength = update_routine (cycle, signal_strength, x)
                    x += int(n)

                case ['noop']:
                    cycle, signal_strength = update_routine (cycle, signal_strength, x)

                case _: raise AssertionError()
            
    return signal_strength


def part2 (filename):

    cycle = 1
    x = 1
    sprite_pos = x
    cur_line = 0

    crt = []
    for _ in range(6): crt.append(['.'] * 40)
    
    def update_routine (cycle, cur_line, crt, sprite_pos):
        if abs((cycle-1) - sprite_pos) <= 1:
            crt[cur_line][cycle-1] = '#'
        cycle += 1
        if cycle-1 == 40: 
            cycle = 1
            cur_line += 1
        return (cycle, cur_line)

    with open(filename) as f:
        for command in f:
            match command.strip().split():
                case ['addx', n]: 
                    cycle, cur_line = update_routine(cycle, cur_line, crt, sprite_pos)
                    cycle, cur_line = update_routine(cycle, cur_line, crt, sprite_pos)
                    x += int(n)
                    sprite_pos = x

                case ['noop']: 
                    cycle, cur_line = update_routine(cycle, cur_line, crt, sprite_pos)

                case _: raise AssertionError()

    return [''.join(line) for line in crt]


if __name__ == "__main__":

    assert part1("input_10_test.txt") == 13140
    assert part2("input_10_test.txt") == [  '##..##..##..##..##..##..##..##..##..##..', 
                                            '###...###...###...###...###...###...###.', 
                                            '####....####....####....####....####....', 
                                            '#####.....#####.....#####.....#####.....', 
                                            '######......######......######......####', 
                                            '#######.......#######.......#######.....'  ]

    t = time.process_time()
    result = part1("input_10.txt")
    t = time.process_time() - t
    print(f"part1 : {result} , {t * 1000:.02f} ms")
    
    t = time.process_time()
    result = part2("input_10.txt")
    t = time.process_time() - t
    result = "\n" + "\n".join(line for line in result)
    print(f"part2 : {result} , {t * 1000:.02f} ms")