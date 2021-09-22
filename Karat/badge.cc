// Given a list of people who enter and exit, find the people who entered without
// their badge and who exited without their badge.

// badge_records = [
//   ["Martha",   "exit"],
//   ["Paul",     "enter"],
//   ["Martha",   "enter"],
//   ["Martha",   "exit"],
//   ["Jennifer", "enter"],
//   ["Paul",     "enter"],
//   ["Curtis",   "enter"],
//   ["Paul",     "exit"],
//   ["Martha",   "enter"],
//   ["Martha",   "exit"],
//   ["Jennifer", "exit"],
// ]

// Expected output: ["Paul", "Curtis"], ["Martha"]
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <deque>
using namespace std;

vector<vector<string>> without_badge_list(vector<vector<string>> records){
    unordered_map<string,int> name_map;
    vector<string> enter,exit;
    for(auto record:records){
        string name = record[0];
        int b;
        if (record[1] == "exit"){
            b = -1;
        }
        if (record[1] == "enter"){
            b = 1;
        }
        name_map[name] += b;
    }

    for(auto elem: name_map){
        if(elem.second > 0){
            enter.push_back(elem.first);
        }
        if(elem.second < 0){
            exit.push_back(elem.first);
        }
    }
    return {enter,exit};
}

// 给 list of [name, time], time is string format: '1300' //下午一点
// return: list of names and the times where their swipe badges within one hour. if there are multiple intervals that satisfy the condition, return any one of them.
// name1: time1, time2, time3...
// name2: time1, time2, time3, time4, time5...
// example:
// input: [['James', '1300'], ['Martha', '1600'], ['Martha', '1620'], ['Martha', '1530']] 
// output: {
// 'Martha': ['1600', '1620', '1530']
// }

unordered_map<string,vector<string>> one_hr_access(vector<vector<string>> record){
    sort(record.begin(),record.end(),[](vector<string>& a,vector<string>& b){

         int a_num = std::stoi (a[1]);
         int b_num = std::stoi (b[1]);
         return a_num < b_num;
    }
    );
    unordered_map<string,vector<string>> res;
    unordered_map<string,vector<string>> ans;

    for (size_t i = 0; i < record.size(); i++)
    {
        if(res.find(record[i][0]) == res.end()){
            res[record[i][0]].push_back(record[i][1]);
            continue;
        }
        if(res[record[i][0]].size()){
            std::string::size_type sz,sz2; 
            int a_num = std::stoi (res[record[i][0]][0],&sz);
            int b_num = std::stoi (record[i][1],&sz2);
            if(b_num - a_num <= 100){
                res[record[i][0]].push_back(record[i][1]);
                continue;
            }
            if(res[record[i][0]].size() > 1){
                continue;
            }
            res[record[i][0]] = {record[i][1]};
        }   
    }

    for(auto elem: res){
        if(elem.second.size() >= 2){
            ans[elem.first] = move(elem.second);
        }
    }
    return ans;
    
}

int main(){
    vector<vector<string>> badge_records = {{"Martha","exit"},{"Paul","enter"},{"Martha","enter"},{"Martha","exit"},{"Jennifer", "enter"},{"paul", "enter"},{"Jennifer", "exit"},{"paul", "exit"}};
    auto res = without_badge_list(badge_records);
    for (size_t i = 0; i < res.size(); i++)
    {
        for (size_t j = 0; j < res[i].size(); j++)
        {
            cout<<res[i][j]<< " ";
        }
         cout<<endl;
        
    }
    vector<vector<string>> record = {{"James", "1300"},{"Martha", "1600"},{"Martha", "1620"},{"James", "1420"},{"Martha", "1530"},{"James", "1410"}};
    unordered_map<string,vector<string>> res = one_hr_access(record);
    for(auto elem: res){
        cout<<elem.first<<":";
        for (auto t: elem.second)
        {
           cout<<t<<",";
        }
        cout<<endl;
        
    }
    
    return 0;
}