import heapq

n = int(input("Enter the Number of Nodes : "))
print("Enter Adjacency Matrix:-")
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

open_list = []
closed = []
cost = {}
parent = {}
cost[start] = 0
parent[start] = None
heapq.heappush(open_list, (0, start))

found = False
while open_list:
    current_cost, current = heapq.heappop(open_list)
    if current in closed:
        continue
    closed.append(current)
    print("\nExpanded Node : ", chr(ord('A') + current), "with cost", current_cost)
    print("OPEN : ", [(chr(ord('A') + n), c) for c, n in open_list])
    print("CLOSED : ", [chr(ord('A') + n) for n in closed])

    if current == goal:
        found = True
        break

    for neighbour, weight in B[current]:
        new_cost = current_cost + weight
        if neighbour not in cost or new_cost < cost[neighbour]:
            cost[neighbour] = new_cost
            parent[neighbour] = current
            heapq.heappush(open_list, (new_cost, neighbour))

if found:
    path = []
    node = goal
    while node is not None:
        path.append(node)
        node = parent[node]
    path.reverse()
    print("\nGoal Found")
    print("Path : ", [chr(ord('A') + p) for p in path])
    print("Cost : ", cost[goal])
else:
    print("\nGoal Not Found")
