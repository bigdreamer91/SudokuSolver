//
//  main.cpp
//  SudokuSolverFinal
//
//  Created by Geethanjali Jeevanatham on 3/28/17.
//  Copyright © 2017 Geethanjali Jeevanatham. All rights reserved.
//

#include <iostream>
#include <set>
#include <queue>
using namespace std;

set<int> *map[81];
set<int> temp;
queue<int> queuearr;
void crosshatch(int matrix[9][9]);
queue<int> crosshatchqueue;

void update(int matrix[9][9],int updateindex, int val){
    int index;
    int maxcol;
    int maxrow;
    set<int> tem;
    int item;
    int value = 0;
    
    queuearr.push(updateindex);
    
    while(!queuearr.empty()){
        tem.clear();
        item = queuearr.front();
        queuearr.pop();
        int ix = item / 9;
        int iy = item - (ix *9);
        if(val == 0){
            value = *map[item]->begin();
        }
        else{
            value = val;
            val = 0;
        }
        
        matrix[ix][iy] = value;
        
        for(int il=0; il<9; il++){
            tem.clear();
            if(matrix[ix][il] == 0){
                index = ix*9+il;
                if(*map[index]->begin()!=0){
                    tem = *map[index];
                    map[index]->clear();
                    for(set<int>::iterator it = tem.begin(); it!=tem.end(); ++it){
                        if(*it != value){
                            map[index]->insert(*it);
                        }
                    }
                    if(map[index]->size()==1){
                        queuearr.push(index);
                    }
                }
            }
        }
        
        for(int il=0; il<9; il++){
            tem.clear();
            if(matrix[il][iy] == 0){
                index = il*9+iy;
                if(*map[index]->begin()!=0){
                    tem = *map[index];
                    map[index]->clear();
                    for(set<int>::iterator it = tem.begin(); it!=tem.end(); ++it){
                        if(*it != value){
                            map[index]->insert(*it);
                        }
                    }
                    if(map[index]->size()==1){
                        queuearr.push(index);
                    }
                }
            }
        }
        
        maxcol = iy+1;
        maxrow = ix+1;
        while(maxrow%3!=0){
            maxrow++;
        }
        while(maxcol%3!=0){
            maxcol++;
        }
        
        for(int x = maxrow-3; x<maxrow; x++){
            for(int y= maxcol-3; y<maxcol; y++){
                if(matrix[x][y]==0){
                    index = x*9+y;
                    if(*map[index]->begin()!=0){
                        tem = *map[index];
                        map[index]->clear();
                        for(set<int>::iterator it = tem.begin(); it!=tem.end(); ++it){
                            if(*it != value){
                                map[index]->insert(*it);
                            }
                        }
                        if(map[index]->size()==1){
                            queuearr.push(index);
                        }
                    }
                }
            }
        }
    }
}

void crosshatchstep(int matrix[9][9], int stepindex){
    int maxcol;
    int maxrow;
    int ix = 0;
    int index = 0;
    set<int> temp;
    int count = 0;
    int savetempindex = 0;
    
    //check for hidden singles in each block
        temp.clear();
    
        if(stepindex<3){
            ix = 0;
        }
        else if(stepindex < 6){
            ix = 3;
        }
        else if(stepindex < 9){
            ix = 6;
        }
        
        maxrow = ix+1;
        maxcol = ((ix%3)-3)+3+1;
        
        while(maxrow%3!=0){
            maxrow++;
        }
        while(maxcol%3!=0){
            maxcol++;
        }
        
        for(int x = maxrow-3; x<maxrow; x++){
            for(int y= maxcol-3; y<maxcol; y++){
                if(matrix[x][y]==0){
                    index = x*9+y;
                    for(set<int>::iterator it = map[index]->begin(); it!=map[index]->end(); ++it){
                        temp.insert(*it);
                    }
                }
            }
        }
    
    for(set<int>::iterator it = temp.begin(); it!=temp.end(); ++it){
        count = 0;
        for(int x = maxrow-3; x<maxrow; x++){
            for(int y= maxcol-3; y<maxcol; y++){
                if(matrix[x][y]==0){
                    index = x*9+y;
                    for(set<int>::iterator iter = map[index]->begin(); iter!=map[index]->end(); ++iter){
                        if(*iter==*it){
                            count++;
                            savetempindex = index;
                        }
                    }
                    if(count>1){
                        break;
                    }

                }
            }
            if(count > 1){
                break;
            }
        }
        
        if(count==1){
        update(matrix, savetempindex, *it);
            crosshatchqueue.push(savetempindex/9);
            crosshatchqueue.push(savetempindex-((savetempindex/9)*9));
        }
    }
    
    //check for hidden singles in each row
    temp.clear();
    
    for(int i=0; i<9; i++){
        index = stepindex*9 + i;
        if(matrix[stepindex][i]==0){
            for(set<int>::iterator iter = map[index]->begin(); iter!=map[index]->end(); ++iter){
                temp.insert(*iter);
            }
        }
        
    }
    
    for(set<int>::iterator iter = temp.begin(); iter!=temp.end(); ++iter){
        count = 0;
        for(int i=0; i<9; i++){
            index = stepindex*9+i;
            if(matrix[stepindex][i]==0){
                for(set<int>::iterator it=map[index]->begin(); it!=map[index]->end(); ++it){
                    if(*it==*iter){
                        count++;
                        savetempindex = index;
                    }
                }
                if(count>1){
                    break;
                }

            }
        }
        if(count==1){
            update(matrix, savetempindex, *iter);
            crosshatchqueue.push(savetempindex/9);
            crosshatchqueue.push(savetempindex-((savetempindex/9)*9));
        }
    }
    
    //check for hidden singles in each column
    temp.clear();
    for(int i=0; i<9; i++){
        index = i*9 + stepindex;
        if(matrix[i][stepindex]==0){
            for(set<int>::iterator iter = map[index]->begin(); iter!=map[index]->end(); ++iter){
                temp.insert(*iter);
            }
        }
        
    }
    
    for(set<int>::iterator iter = temp.begin(); iter!=temp.end(); ++iter){
        count = 0;
        for(int i=0; i<9; i++){
            index = i*9 + stepindex;
            if(matrix[i][stepindex]==0){
                for(set<int>::iterator it=map[index]->begin(); it!=map[index]->end(); ++it){
                    if(*it==*iter){
                        count++;
                        savetempindex = index;
                    }
                }
                if(count>1){
                    break;
                }
            }
            
        }
        if(count==1){
            update(matrix, savetempindex, *iter);
            crosshatchqueue.push(savetempindex/9);
            crosshatchqueue.push(savetempindex-((savetempindex/9)*9));
        }
    }

    
    
}

void crosshatch(int matrix[9][9]){
    for(int i=0; i<9; i++){
        crosshatchstep(matrix, i);
    }
    
    while(!crosshatchqueue.empty()){
        crosshatchstep(matrix, crosshatchqueue.front());
        crosshatchqueue.pop();
    } 
}

int init(int matrix[9][9]){
    int index;
    int maxcol;
    int maxrow;
    int lowest = 9;
    int lowestindex = 81;
    bool yes = false;
    
    for(int i=0; i<9; i++){
        temp.clear();
        for(int j=0; j<9; j++){
            temp.clear();
            if(matrix[i][j] == 0){
                index = i*9+j;
                map[index]->clear();
                
                for(int x=0; x< 9; x++){
                    if(matrix[i][x]!=0){
                        temp.insert(matrix[i][x]);
                    }
                }
                
                for(int x=0; x<9;x++){
                    if(matrix[x][j]!=0){
                        temp.insert(matrix[x][j]);
                    }
                }
                
                maxcol = j+1;
                maxrow = i+1;
                while(maxrow%3!=0){
                    maxrow++;
                }
                while(maxcol%3!=0){
                    maxcol++;
                }
                
                for(int x = maxrow-3; x<maxrow; x++){
                    for(int y= maxcol-3; y<maxcol; y++){
                        if(matrix[x][y]!=0){
                            temp.insert(matrix[x][y]);
                        }
                    }
                }
                
                for(int k=0; k<9; k++){
                    yes = false;
                    for(set<int>::iterator it=temp.begin(); it!=temp.end();++it){
                        if(*it-1 == k){
                            yes = true;
                            break;
                        }
                    }
                    if(yes==false){
                      //  cout << k+1 << "  " <<  index << endl;
                        map[index]->insert(k+1);
                    }
                    //cout << "\n" << endl;
                }
                
                if(map[index]->size()==1 && lowestindex==81){
                    //lowest = map[index]->size();
                    lowestindex = index;
                }
            }
        }
    }
    
    return lowestindex;
}

void printmap(){
    for(int i=0; i<81; i++){
        cout << "map[" << i << "] -> ";
        for(set<int>::iterator it = map[i]->begin(); it!=map[i]->end(); ++it){
            cout << *it << " ";
            
        }
        cout<<endl;
    }
}

bool isValidMatrix(int matrix[9][9]){
    bool validMatrix = true;
    int maxcol;
    int maxrow;
    
    for(int ia=0; ia<9; ia++){
        for(int ib=0; ib<9; ib++){
            
            for(int ic=0; ic<9; ic++){
                if(ic!=ib){
                    if(matrix[ia][ic] == matrix[ia][ib]){
                        validMatrix = false;
                        break;
                    }
                }
            }
            
            if(validMatrix==true){
                for(int ic=0; ic <9 ; ic++){
                    if(ic!=ia){
                        if(matrix[ic][ib] == matrix[ia][ib]){
                            validMatrix = false;
                            break;
                        }
                    }
                }
            }
            
            if(validMatrix==true){
                maxcol = ib+1;
                maxrow = ia+1;
                while(maxrow%3!=0){
                    maxrow++;
                }
                while(maxcol%3!=0){
                    maxcol++;
                }
                
                for(int x = maxrow-3; x<maxrow; x++){
                    for(int y= maxcol-3; y<maxcol; y++){
                        if(x!=ia || y!=ib){
                            if(matrix[x][y] == matrix[ia][ib]){
                                validMatrix = false;
                                break;
                            }
                        }
                    }
                    if(validMatrix==false){
                        break;
                    }
                }
            }
        }
        
        if(validMatrix==false){
            break;
        }
    }
    
    return validMatrix;

}

void printMatrix(int matrix[9][9]){
    for(int ia=0; ia<9; ia++){
        for(int ib=0; ib<9; ib++){
            cout << matrix[ia][ib] << "  ";
        }
        cout << endl;
    }
}

void lockedCandidates(int matrix[9][9]){
    
}

int main(int argc, const char * argv[]) {
    
    for(int i=0; i<81; i++){
        map[i] = new set<int>;
        map[i]->insert(0);
    }
    
    int matrix[9][9] = {
        {0,0,0,2,0,5,0,0,0},
        {2,0,0,0,0,0,0,0,4},
        {0,8,3,0,0,0,9,2,0},
        {3,0,8,9,0,7,2,0,6},
        {0,0,0,3,0,4,0,0,0},
        {0,0,0,0,5,0,0,0,0},
        {8,0,6,0,0,0,7,0,2},
        {0,3,0,6,0,8,0,9,0},
        {0,4,5,0,0,0,8,6,0}
    };
    
    int lowest = init(matrix);
    
    if(lowest!=81){
        update(matrix, lowest, 0);
    }
    
    bool isVal = isValidMatrix(matrix);
    
    if(!isVal){
        crosshatch(matrix);
    }
    
    isVal = isValidMatrix(matrix);
    
    if(isVal){
        cout << "Correct Solution" << endl;
        printMatrix(matrix);
    }
    else{
        cout << "incorrect solution" << endl;
        printMatrix(matrix);
    }
    
    return 0;
}
