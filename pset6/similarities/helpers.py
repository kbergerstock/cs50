from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def min(f1, f2, f3):
    """ returns the minimum of three tuples """
    if f1[0] < f2[0] and f1[0] < f3[0]:
        return f1
    elif f2[0] < f3[0]:
        return f2
    else:
        return f3


def distances(a, b):
    """Calculate edit distance from a to b"""
    nc = len(b)
    nr = len(a)
    t = (0, None)
    # create empty output matching size requirements
    m = [[t for c in range(nc + 1)] for r in range(nr + 1)]

    # fill in left col
    for r in range(nr):
        m[r + 1][0] = (r + 1, Operation.DELETED)

    # fill in top row
    for c in range(nc):
        m[0][c + 1] = (c + 1, Operation.INSERTED)

    # fill in matrix
    for c in range(nc):
        c1 = c + 1
        for r in range(nr):
            r1 = r + 1
            f1 = (m[r][c1][0] + 1, Operation.INSERTED)
            f2 = (m[r1][c][0] + 1, Operation.DELETED)
            f3 = (m[r][c][0] + (0 if a[r] == b[c] else 1), Operation.SUBSTITUTED)
            m[r1][c1] = min(f1, f2, f3)
    return m
