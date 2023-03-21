#include<iostream>
#include<string.h>
#include<vector>
using namespace std;

int match = 2;
int mis_match = -1;
int gaps = -2;

void local_align(vector< vector< int > > &data, int rows, int cols){
    data[0][0] = 0;

    // now we have to somewhat like 1 based indexing
    for(int i=1;i<cols;i++){
        data[0][i] = 0;
    }   // for column

    for(int i=1;i<rows;i++){
        data[i][0] = 0;
    }   // for rows
}

void make_best_possible_path(vector< vector< int > > &data, int rows, int cols, string source, string s, int row, int col){
    char source_char = source[col-1];
    char s_char = s[row-1];

    int diagonal = -1, down = -1, right = -1; 
    // for match
    if(source_char == s_char){
        diagonal = data[row-1][col-1] + match;      // matching Scheme
        down = data[row-1][col] + gaps;            // for gaps
        right = data[row][col-1] + gaps;            // for gaps
    }
    else{
        diagonal = data[row-1][col-1] + mis_match;      // Mis-matching Scheme
        down = data[row-1][col] + gaps;            // for gaps
        right = data[row][col-1] + gaps;            // for gaps
    }

    int max_value = max(diagonal, max(right, down));
    if(max_value <= 0){
        // if value is negative initialize it to zero
        data[row][col] = 0;
    }
    else if(max_value == diagonal){
        // diagonal is greatest
        data[row][col] = diagonal;
    }
    else if(max_value == right){
        // right is greatest
        data[row][col] = right;
    }
    else if(max_value == down){
        // down is greatest
        data[row][col] = down;
    }
}
void make_full_allignment(vector< vector< int > > &data, int rows, int cols, string source, string s){
    for(int i=1;i<rows;i++){
        for(int j=1;j<cols;j++){
            make_best_possible_path(data, rows, cols, source, s, i, j);
        }
    }
}

void find_max_value(vector< vector< int > > &data, int rows, int cols, int &row, int &col){
    int max_value = -1;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(max_value < data[i][j]){
                max_value = data[i][j];
                row = i;
                col = j;
            }
        }
    }
}

void backtrack_solution(vector< vector< int > > &data, string source, string s, vector< pair<string, string> > &ans, int row, int col, string temp_source, string temp_s){
    if(row == 0 && col == 0){
        pair<string, string> p;
        p.first = temp_source;
        p.second = temp_s;

        ans.push_back(p);
        return;
    }

    // it is in 0th row so it should move in left direction only.
    if(row == 0){
        temp_source.push_back(source[col-1]);
        temp_s.push_back('_');

        backtrack_solution(data, source, s, ans, row, col-1, temp_source, temp_s);
        
        temp_source.pop_back();
        temp_s.pop_back();
        return;
    }

    // it is in 0th col so we have to move up direction only.
    if(col == 0){
        temp_source.push_back('_');
        temp_s.push_back(s[row-1]);

        backtrack_solution(data, source, s, ans, row-1, col, temp_source, temp_s);
        
        temp_source.pop_back();
        temp_s.pop_back();
        return;
    }

    int diagonal = data[row-1][col-1];
    int left = data[row][col-1];
    int up = data[row-1][col];

    int value = data[row][col];


    // for diagonal -- match
    if(diagonal + match == value && source[col-1] == s[row-1]){
        temp_source.push_back(source[col-1]);
        temp_s.push_back(s[row-1]);

        backtrack_solution(data, source, s, ans, row-1, col-1, temp_source, temp_s);

        temp_source.pop_back();
        temp_s.pop_back();
    }

    if(diagonal + mis_match == value && source[col-1] != s[row-1]){
        temp_source.push_back(source[col-1]);
        temp_s.push_back(s[row-1]);

        backtrack_solution(data, source, s, ans, row-1, col-1, temp_source, temp_s);
        
        temp_source.pop_back();
        temp_s.pop_back();
    }

    if(left + gaps == value){
        temp_source.push_back(source[col-1]);
        temp_s.push_back('_');

        backtrack_solution(data, source, s, ans, row, col-1, temp_source, temp_s);
        
        temp_source.pop_back();
        temp_s.pop_back();
    }

    if(up + gaps == value){
        temp_source.push_back('_');
        temp_s.push_back(s[row-1]);

        backtrack_solution(data, source, s, ans, row-1, col, temp_source, temp_s);
        
        temp_source.pop_back();
        temp_s.pop_back();
    }

    return;
}

void print_data(vector< vector< int > > &data, int rows, int cols){
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            cout<<data[i][j]<<"\t";
        }
        cout<<endl<<endl;
    }
}



int main(){
    string source = "", s = "";
    cin>>source;
    cin>>s;

    vector< vector<int> > data;
    vector<int> temp;
    int rows = s.size() + 1;
    int cols = source.size() + 1;

    for(int i=0;i<rows;i++){
        data.push_back(temp);
        for(int j=0;j<cols;j++){
            data[i].push_back(0);
        }
    }  

    local_align(data, rows, cols);

    make_full_allignment(data, rows, cols, source, s);

    vector< pair<string, string> > ans;
    string temp_source = "", temp_s = "";

    // finding the maximum value in whole matrix
    int row = -1, col = -1;
    find_max_value(data, rows, cols, row, col);

    backtrack_solution(data, source, s, ans, row, col, temp_source, temp_s);

    for(int i=0;i<ans.size();i++){
        reverse(ans[i].first.begin(), ans[i].first.end());
        reverse(ans[i].second.begin(), ans[i].second.end());
    }

    cout<<endl;

    for(int i=0;i<ans.size();i++){
        cout<<ans[i].first<<endl<<ans[i].second<<"\n\n";
    }

    print_data(data, rows, cols);

    cout<<endl<<"There are total " << ans.size() <<" combinations"<<endl;
    return 0;
}

// for match : same character;
// for mismatch : s's character;
// for gap : _ character;