#include <iostream>
#include <string>
#include <vector>
#include <utility>

// there is an image filled with 0s and 1s. There is at most 
// one rectangle in this image filled with 0s, find the rectangle. Output 
// could be the coordinates of top-left and bottom-right elements of the rectangle, 
// or top-left element, width and height.


using namespace std;

vector<std::pair<int,int>> findTriangle(vector<vector<int>> rectangle){
    vector<std::pair<int,int>> res;

    for(int i = 0;i<rectangle.size();i++){
        for(int j = 0; j<rectangle[i].size();j++){

            if(rectangle[i][j] == 0){
                res.push_back(make_pair(i,j));
                int height = 1;
                int width = 1;

                while(height + i <rectangle.size() && rectangle[i+height][j]==0){
                    height++;

                }
                while(width + j <rectangle[0].size() && rectangle[i][j + width]==0){   
                    width++;

                }

                for(int m = i;m<i+height;m++){
                    for(int n = j;n<j+width;n++){
                        rectangle[m][n] = 1;
                }
               res.push_back(make_pair(i+height - 1,j+width - 1));
            }
            }

        }
    }
    return res;
}

void dfs(vector<vector<int>>& board,vector<pair<int,int>>& lst,int i,int j){
    if(i <0 || j <0 || i>=board.size() || j>=board[0].size() || board[i][j] == 1){
        return;
    }
    lst.push_back({i,j});
    board[i][j] = 1;
    dfs(board,lst,i+1,j);
    dfs(board,lst,i-1,j);
    dfs(board,lst,i,j+1);
    dfs(board,lst,i,j-1);

}

vector<vector<pair<int,int>>> find_shapes(vector<vector<int>> board){
    vector<vector<pair<int,int>>> res;
    for (size_t i = 0; i < board.size(); i++)
    {
       for(size_t j = 0;j<board[0].size(); j++){
           if(board[i][j] == 0){
               vector<pair<int,int>> lst;
                dfs(board,lst,i,j);
                res.push_back(lst);
           }

       }
    }
    
    return res;
}

int main(){
    // 0 0 0
    // 1 1 1
    // 0 0 1

    // 0 0 0
    // 1 1 1
    // 1 0 0
    vector<vector<int> > rectangle = {{0,0,0},{1,1,1},{1,0,0}};
    auto res2 = findTriangle(rectangle);
    for(int i = 0;i<res2.size();i+=2){
         cout<<"res:"<<res2[i].first << ","<<res2[i].second<<" => "<<res2[i+1].first<<","<<res2[i+1].second<<endl;
    }

    vector<vector<int> > board = {{0,0,0},{1,1,1},{1,0,0}};
    auto res = find_shapes(board);
    for(int i = 0;i<res.size();i++){
        cout<<"next\n";
        for(int j = 0; j< res[i].size(); j++){
                cout<<"res:"<<res[i][j].first << ","<<res[i][j].second<<endl;
        }

    }


    return 0;
}