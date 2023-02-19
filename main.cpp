/*
Author: Abir Haque
Last modified: 18 February 2023
Purpose: 
    Assign five programmers to five different departments given preferences from both departents and programmers.
    Use "gcc main.cpp -o main.o && ./main.o" to run.
*/

#include <iostream>
#include <fstream>
#include <string>
#include "./LinkedList.h"

#define ascii_int_to_int(ascii_integer) ascii_integer-48

using namespace std;

bool is_in(int* arr, int len, int x){
    for(int i=0;i<len;i++){
        if (arr[i]==x)
            return true;
    }
    return false;
}

int main(){
    
    int i = 0;int j = 0;int k = 0;int l = 0;
    string line;
    int prog_dep_prefs[10][6];
    LinkedList prog_stacks[5];
    LinkedList dep_stacks[5];


    //Get filename.
    ifstream file; 
    string filename;
    cout<<"Enter filename: ";
    cin>>filename;

    //Load file contents into 2D array.
    file.open(filename);
    if(file.is_open()){
        while(getline(file,line)){
            for(j=0;j<9;j++){
                if (j%2==0){
                    prog_dep_prefs[i][j/2]=ascii_int_to_int(line[j]);
                }
            }
            prog_dep_prefs[i][5]='\0';
            i++;
        }
        file.close();
    }

    //Load 2D array contents onto LinkedList. Highest priority is in the first index.
    for(i=4;i>=0;i--){
        for(j=0;j<5;j++){
            prog_stacks[j].insert(0,prog_dep_prefs[i+5][j]);
            dep_stacks[j].insert(0,prog_dep_prefs[i][j]);
        }
    }

    int assign[5]={0,0,0,0,0};

    
    while(is_in(assign,5,0)){
        //Iterate through all departments.
        for(i = 0; i < 5;i++){
            if (dep_stacks[i].get_length()==0){
                continue;
            }
            int requested_programmer=dep_stacks[i].get(0);
            while (is_in(assign,5,requested_programmer)&&dep_stacks[i].get_length()!=0){
                dep_stacks[i].remove(0);
                requested_programmer=dep_stacks[i].get(0);
            }
            if (dep_stacks[i].get_length()==0){
                continue;
            }

            //Find all possible conflicts between departments by iterating through departments and appending to dups.
            LinkedList* dups=new LinkedList();
            dups->append(i+1);
            for(j=0;j<5;j++){
                if (i==j||dep_stacks[j].get_length()==0)
                    continue;
                if (dep_stacks[j].get(0)==requested_programmer){
                    dups->append(j+1);
                }
            }

            //Assign programmers to dept based on whether there were dups found or not.
            int requested_dep;
            if(dups->get_length()==1&&assign[i]==0){
                prog_stacks[requested_programmer-1].empty_list();
                dep_stacks[i].empty_list();
                assign[i]=requested_programmer;
            }
            else{
                requested_dep=prog_stacks[requested_programmer-1].get(0);
                prog_stacks[requested_programmer-1].remove(0);
                //While the programmer has selected other depts as higher priority
                while (prog_stacks[requested_programmer-1].get_length()!=0&&!dups->is_in(requested_dep)&&!is_in(assign,5,requested_programmer)){
                    requested_dep=prog_stacks[requested_programmer-1].get(0);
                    prog_stacks[requested_programmer-1].remove(0);
                }
                prog_stacks[requested_programmer-1].empty_list();
                dep_stacks[requested_dep-1].empty_list();
                assign[requested_dep-1]=requested_programmer;
            }
            //Clear dept/prog choices if they already have completed assignments.
            for(j=0;j<5;j++){
                if (dep_stacks[j].is_in(requested_programmer)){
                    dep_stacks[j].remove(dep_stacks[j].index_of(requested_programmer));
                }
                if (prog_stacks[j].is_in(requested_dep)){
                    prog_stacks[j].remove(prog_stacks[j].index_of(requested_dep));
                }
            }
            delete dups;
        }
    }

    //Print results.
    for(i = 0; i < 5; i++){
        cout<<"Department #"<<i+1<<" will get Programmer #"<<assign[i]<<endl;
    }

    return 0;
}