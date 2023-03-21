# Here we can use any gap penalties that we want
match = 10
mis_match = -5
gaps = -7

# this is for preprocessing of array -- here we are assigning gap penalties in the 2D array 
# For local alignment we would fill first row and first col with increasing gap penalties
def local_align(data, rows, cols):
    data[0][0] = 0
    
    # for 1st row 
    for i in range(1, cols):
        data[0][i] = 0              # Here will be changes

    # for 1st col 
    for i in range(1, rows):
        data[i][0] = 0              # Here will be changes

def make_best_possible_path(data, rows, cols, source, s, row, col):
    # Here we are doing col-1 because col and row starting from 1 and to get the character we would have to make it to 0
    source_char = source[col-1]
    s_char = s[row-1]

    diagonal = -1
    down = -1
    right = -1

    # here we are finding the score for match and mismatch
    if source_char == s_char:
        diagonal = data[row-1][col-1] + match
        down = data[row-1][col] + gaps
        right = data[row][col-1] + gaps
    else:
        diagonal = data[row-1][col-1] + mis_match
        down = data[row-1][col] + gaps
        right = data[row][col-1] + gaps

    data[row][col] = max(diagonal, right, down)
    if(data[row][col] < 0):
        data[row][col] = 0

# for calculating the whole matrix
def make_full_allignment(data, rows, cols, source, s):
    for i in range(1, rows):
        for j in range(1, cols):
            make_best_possible_path(data, rows, cols, source, s, i, j)

def find_max_value(data, rows, cols, row, col):
    max_value = -1
    for i in range(rows):
        for j in range(cols):
            if(max_value < data[i][j]):
                max_value = data[i][j]
                row = i
                col = j
    
    return [row, col]
            

# This is the backtracking of the solution from row and col
def backtrack_solution(data, source, s, row, col):
    if row == 0 and col == 0:
        p = ("", "")
        dp[row][col].append(p)
        return

    if row == 0:
        temp_source = source[col-1]
        temp_s = '_'
        # here we are using DP
        if(len(dp[row][col-1]) == 0):
            backtrack_solution(data, source, s, row, col-1)
            
        # Here we are storing the answers in DP
        for i in range(len(dp[row][col-1])):
            dp[row][col].append((temp_source + dp[row][col-1][i][0], temp_s + dp[row][col-1][i][1]))
        return

    if col == 0:
        temp_source = '_'
        temp_s = s[row-1]
        # here we are using DP
        if(len(dp[row-1][col]) == 0):
            backtrack_solution(data, source, s, row-1, col)
            
        # Here we are storing the answers in DP
        for i in range(len(dp[row-1][col])):
            dp[row][col].append((temp_source + dp[row-1][col][i][0], temp_s + dp[row-1][col][i][1]))
        return

    diagonal = data[row-1][col-1]
    left = data[row][col-1]
    up = data[row-1][col]
    value = data[row][col]

    # When first 0 is encountered we stop......
    if(value == 0):
        # p = (temp_source, temp_s)
        # ans.append(p)
        # return
        p = ("", "")
        dp[row][col].append(p)
        return

    # four calls are made for bactracking the solution
    # 1. it is for match 
    if diagonal + match == value and source[col-1] == s[row-1]:
        temp_source = source[col-1]
        temp_s = s[row-1]

        if(len(dp[row-1][col-1]) == 0):
            backtrack_solution(data, source, s, row-1, col-1)
        
        # Here we are storing the answers in DP
        for i in range(len(dp[row-1][col-1])):
            dp[row][col].append((temp_source + dp[row-1][col-1][i][0], temp_s + dp[row-1][col-1][i][1]))

    # 2. it is for mismatch 
    if diagonal + mis_match == value and source[col-1] != s[row-1]:
        temp_source = source[col-1]
        temp_s = s[row-1]

        if(len(dp[row-1][col-1]) == 0):
            backtrack_solution(data, source, s, row-1, col-1)
        
        # Here we are storing the answers in DP
        for i in range(len(dp[row-1][col-1])):
            dp[row][col].append((temp_source + dp[row-1][col-1][i][0], temp_s + dp[row-1][col-1][i][1]))

    # 3. it is for gap 
    if left + gaps == value:
        temp_source = source[col-1]
        temp_s = '_'

        if(len(dp[row][col-1]) == 0):
            backtrack_solution(data, source, s, row, col-1)

        # Here we are storing the answers in DP
        for i in range(len(dp[row][col-1])):
            dp[row][col].append((temp_source + dp[row][col-1][i][0], temp_s + dp[row][col-1][i][1]))

    # 4. it is for gap 
    if up + gaps == value:
        temp_source = '_'
        temp_s = s[row-1]

        if(len(dp[row-1][col]) == 0):
            backtrack_solution(data, source, s, row-1, col)

        # Here we are storing the answers in DP
        for i in range(len(dp[row-1][col])):
            dp[row][col].append((temp_source + dp[row-1][col][i][0], temp_s + dp[row-1][col][i][1]))

    return

# It is for printing the matrix
def print_data(data, rows, cols):
    for i in range(rows):
        for j in range(cols):
            print(data[i][j], end="\t")
        print("\n")


source = input().strip()
s = input().strip()

rows = len(s) + 1
cols = len(source) + 1

# Initializing the 2D array
data = [[0 for j in range(len(source) + 1)] for i in range(len(s) + 1)]
dp = [[[] for j in range(cols)] for i in range(rows)]

# This is for local Alignment Only
local_align(data, len(s) + 1, len(source) + 1)

make_full_allignment(data, len(s) + 1, len(source) + 1, source, s)

# finding the maximum value in whole matrix
row = -1
col = -1
[row, col] = find_max_value(data, len(s) + 1, len(source) + 1, row, col);

#min code
backtrack_solution(data, source, s, row, col)

print()
print_data(data, rows, cols)

print("There are ", len(dp[row][col]), " combinations")

for i in range(len(dp[row][col])):
    print(dp[row][col][i][0][::-1])
    print(dp[row][col][i][1][::-1])
    print()


# Here we start from max_value in the matrix i.e  (row, col)