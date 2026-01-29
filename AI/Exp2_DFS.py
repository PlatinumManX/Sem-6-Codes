def dfs(node, goal, visited, path, graph):
    visited.append(node)
    path.append(node)
    if node == goal:
        return True
    for neighbour in graph[node]:
        if neighbour not in visited:
            if dfs(neighbour, goal, visited, path, graph):
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
#print(start, goal, max)

visited = []
path = []
found = dfs(start, goal, visited, path, B)

if found:
    print("Goal Found")
    print("Path : ", [chr(ord('A') + p) for p in path])
else:
    print("Goal Not Found")
