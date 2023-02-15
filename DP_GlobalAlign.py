match = 2
mis_match = -1
gaps = -1


def global_align(data, rows, cols):
    data[0][0] = 0
    
    for i in range(1, cols):
        data[0][i] = -i

    for i in range(1, rows):
        data[i][0] = -i

def make_best_possible_path(data, rows, cols, source, s, row, col):
    source_char = source[col-1]
    s_char = s[row-1]

    diagonal = -1
    down = -1
    right = -1

    if source_char == s_char:
        diagonal = data[row-1][col-1] + match
        down = data[row-1][col] + gaps
        right = data[row][col-1] + gaps
    else:
        diagonal = data[row-1][col-1] + mis_match
        down = data[row-1][col] + gaps
        right = data[row][col-1] + gaps

    max_value = max(diagonal, down, right)
    if max_value == diagonal:
        data[row][col] = diagonal
    elif max_value == right:
        data[row][col] = right
    elif max_value == down:
        data[row][col] = down

def make_full_allignment(data, rows, cols, source, s):
    for i in range(1, rows):
        for j in range(1, cols):
            make_best_possible_path(data, rows, cols, source, s, i, j)


def backtrack_solution(data, source, s, ans, row, col, temp_source, temp_s):
    if row == 0 and col == 0:
        p = (temp_source, temp_s)
        ans.append(p)
        return

    if row == 0:
        temp_source += source[col-1]
        temp_s += '_'
        backtrack_solution(data, source, s, ans, row, col-1, temp_source, temp_s)
        temp_source = temp_source[:-1]
        temp_s = temp_s[:-1]
        return

    if col == 0:
        temp_source += '_'
        temp_s += s[row-1]
        backtrack_solution(data, source, s, ans, row-1, col, temp_source, temp_s)
        temp_source = temp_source[:-1]
        temp_s = temp_s[:-1]
        return

    diagonal = data[row-1][col-1]
    left = data[row][col-1]
    up = data[row-1][col]
    value = data[row][col]

    if diagonal + match == value and source[col-1] == s[row-1]:
        temp_source += source[col-1]
        temp_s += s[row-1]
        backtrack_solution(data, source, s, ans, row-1, col-1, temp_source, temp_s)
        temp_source = temp_source[:-1]
        temp_s = temp_s[:-1]

    if diagonal + mis_match == value and source[col-1] != s[row-1]:
        temp_source += source[col-1]
        temp_s += s[row-1]
        backtrack_solution(data, source, s, ans, row-1, col-1, temp_source, temp_s)
        temp_source = temp_source[:-1]
        temp_s = temp_s[:-1]

    if left + gaps == value:
        temp_source += source[col-1]
        temp_s += '_'
        backtrack_solution(data, source, s, ans, row, col-1, temp_source, temp_s)
        temp_source = temp_source[:-1]
        temp_s = temp_s[:-1]

    if up + gaps == value:
        temp_source += '_'
        temp_s += s[row-1]
        backtrack_solution(data, source, s, ans, row-1, col, temp_source, temp_s)
        temp_source = temp_source[:-1]
        temp_s = temp_s[:-1]

    return

def print_data(data, rows, cols):
    for i in range(rows):
        for j in range(cols):
            print(data[i][j], end="\t")
        print("\n")


if __name__ == '__main__':
    source = input().strip()
    s = input().strip()

    data = [[0 for j in range(len(source) + 1)] for i in range(len(s) + 1)]

    global_align(data, len(s) + 1, len(source) + 1)

    make_full_allignment(data, len(s) + 1, len(source) + 1, source, s)

    ans = []
    backtrack_solution(data, source, s, ans, len(s), len(source), "", "")

    ans = [(a[::-1], b[::-1]) for a, b in ans]

    print()
    for a, b in ans:
        print(a)
        print(b)
        print()

    print_data(data, len(s) + 1, len(source) + 1)
    print("\nThere are total", len(ans), "combinations")
