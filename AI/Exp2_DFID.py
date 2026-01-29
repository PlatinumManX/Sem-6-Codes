def dls(node, goal, depth, visited, path, graph):
    visited.append(node)
    path.append(node)
    if node == goal:
        return True
    if depth == 0:
        path.pop()
        return False
    for neighbour in graph[node]:
        if neighbour not in visited:
            if dls(neighbour, goal, depth-1, visited, path, graph):
                return True
    path.pop()
    return False

n = int(input("Enter the Number of Nodes : "))
print("Enter the Adjacency Matrix:-")
A = []
for i in range(n):
    row = list(map(int, input().strip()))
    A.append(row)
#print(A)

B = [[] for _ in range(n)]
for i in range(n):
    for j in range(n):
        if A[i][j] == 1:
            B[i].append(j)
#print(B)

start_char = input("Enter Start Node : ")
goal_char = input("Enter Goal Node : ")
start = ord(start_char) - ord('A')
goal = ord(goal_char) - ord('A')
depth = int(input("Enter the Maximum Depth : "))
flag = 0
#print(start, goal, max)

for i in range(depth+1):
    visited = []
    path = []
    found = dls(start, goal, i, visited, path, B)

    print(f"\nIteration {i}:-")
    print("Visited Nodes : ", [chr(ord('A') + v) for v in visited])

    if found:
        print("Goal Found")
        print("Path : ", [chr(ord('A') + p) for p in path])
        print("Iterations Required : ", i)
        flag = 1
        break
if flag == 0:
    print("Goal Not Found")
