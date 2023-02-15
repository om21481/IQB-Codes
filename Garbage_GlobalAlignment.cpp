#include<iostream>
#include<string.h>
#include<vector>
using namespace std;

void global_align(vector< vector< pair<string, string> > > &ans, vector< vector< int > > &data){
    ans[0][0].first = "";
    ans[0][0].second = "";
    data[0][0] = 0;

    // now we have to somewhat like 1 based indexing
    // for columns gaps are added to source string and for rows gaps are added to s string
    string gaps = "_";
    for(int i=1;i<ans.size();i++){
        ans[i][0].first = gaps;
        gaps += "_";
        data[i][0] = -i;
    }   // for column

    gaps = "_";
    for(int i=1;i<ans[0].size();i++){
        ans[0][i].second = gaps;
        gaps += "_";
        data[0][i] = -i;
    }   // for rows

    return;
}

void make_best_possible_path(vector< vector< pair<string, string> > > &ans, vector< vector< int > > &data, string source, string s, int row, int col){
    char source_char = source[col-1];
    char s_char = s[row-1];

    int diagonal = -1, down = -1, right = -1; 
    // for match
    if(source_char == s_char){
        diagonal = data[row-1][col-1] + 2;      // matching Scheme
        down = data[row-1][col] - 1;            // for gaps
        right = data[row][col-1] - 1;            // for gaps

        if(diagonal >= down && diagonal >= right){
            // diagonal is greatest
            data[row][col] = diagonal;
            ans[row][col].first = ans[row-1][col-1].first + source_char;
            ans[row][col].second = ans[row-1][col-1].second + source_char;
        }
        else if(right >= diagonal && right >= down){
            // right is greatest
            data[row][col] = right;
            ans[row][col].first = ans[row][col-1].first + source_char;
            ans[row][col].second = ans[row][col-1].second + "_";
        }
        else if(down >= diagonal && down >= right){
            // down is greatest
            data[row][col] = down;
            ans[row][col].first = ans[row-1][col].first + "_";
            ans[row][col].second = ans[row-1][col].second + s_char;
        }
    }
    else{
        diagonal = data[row-1][col-1] -1;      // Mis-matching Scheme
        down = data[row-1][col] - 1;            // for gaps
        right = data[row][col-1] - 1;            // for gaps

        if(diagonal >= down && diagonal >= right){              // we will only take this when diagonal is strictly grater than right and down
            // diagonal is greatest
            data[row][col] = diagonal;
            ans[row][col].first = ans[row-1][col-1].first + source_char;
            ans[row][col].second = ans[row-1][col-1].second + s_char;
        }
        else if(right >= diagonal && right >= down){
            // right is greatest
            data[row][col] = right;
            ans[row][col].first = ans[row][col-1].first + source_char;
            ans[row][col].second = ans[row][col-1].second + "_";
        }
        else if(down >= diagonal && down >= right){
            // down is greatest
            data[row][col] = down;
            ans[row][col].first = ans[row-1][col].first + "_";
            ans[row][col].second = ans[row-1][col].second + s_char;
        }
    }


    return;

}
void make_full_allignment(vector< vector< pair<string, string> > > &ans, vector< vector< int > > &data, string source, string s){
    for(int i=1;i<ans.size();i++){
        for(int j=1;j<ans[i].size();j++){
            make_best_possible_path(ans, data, source, s, i, j);
        }
    }

    return;
}

void print_ans(vector< vector< pair<string, string> > > &ans){
    for(int i=0;i<ans.size();i++){
        for(int j=0;j<ans[i].size();j++){
            cout<<ans[i][j].first<<" , "<<ans[i][j].second<<"\t";
        }
        cout<<endl;
    }

    return;
}

int main(){
    string source = "", s = "";
    cin>>source;
    cin>>s;

    vector< vector< pair<string, string> > > ans;       // for source and s
    vector< pair<string, string> > temp;
    pair<string, string> p;
    p.first = "";
    p.second = "";

    vector< vector< int > > data;              // for storing the best scores
    vector<int> data_temp; 

    for(int i=0;i<source.size() + 1;i++){       // one extra box
        temp.push_back(p);
        data_temp.push_back(0);
    } 

    for(int i=0;i<s.size() + 1;i++){              // one extra box
        ans.push_back(temp);
        data.push_back(data_temp);
    }

    // for global alignment
    global_align(ans, data);
    
    // aligning the sequences
    make_full_allignment(ans, data, source, s);

    cout<<endl;

    string final_source = ans[s.size()][source.size()].first;
    string final_s = ans[s.size()][source.size()].second;
    cout<<final_source<<endl<<final_s<<endl; 

    cout<<data[s.size()][source.size()]<<endl;
    
    return 0;
}

// for match : same character;
// for mismatch : s's character;
// for gap : _ character;

// Input:
// ACCGGTAT
// ACCTATC