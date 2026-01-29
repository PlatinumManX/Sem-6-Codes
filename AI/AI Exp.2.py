def calculate(path, A):
    cost = 0
    for i in range(len(path) - 1):
        cost = cost + A[path[i]][path[i+1]]
    return cost

def dls(node, goal, depth, visited, path, open_list, graph):
    visited.append(node)
    path.append(node)
    open_list.append(node)
    print("OPEN : ", [chr(ord('A') + o) for o in open_list])
    print("CLOSED : ", [chr(ord('A') + v) for v in visited])
    print("-----------")
    
    if node == goal:
        return True
    if depth == 0:
        open_list.pop()
        path.pop()
        return False
    for neighbour in graph[node]:
        if neighbour not in visited:
            if dls(neighbour, goal, depth-1, visited, path, open_list, graph):
                return True
    open_list.pop()
    path.pop()
    return False

def dfs(node, goal, visited, path, open_list, graph):
    visited.append(node)
    path.append(node)
    open_list.append(node)
    print("OPEN : ", [chr(ord('A') + o) for o in open_list])
    print("CLOSED : ", [chr(ord('A') + v) for v in visited])
    print("--------")
    
    if node == goal:
        return True
    for neighbour in graph[node]:
        if neighbour not in visited:
            if dfs(neighbour, goal, visited, path, open_list, graph):
                return True
    open_list.pop()
    path.pop()
    return False

n = int(input("Enter the Number of Nodes : "))
print("Enter the Adjacency Matrix:-")
A = []
for i in range(n):
    row = list(map(int, input().split()))
    A.append(row)
#print(A)

B = [[] for _ in range(n)]
for i in range(n):
    for j in range(n):
        if A[i][j] != 0:
            B[i].append(j)
#print(B)

start_char = input("Enter Start Node : ")
goal_char = input("Enter Goal Node : ")
start = ord(start_char) - ord('A')
goal = ord(goal_char) - ord('A')
#print(start, goal)

while True:
    choice = int(input("1.DFS\n2.DLS\n3.DFID\n4.Exit\nEnter Your Choice : "))
    if choice == 1:
        visited = []
        path = []
        open_list = []
        found = dfs(start, goal, visited, path, open_list, B)
        if found:
            print("Goal Found")
            print("Path : ", [chr(ord('A') + p) for p in path])
            cost = calculate(path, A)
            print("Total Cost : ",cost)
        else:
            print("Goal Not Found")
    elif choice == 2:
        visited = []
        path = []
        open_list = []
        depth = int(input("Enter the Maximum Depth : "))
        found = dls(start, goal, depth, visited, path, open_list, B)
        if found:
            print("Goal Found")
            print("Path : ", [chr(ord('A') + p) for p in path])
            cost = calculate(path, A)
            print("Total Cost : ",cost)
        else:
            print("Goal Not Found")
    elif choice == 3:
        depth = int(input("Enter the Maximum Depth : "))
        flag = 0
        for i in range(depth + 1):
            visited = []
            path = []
            open_list = []
            found = dls(start, goal, i, visited, path, open_list, B)
            print(f"Iteration {i}:-")
            print("Visited Nodes : ", [chr(ord('A') + v) for v in visited])
            if found:
                print("Goal Found")
                print("Path : ", [chr(ord('A') + p) for p in path])
                cost = calculate(path, A)
                print("Total Cost : ",cost)
                flag = 1
                break
        if flag == 0:
            print("Goal Not Found")
    elif choice == 4:
        print("Exiting...")
        break
    else:
        print("Invalid Input")
