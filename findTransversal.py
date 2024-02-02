def find_all_transversals(latin_square):
    n = len(latin_square)
    transversals = []
    transversal = [-1] * n
    used = [False] * n

    def backtrack(i):
        if i == n:
            transversals.append(transversal.copy())
            return
        for j in range(n):
            if not used[j] and latin_square[i][j] not in transversal:
                transversal[i] = latin_square[i][j]
                used[j] = True
                backtrack(i + 1)
                used[j] = False
                transversal[i] = -1

    backtrack(0)
    return transversals

latin_square = [[1, 2, 3], [2, 3, 1], [3, 1, 2]]
all_transversals = find_all_transversals(latin_square)
for transversal in all_transversals:
    print(transversal)