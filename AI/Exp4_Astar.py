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
    row = list(map(int, input().split()))
    A.append(row)

B = [[] for _ in range(n)]
for i in range(n):
    for j in range(n):
        if A[i][j] != 0:
            B[i].append((j, A[i][j]))

start_char = input("Enter Start Node : ")
start = ord(start_char) - ord('A')
goal_char = input("Enter Goal Node : ")
goal = ord(goal_char) - ord('A')

print("Enter Heuristic Values:-")
H = []
for i in range(n):
    value = int(input(f"H({chr(ord('A') + i)}) = "))
    H.append(value)

temp = []
visited = []
temp.append(start)
parent = {}
parent[start] = None
g = {}
f = {}
g[start] = 0
f[start] = H[start]
found = False

while temp:
    current = select(temp, f)
    temp.remove(current)
    visited.append(current)

    print("Expanded Node : ", chr(ord('A') + current))
    print("g(n) = ", g[current], "h(n) = ", H[current], "f(n) = ", f[current])
    print("OPEN : ", [chr(ord('A') + n) for n in temp])
    print("VISITED : ", [chr(ord('A') + n) for n in visited])
    print()

    if current == goal:
        found = True
        break
    for neighbour, weight in B[current]:
        new_g = g[current] + weight
        if neighbour not in g or new_g < g[neighbour]:
            g[neighbour] = new_g
            f[neighbour] = g[neighbour] + H[neighbour]
            parent[neighbour] = current
            if neighbour not in visited and neighbour not in temp:
                temp.append(neighbour)

if found:
    path = []
    node = goal
    while node is not None:
        path.append(node)
        node = parent[node]
    path.reverse()
    print("Goal Found")
    print("Path : ", [chr(ord('A') + p) for p in path])
    print("Total Cost : ", g[goal])

else:
    print("Goal Not Found")








    
