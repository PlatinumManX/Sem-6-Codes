from collections import deque
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
goal_char = input("Enter Goal Node : ")
start = ord(start_char) - ord('A')
goal = ord(goal_char) - ord('A')

'''print("\nAdjacency List (with weights):")
for i in range(n):
    print(chr(ord('A') + i), "->",
          [(chr(ord('A') + v), w) for v, w in B[i]])'''

open_list = deque()
closed = []
open_list.append(start)
parent = {}
parent[start] = None
found = False

while open_list:
    current = open_list.popleft()
    closed.append(current)
    print("Expanded Node: ", chr(ord('A') + current))
    print("OPEN :", [chr(ord('A') + n) for n in open_list])
    print("CLOSED :", [chr(ord('A') + n) for n in closed])
    print()

    if current == goal:
        found = True
        break

    for neighbour, weight in B[current]:
        if neighbour not in closed and neighbour not in open_list:
            parent[neighbour] = current
            open_list.append(neighbour)
if found:
    path = []
    node = goal
    while node is not None:
        path.append(node)
        node = parent[node]
    path.reverse()
    cost = 0
    for i in range(len(path) - 1):
        cost = cost + A[path[i]][path[i+1]]
    print("Goal Found")
    print("Path : ", [chr(ord('A') + p) for p in path])
    print("Total Cost :", cost)
else:
    print("Goal Not Found")
