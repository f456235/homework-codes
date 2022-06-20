#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>
#include<set>
#include<algorithm>

#include<climits>
using namespace std;
enum SPOT_STATE {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

int player;
const int SIZE = 15;
std::array<std::array<int, SIZE>, SIZE> board;
#define INF INT_MAX
#define NINF INT_MIN
struct point {
    int x, y, score;
    point():point(0, 0) {};
    point(int a, int b) :x(a), y(b){};
    bool operator==(const point& rhs) const{
        return this->x == rhs.x && this->y == rhs.y;
    }
    bool operator!=(const point& rhs) const{
        return ! operator==(rhs);
    }
    point operator+(const point& rhs) const{
        return point(this->x + rhs.x, this->y + rhs.y);
    }
    point operator-(const point& rhs) const {
        return point(this->x - rhs.x, this->y - rhs.y);
    }
    bool operator<(const point& rhs) const {
       if(x!=rhs.x) return x<rhs.x;
       if(y!=rhs.y) return y<rhs.y;
       /* int num=SIZE/2;
        int num1=(rhs.x-num)*(rhs.x-num)+(rhs.y-num)*(rhs.y-num);
        int num2=(x-num)*(x-num)+(y-num)*(y-num);
        if(num1!=num2){
            return num1<num2;
        }*/
        return 0;
    }
};
point newpt;
class state {
    public:
        array<array<int, SIZE>, SIZE> board;
        set<point> move_space;
        int player, score;
        point best_point;
        state(array<array<int, SIZE>, SIZE> Gomoku_Board, int player_number) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    this->board[i][j] = Gomoku_Board[i][j];
                }
            }
            this->player = player_number;
            this->score=NINF;

        }
        state(state& ref) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    this->board[i][j] = ref.board[i][j];
                }
            }
            this->player = ref.player;

        }
        void next_move() {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE;j++) {
                    if (board[i][j] == EMPTY) {
                        this->move_space.insert(point(i, j));
                    }
                }
            }
            return;
        }
        void add_point(point& to_add,int type) {
           board[to_add.x][to_add.y]=type;
        }
        int evaluate_score() {
            int h = 0;
            //set<int,int> vis;
            int opponent = 3 - player;

            for(int i = 0; i<SIZE; i++){
                for(int j=0; j<SIZE; j++){
                    int win_possibilty=0;
                    if(board[i][j] == player){
                        if(j+1<SIZE && board[i][j+1] == player){  
                            win_possibilty++;
                            if(j+2<SIZE && board[i][j+2] == player){
                                win_possibilty++;
                                if(j+3<SIZE && board[i][j+3] == player){
                                    win_possibilty++;
                                    if(j+4<SIZE && board[i][j+4] == player){
                                        h+=150000;
                                        win_possibilty++;
                                        
                                    }
                                    else{
                                        int prob=0;
                                        if(j+4<SIZE && board[i][j+4] == 0){
                                            prob++;
                                        }
                                        if(j-1>=0 && board[i][j-1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h+=100000;
                                        }
                                        else if(prob == 1){
                                            h+=1200;
                                        }
                                        else if(!prob){
                                            win_possibilty-=3;
                                        }   
                                    }
                                }
                                else{
                                    int prob=0;
                                    if(j+3 < SIZE && board[i][j+3] == 0){
                                        prob++;
                                    }
                                    if(j-1>=0 && board[i][j-1] == 0){
                                        prob++;
                                    }
                                    if(prob==2){
                                        h+=1000;
                                    }
                                    else if(prob==1){
                                        h+=100;
                                    }
                                    else if(!prob){
                                        win_possibilty-=2;
                                    }
                                }
                            }
                            else{
                                int prob=0;
                                if(j+2 < SIZE && board[i][j+2]==0){
                                    prob++;
                                    if(j+3 < SIZE && board[i][j+3]==player){
                                        if(j+4 < SIZE && board[i][j+4]==player){
                                            if(j+5 < SIZE &&board[i][j+5]==opponent){
                                                h+=90000;
                                            }
                                            else if(j+5 < SIZE &&board[i][j+5]==0)
                                                h+=10000;
                                        }
                                    }
                                }
                                if(j-1 >= 0 && board[i][j-1] == 0){
                                    prob++;
                                }
                                if(prob==2){
                                    h+=100;
                                }
                                else if(prob == 1){
                                    h+=20;
                                }
                                else if(!prob){
                                    win_possibilty--;
                                }
                            }
                        }
                        if(i+1<SIZE && board[i+1][j] == player){  
                            win_possibilty++;
                            if(i+2<SIZE && board[i+2][j] == player){
                                win_possibilty++;
                                if(i+3<SIZE && board[i+3][j] == player){
                                    win_possibilty++;
                                    if(i+4<SIZE && board[i+4][j] == player){
                                        win_possibilty++;
                                        h+=150000;
                                    }
                                    else{
                                        int prob=0;
                                        if(i+4<SIZE && board[i+4][j] == 0){
                                            prob++;
                                        }
                                        if(i-1>=0 && board[i-1][j] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h+=100000;
                                        }
                                        if(prob == 1){
                                            h+=1200;
                                        }
                                        if(!prob){
                                           win_possibilty-=3;
                                        }   
                                    }
                                }
                                 else{
                                    int prob=0;
                                        if(i+3<SIZE && board[i+3][j] == 0){
                                            prob++;
                                        }
                                        if(i-1>=0 && board[i-1][j] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h+=1000;
                                        }
                                        if(prob == 1){
                                            h+=100;
                                        }
                                        if(!prob){
                                           win_possibilty-=2;
                                        }   
                                }
                            }
                            else{
                                 int prob=0;
                                  if(i+2<SIZE && board[i+2][j] == 0){
                                         prob++;
                                         if(i+3 < SIZE && board[i+3][j]==player){
                                            if(i+4 < SIZE && board[i+4][j]==player){
                                                if(j-1>=0 && board[i][j-1]==opponent && j+5 < SIZE &&board[i][j+5]==opponent){
                                                    h+=90000;
                                                }
                                                 else if(j-1>=0 && board[i][j-1]==player &&j+5 < SIZE &&board[i][j+5]==0)
                                                    h+=10000;
                                            }
                                        }
                                }
                                  if(i-1>=0 && board[i-1][j] == 0){
                                        prob++;
                                }
                                 if(prob == 2){
                                        h+=100;
                                }
                                if(prob == 1){
                                        h+=20;
                                }
                                if(!prob){
                                    win_possibilty--;
                                }   
                            }
                        }
                        if(i+1<SIZE && j+1<SIZE && board[i+1][j+1] == player){
                            win_possibilty++;
                            if(i+2<SIZE && j+2<SIZE && board[i+2][j+2] == player){
                                win_possibilty++;
                                if(i+3<SIZE && j+3<SIZE && board[i+3][j+3] == player){
                                    win_possibilty++;
                                    if(i+4<SIZE && j+4<SIZE && board[i+4][j+4] == player){
                                        win_possibilty++;
                                        h+=150000;
                                    }
                                     else{
                                        int prob=0;
                                        if(i+4<SIZE && j+4<SIZE &&board[i+4][j+4] == 0){
                                            prob++;
                                        }
                                        if(i-1>=0 && j-1>=0 && board[i-1][j-1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h+=100000;
                                        }
                                        if(prob == 1){
                                            h+=1200;
                                        }
                                        if(!prob){
                                            win_possibilty-=3;
                                        }   
                                    }
                                }
                                else{
                                    int prob=0;
                                        if(i+3<SIZE && j+3<SIZE &&board[i+3][j+3] == 0){
                                            prob++;
                                        }
                                        if(i-1>=0 && j-1>=0 && board[i-1][j-1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h+=1000;
                                        }
                                        if(prob == 1){
                                            h+=100;
                                        }
                                        if(!prob){
                                            win_possibilty-=2;
                                        }   
                                }
                            }
                              else{
                                    int prob=0;
                                        if(i+2<SIZE && j+2<SIZE &&board[i+2][j+2] == 0){
                                            prob++;
                                           if(i+3 < SIZE && j+3 < SIZE && board[i+3][j+3]==player){
                                            if(i+4 < SIZE && j+4 < SIZE && board[i+4][j+4]==player){
                                                if(i-1 >= 0 && j-1 >= 0 && board[i-1][j-1]==opponent &&
                                                 i+5 < SIZE && j+5 < SIZE && board[i+5][j+5]==opponent){
                                                    h+=90000;
                                                }
                                                 else if(i-1 >= 0 && j-1 >= 0 && board[i-1][j-1]==EMPTY &&
                                                  i+5 < SIZE && j+5 < SIZE && board[i+5][j+5]==0)
                                                    h+=10000;
                                                }
                                            }
                                        }
                                        if(i-1>=0 && j-1>=0 && board[i-1][j-1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h+=100;
                                        }
                                        if(prob == 1){
                                            h+=20;
                                        }
                                        if(!prob){
                                            win_possibilty--;
                                        }
                              }
                        }
                        if(i+1<SIZE && j-1>=0 && board[i+1][j-1] == player){
                            win_possibilty++;
                            if(i+2<SIZE && j-2>=0 && board[i+2][j-2] == player){
                                win_possibilty++;
                                if(i+3<SIZE && j-3>=0 && board[i+3][j-3] == player){
                                    win_possibilty++;
                                    if(i+4<SIZE && j-4>=0 && board[i+4][j-4] == player){
                                        win_possibilty++;
                                        h+=150000;
                                    }
                                     else{
                                        int prob=0;
                                        if(i+4<SIZE && j-4>=0 &&board[i+4][j-4] == 0){
                                            prob++;
                                        }
                                        if(i-1>=0 && j+1<SIZE && board[i-1][j+1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h+=100000;
                                        }
                                        if(prob == 1){
                                            h+=1200;
                                        }
                                        if(!prob){
                                           win_possibilty-=3;
                                        }   
                                    }
                                }
                                  else{
                                        int prob=0;
                                        if(i+3<SIZE && j-3>=0 &&board[i+3][j-3] == 0){
                                            prob++;
                                        }
                                        if(i-1>=0 && j+1<SIZE && board[i-1][j+1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h+=1000;
                                        }
                                        if(prob == 1){
                                            h+=100;
                                        }
                                        if(!prob){
                                           win_possibilty-=2;
                                        }   
                                    }
                                }
                                 else{
                                        int prob=0;
                                        if(i+2<SIZE && j-2>=0 &&board[i+2][j-2] == 0){
                                            prob++;
                                             if(i+3 < SIZE && j-3 < SIZE && board[i+3][j-3]==player){
                                                if(i+4 < SIZE && j-4 < SIZE && board[i+4][j-4]==player){
                                                    if(i-1 >= 0 && j-1 >= 0 && board[i-1][j-1] == opponent &&
                                                     i+5 < SIZE && j-5 < SIZE && board[i+5][j-5]==opponent){
                                                    h+=90000;
                                                    }
                                                    else if(i-1 >= 0 && j-1 >= 0 && board[i-1][j-1] == opponent &&
                                                        i+5 < SIZE && j-5 < SIZE && board[i+5][j-5]==0)
                                                        h+=10000;
                                                    }
                                            }
                                         }
                    
                                        if(i-1>=0 && j+1<SIZE && board[i-1][j+1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h+=100;
                                        }
                                        if(prob == 1){
                                            h+=20;
                                        }
                                        if(!prob){
                                           win_possibilty--;
                                        }   
                                }
                            }
                    }else if(board[i][j] == opponent){
                        //if(i>4 && i<11 && j>4 && j<11)h-=2,cout<<"NO\n";
                        if(j+1<SIZE && board[i][j+1] == opponent){
                            win_possibilty--;  
                            if(j+2<SIZE && board[i][j+2] == opponent){
                                win_possibilty--;
                                if(j+3<SIZE && board[i][j+3] == opponent){
                                    win_possibilty--;
                                    if(j+4<SIZE && board[i][j+4] == opponent){
                                        win_possibilty--;
                                        h-=150000;
                                    }
                                    else{
                                        int prob=0;
                                        if(j+4<SIZE && board[i][j+4] == 0){
                                            prob++;
                                        }
                                        if(j-1>=0 && board[i][j-1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h-=100000;
                                        }
                                        if(prob == 1){
                                            h-=1200;
                                        }
                                        if(!prob){
                                           win_possibilty+=3;
                                        }   
                                    }
                                }
                                else{
                                        int prob=0;
                                        if(j+3<SIZE && board[i][j+3] == 0){
                                            prob++;
                                        }
                                        if(j-1>=0 && board[i][j-1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h-=1000;
                                        }
                                        if(prob == 1){
                                            h-=100;
                                        }
                                        if(!prob){
                                           win_possibilty+=2;
                                        }   
                                }
                            }
                            else{
                                        int prob=0;
                                        if(j+2<SIZE && board[i][j+2] == 0){
                                            prob++;
                                            if(j+3 < SIZE && board[i][j+3]==opponent){
                                                if(j+4 < SIZE && board[i][j+4]==opponent){
                                                    if(j-1>=0 && board[i][j-1]==player && j+5 < SIZE &&board[i][j+5]==player){
                                                        h-=90000;
                                                    }
                                                    else if(j-1>=0 && board[i][j-1]==player &&j+5 < SIZE &&board[i][j+5]==0)
                                                         h-=10000;
                                                }
                                                else if(j+4 < SIZE &&board[i][j+4]==0){
                                                    //h-=70000;
                                                }
                                             }
                                        }
                                        if(j-1>=0 && board[i][j-1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h-=60;
                                        }
                                        if(prob == 1){
                                            h-=10;
                                        }
                                        if(!prob){
                                           win_possibilty++;
                                        }   
                                    }
                        }
                        if(i+1<SIZE && board[i+1][j] == opponent){  
                            win_possibilty--;
                            if(i+2<SIZE && board[i+2][j] == opponent){
                                win_possibilty--;
                                if(i+3<SIZE && board[i+3][j] == opponent){
                                    win_possibilty--;
                                    if(i+4<SIZE && board[i+4][j] == opponent){
                                        h-=150000;
                                       win_possibilty--;
                                    }
                                    else{
                                        int prob=0;
                                        if(i+4<SIZE && board[i+4][j] == 0){
                                            prob++;
                                        }
                                        if(i-1>=0 && board[i-1][j] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h-=100000;
                                        }
                                        if(prob == 1){
                                            h-=1200;
                                        }
                                        if(!prob){
                                            win_possibilty+=3;
                                        }   
                                    }
                                }
                               else{
                                        int prob=0;
                                        if(i+3<SIZE && board[i+3][j] == 0){
                                            prob++;
                                        }
                                        if(i-1>=0 && board[i-1][j] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h-=1000;
                                        }
                                        if(prob == 1){
                                            h-=100;
                                        }
                                        if(!prob){
                                            win_possibilty+=2;
                                        }   
                                }
                            }
                            else{
                                        int prob=0;
                                        if(i+2<SIZE && board[i+2][j] == 0){
                                            prob++;
                                             if(i+3 < SIZE && board[i+3][j]==opponent){
                                                if(i+4 < SIZE && board[i+4][j]==opponent){
                                                    if(i+5 < SIZE &&board[i+5][j]==player){
                                                        h-=90000;
                                                    }
                                                    else if(i+5 < SIZE &&board[i+5][j]==0)
                                                        h-=10000;
                                                }
                                            }
                                        }
                                        if(i-1>=0 && board[i-1][j] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h-=60;
                                        }
                                        if(prob == 1){
                                            h-=10;
                                        }
                                        if(!prob){
                                            win_possibilty++;
                                        }   
                            }
                        }
                        if(i+1<SIZE && j+1<SIZE && board[i+1][j+1] == opponent){
                            win_possibilty--;
                            if(i+2<SIZE && j+2<SIZE && board[i+2][j+2] == opponent){
                                win_possibilty--;
                                if(i+3<SIZE && j+3<SIZE && board[i+3][j+3] == opponent){
                                    win_possibilty--;
                                    if(i+4<SIZE && j+4<SIZE && board[i+4][j+4] == opponent){
                                        h-=150000;
                                        win_possibilty--;
                                    }
                                    else{
                                        int prob=0;
                                        if(i+4<SIZE && j+4<SIZE &&board[i+4][j+4] == 0){
                                            prob++;
                                        }
                                        if(i-1>=0 && j-1>=0 && board[i-1][j-1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h-=100000;
                                        }
                                        if(prob == 1){
                                            h-=1200;
                                        }
                                        if(!prob){
                                            win_possibilty+=3;
                                        }   
                                    }
                                }
                                else{
                                    int prob=0;
                                        if(i+3<SIZE && j+3<SIZE &&board[i+3][j+3] == 0){
                                            prob++;
                                        }
                                        if(i-1>=0 && j-1>=0 && board[i-1][j-1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h-=1000;
                                        }
                                        if(prob == 1){
                                            h-=100;
                                        }
                                        if(!prob){
                                            win_possibilty+=2;
                                        }
                                }
                            }
                             else{
                                    int prob=0;
                                        if(i+2<SIZE && j+2<SIZE &&board[i+2][j+2] == 0){
                                            prob++;
                                            if(i+3 < SIZE && j+3 < SIZE && board[i+3][j+3]==opponent){
                                                if(i+4 < SIZE && j+4 < SIZE && board[i+4][j+4]==opponent){
                                                    if(i+5 < SIZE && j+5 < SIZE && board[i+5][j+5]==player){
                                                        h-=90000;
                                                    }
                                                    else if(i+5 < SIZE && j+5 < SIZE && board[i+5][j+5]==0)
                                                        h-=10000;
                                                }
                                            }
                                        }
                                        if(i-1>=0 && j-1>=0 && board[i-1][j-1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h-=60;
                                        }
                                        if(prob == 1){
                                            h-=10;
                                        }
                                        if(!prob){
                                            win_possibilty++;
                                        }
                                }
                        }
                        if(i+1<SIZE && j-1>=0 && board[i+1][j-1] == opponent){
                            win_possibilty--;
                            if(i+2<SIZE && j-2>=0 && board[i+2][j-2] == opponent){
                                win_possibilty--;
                                if(i+3<SIZE && j-3>=0 && board[i+3][j-3] == opponent){
                                    win_possibilty--;
                                    if(i+4<SIZE && j-4>=0 && board[i+4][j-4] == opponent){
                                        h-=150000;
                                        win_possibilty--;
                                    }
                                     else{
                                        int prob=0;
                                        if(i+4<SIZE && j-4>=0 &&board[i+4][j-4] == 0){
                                            prob++;
                                        }
                                        if(i-1>=0 && j+1<SIZE && board[i-1][j+1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h-=100000;
                                        }
                                        if(prob == 1){
                                            h-=1200;
                                        }
                                        if(!prob){
                                            win_possibilty+=3;
                                        }   
                                    }
                                }
                                else{
                                    int prob=0;
                                        if(i+3<SIZE && j-3>=0 &&board[i+3][j-3] == 0){
                                            prob++;
                                        }
                                        if(i-1>=0 && j+1<SIZE && board[i-1][j+1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h-=1000;
                                        }
                                        if(prob == 1){
                                            h-=100;
                                        }
                                        if(!prob){
                                            win_possibilty+=2;
                                        } 
                                }
                            }
                            else{
                                    int prob=0;
                                        if(i+2<SIZE && j-2>=0 &&board[i+2][j-2] == 0){
                                            prob++;
                                               if(i+3 < SIZE && j-3 < SIZE && board[i+3][j-3]==opponent){
                                                if(i+4 < SIZE && j-4 < SIZE && board[i+4][j-4]==opponent){
                                                    if(i+5 < SIZE && j-5 < SIZE && board[i+5][j-5]==player){
                                                         h-=90000;
                                                    }
                                                    else if(i+5 < SIZE && j-5 < SIZE && board[i+5][j-5]==0)
                                                        h-=10000;
                                                    }
                                                }
                                        }
                                        if(i-1>=0 && j+1<SIZE && board[i-1][j+1] == 0){
                                            prob++;
                                        }
                                        if(prob == 2){
                                            h-=60;
                                        }
                                        if(prob == 1){
                                            h-=10;
                                        }
                                        if(!prob){
                                            win_possibilty++;
                                        } 
                                }
                        }
                    }
                    if(win_possibilty>1){
                        h+=win_possibilty*250;
                    }
                }
            }
            return h;
        }
};
int minimax(state cur, int depth, int alpha, int beta, bool maximizingPlayer);

point next_move(state &cur) {
    int best=minimax(cur, 2, NINF, INF, true);
    //cout<<"Best ("<<Best.x<<","<<Best.y<<")\n";
    cout<<player<<"\n";
    cout<<"current:"<<cur.evaluate_score()<<"\n";
    state fut=cur;
    fut.add_point(newpt,player);
    cout<<"future:"<<fut.evaluate_score()<<"\n";
    return newpt;
}
void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}

void write_valid_spot(std::ofstream& fout,state &st) {
    srand(time(NULL));
    /*int x, y;
    // Keep updating the output until getting killed.
    bool flag = false;
        // Choose a random spot.
    /*for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(st.board[i][j] == player){
                flag=true;
                break;
            }
        }
    }
  if(flag == true){ */
       // point next = next_move(st);
       // fout<<next.x<<" "<<next.y<<"\n";
   /* }else{
        if(board[SIZE/2][SIZE/2] == 0) fout<<SIZE/2<<" "<<SIZE/2;
        else fout<<(SIZE/2)-1<<" "<<SIZE/2;
    }*/
    //fout.flush();
    int x, y;
    int flag = 0;
    for(int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
             if(st.board[i][j] == player){
                 flag++;
                 break;
             }
         }
     }
    if(flag == 0||flag==1){ 
        if(board[SIZE/2][SIZE/2] == 0) fout<<SIZE/2<<" "<<SIZE/2;
        else if(board[(SIZE/2)-1][(SIZE/2)-1] == 0) fout<<(SIZE/2)-1<<" "<<(SIZE/2)-1;
        else fout<<(SIZE/2)+1<<" "<<SIZE/2;
        
    }else{
        point next = next_move(st);
        fout<<next.x<<" "<<next.y<<"\n";
    }
    fout.flush();    
}

int minimax(state cur, int depth, int alpha, int beta, bool maximizingPlayer) {
    if (depth == 0) {
        return cur.evaluate_score();
    }
    cur.next_move();
    if (maximizingPlayer) {
        int maxEval=NINF;
        for(auto pt : cur.move_space){
            int eval;
            state next=cur;
            next.add_point(pt,player);
            eval = minimax(next, depth - 1, alpha, beta, !maximizingPlayer);
            maxEval = max(eval, maxEval);
            if(eval == maxEval){
                cur.best_point=pt;
                if(depth==2){
                    newpt=pt;
                }
            }
            alpha = max(alpha, maxEval);
            if (beta < alpha) {
                break;
            }
        }
        newpt.score=maxEval;
        return maxEval;
    }
    else {
        int minEval=INF;
        for (point pt : cur.move_space)
        {
            int eval;
            state next=cur;
            next.add_point(pt,3-player);
            eval = minimax(next, depth - 1, alpha, beta,!maximizingPlayer);
            minEval = min(eval, minEval);
            if(eval == minEval){
                cur.best_point=pt;
                if(depth == 2)
                    newpt = pt;
            }
            beta = min(beta, minEval);
            if (beta < alpha) {
                break;
            }
        }
        newpt.score=minEval;
          return minEval;
    }
}

int main(int, char** argv) {
   std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    state init(board, player);
    write_valid_spot(fout, init);
    fin.close();
    fout.close();
    return 0;
}