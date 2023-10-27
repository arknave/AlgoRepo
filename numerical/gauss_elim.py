# Gauss elim on fractions
# untested
def gauss_elim(a):
    rank = 0
    r, c = len(a), len(a[0])
    for i in range(r):
        p = i
        while p < r and a[p][i] == 0:
            p += 1

        # whole column is 1s
        if p == r:
            continue

        rank += 1
        a[i], a[p] = a[p], a[i]

        val = a[i][i]
        assert val != 0
        a[i] = [x / val for x in a[i]]
        for j in range(r):
            if j == i:
                continue
            if a[j][i] != 0:
                scale = a[j][i]
                a[j] = [x - scale * a[i][k] for k, x in enumerate(a[j])]

    if rank < r:
        return rank

    for i in range(r - 1, -1, -1):
        assert a[i][i] == 1
        for j in range(r):
            if i == j:
                continue
            if a[j][i] != 0:
                scale = a[j][i]
                a[j] = [x - scale * a[i][k] for k, x in enumerate(a[j])]

    return rank

