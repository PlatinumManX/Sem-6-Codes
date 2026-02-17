def select(temp, H):
    best = temp[0]
    for node in temp:
        if H[node] < H[best]:
            best = node
    return best

n = int(input("Enter the Number of Nodes : "))
print("Enter the Adjacency Matrix:-")
A = []
for i in range(n):
    row = list(map(int, input().strip()))
    A.append(row)

B= [[] for _ in range(n)]
for i in range(n):
    for j in range(n):
        if A[i][j] == 1:
            B[i].append(j)

start_char = input("Enter Start Node : ")
start = ord(start_char) - ord('A')
goal_char = input("Enter Goal Node : ")
goal = ord(goal_char) - ord('A')

print("Enter the Heuristic Values:-")
H = []
for i in range(n):
    value = int(input(f"H({chr(ord('A') + i)}) = "))
    H.append(value)

temp = []
visited = []
temp.append(start)

parent = {}
parent[start] = None
found = False

while temp:
    current = select(temp, H)
    temp.remove(current)
    visited.append(current)

    print("Expanded Node: ", chr(ord('A') + current))
    print("OPEN: ", [chr(ord('A') + n) for n in temp])
    print("VISITED: ", [chr(ord('A') + n) for n in visited])
    print()

    if current == goal:
        found = True
        break
    for neighbour in B[current]:
        if neighbour not in visited and neighbour not in temp:
            parent[neighbour] = current
            temp.append(neighbour)

if found:
    path = []
    node = goal
    while node is not None:
        path.append(node)
        node = parent[node]
    path.reverse()

    print("Goal Found")
    print("Path: ", [chr(ord('A') + p) for p in path])
else:
    print("Goal Not Found")
