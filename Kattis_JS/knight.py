from collections import deque

RANGE = 50
ds = [(2, 1), (2, -1), (-2, 1), (-2, -1), (1, 2), (1, -2), (-1, 2), (-1, -2)]

def bfs(n, m, src, sink):
    grid = [[float('inf') for _ in range(m)] for _ in range(n)]
    grid[src[0]][src[1]] = 0
    q = deque([src])

    while q:
        cur = q.popleft()
        for dx, dy in ds:
            nx, ny = cur[0] + dx, cur[1] + dy
            if 0 <= nx < n and 0 <= ny < m and grid[nx][ny] == float('inf'):
                grid[nx][ny] = 1 + grid[cur[0]][cur[1]]

                if nx == sink[0] and ny == sink[1]:
                    return grid[nx][ny]

                q.append((nx, ny))

    return float('inf')

def main():
    nx, ny = map(int, input().split())
    sx, sy = map(int, input().split())
    gx, gy = map(int, input().split())

  #

    full = [[2, 2, 1, 1], [1, -1, 2, -2]]
    best = float('inf')
    for first in range(4):
        for second in range(first + 1, 4):
            mat = [[x for i, x in enumerate(row) if i not in (first, second)] for row in full]
            
            det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]

            print(first, second)
            print(mat)
            print(det)

            for v1 in range(-RANGE, RANGE + 1):
                if abs(v1) > best:
                    continue

                for v2 in range(-RANGE, RANGE + 1):
                    if abs(v1) + abs(v2) > best:
                        continue

                    xx = sx - gx - full[0][first] * v1 - full[0][second] * v2
                    yy = sy - gy - full[1][first] * v1 - full[1][second] * v2

                    r1 = mat[1][1] * xx - mat[0][1] * yy
                    r2 = -mat[1][0] * xx + mat[0][0] * yy
                    if r1 % abs(det) != 0 or r2 % abs(det) != 0:
                        continue

                    r1 //= det
                    r2 //= det
                    
                    best = min(best, abs(r1) + abs(r2) + abs(v1) + abs(v2))
    print(best)

main()