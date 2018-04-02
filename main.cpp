#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

struct cell{
    int x;
    int y;
    int grid;
    bool possible[10] = {true, true,true, true,true, true,true, true, true, true};
    int val=-1;
};

void  solve();

int remaining = 81;
cell sudoku[9][9];

void set_question(int a){
    switch(a){
        case 1:

//          sudoku[y][x]
            sudoku[0][1].val = 6;
            sudoku[0][4].val = 1;
            sudoku[0][5].val = 8;
            sudoku[0][6].val = 2;
            sudoku[1][2].val = 5;
            sudoku[1][8].val = 9;
            sudoku[2][2].val = 7;
            sudoku[2][3].val = 6;
            sudoku[2][6].val = 4;
            sudoku[2][7].val = 1;
            sudoku[2][8].val = 5;
            sudoku[3][4].val = 9;
            sudoku[3][5].val = 7;
            sudoku[3][6].val = 8;
            sudoku[4][0].val = 2;
            sudoku[4][1].val = 7;
            sudoku[4][3].val = 3;
            sudoku[4][5].val = 5;
            sudoku[4][7].val = 9;
            sudoku[4][8].val = 6;
            sudoku[5][2].val = 3;
            sudoku[5][3].val = 8;
            sudoku[5][4].val = 6;
            sudoku[6][0].val = 7;
            sudoku[6][1].val = 4;
            sudoku[6][2].val = 1;
            sudoku[6][5].val = 3;
            sudoku[6][6].val = 5;
            sudoku[7][0].val = 9;
            sudoku[7][6].val = 3;
            sudoku[8][2].val = 6;
            sudoku[8][3].val = 7;
            sudoku[8][4].val = 2;
            sudoku[8][7].val = 4;
            remaining = 81-34;
            break;
        case 2:

            sudoku[9][9] = {

            };
            break;
        case 3:

            sudoku[9][9] = {

            };
            break;
        }

}




void display(){
    printf("\n|-----------|-----------|-----------|\n");
    printf("|");
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(sudoku[i][j].val!=-1){
                if((j+1)%3==0)
                    printf(" %d |",sudoku[i][j].val);

                else{
                    printf(" %d  ",sudoku[i][j].val);
                }

            }
            else{
                if((j+1)%3==0)
                    printf("   |");
                    else{
                    printf("    ");
                }

            }
        }
        if((i+1)%3==0)
        printf("\n|-----------|-----------|-----------|\n|");
        else{
            printf("\n|");
        }
    }
    printf("\b");
}



void * col_thread(void *args){

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(sudoku[i][j].val!=-1){
                for(int k=0;k<9;k++){
                    if(sudoku[k][j].val==-1)
                    sudoku[k][j].possible[sudoku[i][j].val] = false;
                }
            }
        }
    }
//    printf("\ncol thread completed");
}
void *row_thread(void * args){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(sudoku[i][j].val!=-1){
                for(int k=0;k<9;k++){
                    if(sudoku[i][k].val==-1)
                        sudoku[i][k].possible[sudoku[i][j].val] = false;
                }
            }
        }
    }
//    printf("\nrow thread completed");
}
void *grid_thread(void * args){
    int * s = (int *) args;
    int val = *s;
    for(int i=val+0;i<val+3;i++){
        for(int j=val+0;j<val+3;j++){
            if(sudoku[i][j].val!=-1){
                for(int k=val+0;k<val+3;k++){
                    for(int l=val+0;l<val+3;l++){
                    if(sudoku[k][l].val==-1)
                        sudoku[k][l].possible[sudoku[i][j].val] = false;
                    }
                }
            }
        }
    }
//    printf("\nrow thread completed");
}
void * fill_value(void * args){
    int found =0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(sudoku[i][j].val==-1){
                int d = -1,count =0;
                for(int k=1;k<10;k++){
                    if(sudoku[i][j].possible[k]){
                        count++;
                        d = k;
                    }
                    if(count>1){
                        break;
                    }
                }
                if(count==1) {
                    sudoku[i][j].val = d;
                    remaining--;
                    found++;
                }
            }
        }
    }
    if(found!=0){
    printf("\nreamaining cells = %d",remaining);
    display();
    solve();
    }
}
void solve(){
    if(remaining>0){
    pthread_t p1, p2, p31, p32, p33, p4;
    pthread_create(&p1,NULL,col_thread,NULL);
    pthread_create(&p2,NULL,row_thread,NULL);
        int a[]  = {0};
        int b[]  = {3};
        int c[]  = {6};
    pthread_create(&p31,NULL,grid_thread,a);
    pthread_create(&p32,NULL,grid_thread,b);
    pthread_create(&p33,NULL,grid_thread,c);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p31, NULL);
    pthread_join(p32, NULL);
    pthread_join(p33, NULL);
    pthread_create(&p4,NULL,fill_value,NULL);
    pthread_join(p4,NULL);
    }
}


int main() {
    set_question(1);

    display();
    solve();



    return 0;
}


