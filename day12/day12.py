import time
from collections import namedtuple
import networkx as nx

Vertex = namedtuple('Vertex', ['index', 'height'])

def solve (filename, part):

    DG = nx.DiGraph()
    
    with open(filename) as f:
        v = list(map(lambda x: list(x.strip()), f.readlines()))

    n_rows = len(v)
    n_cols = len(v[0])
    src_v, dest_v = None, None

    # adding vertices to graph
    for i in range(n_rows):
        for j in range(n_cols):
            if (v[i][j] == 'S'):
                v[i][j] = 'a'
                v[i][j] = Vertex(index = i*n_cols+j, height = ord(v[i][j]))
                src_v = v[i][j]
            elif (v[i][j] == 'E'):
                v[i][j] = 'z'
                v[i][j] = Vertex(index = i*n_cols+j, height = ord(v[i][j]))
                dest_v = v[i][j]
            else:
                v[i][j] = Vertex(index = i*n_cols+j, height = ord(v[i][j]))
            DG.add_node(v[i][j])

    # adding edges to graph
    for i in range(n_rows):
        for j in range(n_cols):
            if j > 0        and v[i][j-1].height - v[i][j].height <= 1: DG.add_edge(v[i][j], v[i][j-1])
            if j < n_cols-1 and v[i][j+1].height - v[i][j].height <= 1: DG.add_edge(v[i][j], v[i][j+1])
            if i > 0        and v[i-1][j].height - v[i][j].height <= 1: DG.add_edge(v[i][j], v[i-1][j])
            if i < n_rows-1 and v[i+1][j].height - v[i][j].height <= 1: DG.add_edge(v[i][j], v[i+1][j])

    if part == 1:
        return nx.shortest_path_length(DG, source=src_v, target=dest_v)
    
    shortest_path_length = len(DG.nodes) + 1
    for v in DG.nodes:
        if v.height == ord('a'):
            try: length = nx.shortest_path_length(DG, source=v, target=dest_v)
            except: pass
            if length < shortest_path_length:
                shortest_path_length = length
    return shortest_path_length


if __name__ == "__main__":

    assert solve("input_12_test.txt", 1) == 31
    assert solve("input_12_test.txt", 2) == 29
    
    t = time.process_time()
    result = solve("input_12.txt", 1)
    t = time.process_time() - t
    print(f"part1 : {result} , {t * 1000:.02f} ms")
    
    t = time.process_time()
    result = solve("input_12.txt", 2)
    t = time.process_time() - t
    print(f"part2 : {result} , {t * 1000:.02f} ms")