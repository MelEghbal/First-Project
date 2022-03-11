#include <iostream>
#include <cstring>
#include "clui.h"
using namespace std;
#define simple 5
#define sim_mine 4
#define intermediate 12
#define inter_mine 28
#define advanced 20
#define ad_mine 96
#define max 25
#define up 'w'
#define down 's'
#define right 'd'
#define left 'a'
#define select ' '
int SIDES , MINES , TOTAL , ind=0 , last_i=-1;
//last_i for last initialized elemnt, ind for index
char real_field[max][max] , playing_field[max][max];
struct player
{
    char name[50];
    int score = 0;
    char board[max][max];
    char real_board[max][max];
    int movement = 0;
    int flags = 0;
    int sides;
    int mines;
    bool won_or_lost;
};
player save[max];
void play();
void menu();
void board_initialize(char board1[][max] , char board2[][max])
{
    for(int i=0 ; i < SIDES ; i++)
        for(int j=0 ; j < SIDES ; j++)
            board1[i][j] = board2[i][j];
}
void save_everything()
{
    board_initialize(save[ind].board , playing_field);
    board_initialize(save[ind].real_board , real_field);
    save[ind].sides = SIDES;
    save[ind].mines = MINES;
}
void menu_press(int key , int cursor_row , int cursor_col)
{
    switch(key)
    {
        case up:
            cursor_to_pos(--cursor_row , cursor_col);
            break;
        case down:
            if(cursor_row == 5)
                break;
            cursor_to_pos(++cursor_row , cursor_col);
            break;
    }
}
void choose_difficulty()
{
    init_clui();
    std::cout << "Choose a difficulty level or pesonalize the board:" << endl;
    change_color_rgb(54, 241, 247);
    std::cout << "> ";
    reset_color();
    std::cout << "personalization" << endl;
    change_color_rgb(18, 255, 57);
    std::cout << "> ";
    reset_color(); 
    std::cout << "Simple" << endl; 
    change_color_rgb(255, 174, 0);
    std::cout << "> ";
    reset_color();
    std::cout << "Intermediate" << endl; 
    change_color_rgb(255 , 0 , 0);
    std::cout << "> ";
    reset_color();
    std::cout << "advaced" << endl;
    cursor_to_pos(2 , 18);
    int key=0 , cursor_x = get_cursor_x() , cursor_y = get_cursor_y();
    while(key != ' ')
    {
        key = getch();
        cursor_x = get_cursor_x();
        cursor_y = get_cursor_y();
        menu_press(key , cursor_x , cursor_y);
    }
    clear_screen();
    switch(cursor_x)
    {
        case 2:
        {
            clear_screen();
            std::cout << "Enter the number of rows and columns of the board you want to play in please:" << endl;
            cin >> SIDES;
            TOTAL = SIDES*SIDES;
            printf("The number of mines is better to be between %d and %d.\nSelect a number from the range please:\n" , TOTAL/5 , TOTAL/3);  
            cin >> MINES;
            clear_screen();
            break;  
        }
        case 3:
        {
            SIDES = simple;
            MINES = sim_mine;
            TOTAL = SIDES*SIDES;
            break;
        }
        case 4:
        {
            SIDES = intermediate;
            MINES = inter_mine;
            TOTAL = SIDES*SIDES;
            break;
        }
        case 5:
        {
            SIDES = advanced;
            MINES = ad_mine;
            TOTAL = SIDES*SIDES;
            break;
        }
    }
}
void press(int key , int cursor_row , int cursor_col)
{
    switch(key)
    {
        case up:
        {
            cursor_row -= 2;
            cursor_to_pos(cursor_row , cursor_col);
            break;
        }
        case down:
        {
            if(cursor_row == 2*SIDES - 1)
               break;
            cursor_row += 2;
            cursor_to_pos(cursor_row , cursor_col);
            break;
        }
        case right:
        {
            if(cursor_col == 4*SIDES - 1)
               break;
            cursor_col += 4;
            cursor_to_pos(cursor_row , cursor_col);
            break;
        }
        case left:
        {
            cursor_col -= 4;
            cursor_to_pos(cursor_row , cursor_col);
            break;
        }
    }
}
bool validity(int i , int j)
{
    if(i < SIDES && j < SIDES && i >= 0 && j >= 0)
        return true;
    return false;
}
void bombing(int first_row , int first_column)
{
    int isbomb_i , isbomb_j;
    for(int num=0 ; num < MINES ; num++)
    {
        isbomb_i = rand()%SIDES;
        isbomb_j = rand()%SIDES;
        if((isbomb_i == first_row && isbomb_j == first_column) || real_field[isbomb_i][isbomb_j] == 'B')
        {
            num--;
            continue;
        }
        real_field[isbomb_i][isbomb_j] = 'B';
    }
}
char mine_count(char field[][max] , int i , int j)
{
    char count='.'; // '.' means 0
    if(field[i][j] != 'B')
    {
        if(validity(i-1 , j) && field[i-1][j] == 'B')
        {
            if(count != '.')
                count ++;
            else
                count = '1';
        }
        if(validity(i+1 , j) && field[i+1][j] == 'B')
        {
            if(count != '.')
                count ++;
            else
                count = '1';
        }
        if(validity(i , j-1) && field[i][j-1] == 'B')
        {
            if(count != '.')
                count ++;
            else
                count = '1';
        }
        if(validity(i , j+1) && field[i][j+1] == 'B')
        {
            if(count != '.')
                count ++;
            else
                count = '1';
        }
        if(validity(i-1 , j-1) && field[i-1][j-1] == 'B')
        {
            if(count != '.')
                count ++;
            else
                count = '1';
        }
        if(validity(i+1 , j+1) && field[i+1][j+1] == 'B')
        {
            if(count != '.')
                count ++;
            else
                count = '1';
        }
        if(validity(i-1 , j+1) && field[i-1][j+1] == 'B')
        {
            if(count != '.')
                count ++;
            else
                count = '1';
        }
        if(validity(i+1 , j-1) && field[i+1][j-1] == 'B')
        {
            if(count != '.')
                count ++;
            else
                count = '1';
        }
    }
    else
        count = 'B';
    return count;
}
bool is_mine(int i , int j)
{
    if(playing_field[i][j] == 'B')
        return false;
        //is mine
    else
        return true;
        //isn't mine
}
void theboard(int first_row , int first_column)
{
    bombing(first_row , first_column);
    for(int i=0 ; i < SIDES ; i++)
        for(int j=0 ; j < SIDES ; j++)
            real_field[i][j] = mine_count(real_field , i , j);
}
void uncover(int i , int j)
{
    int row , col;
    if(real_field[i][j] != '.' || !validity(i , j))
        return;
    if(validity(i-1 , j) && real_field[i-1][j] != 'B' && playing_field[i-1][j] != 'F' && playing_field[i-1][j] != real_field[i-1][j])
    {
        row = i - 1;
        while(validity(row , j) && real_field[row][j] == '.')
        {
            playing_field[row][j] = real_field[row][j];
            save[ind].movement++;
            row--;
            uncover(row , j);
        }
        if(validity(row , j) && real_field[row][j] != 'B' && playing_field[row][j] != 'F' && playing_field[row][j] != real_field[row][j])
        {
            playing_field[row][j] = real_field[row][j];
            save[ind].movement++;
        }
    }
    if(validity(i+1 , j) && real_field[i+1][j] != 'B' && playing_field[i+1][j] != 'F' && playing_field[i+1][j] != real_field[i+1][j])
    {
        row = i + 1;
        while(validity(row , j) && real_field[row][j] == '.')
        {
            playing_field[row][j] = real_field[row][j];
            save[ind].movement++;
            row++;
            uncover(row , j);
        }
        if(validity(row , j) && real_field[row][j] != 'B' && playing_field[row][j] != 'F' && playing_field[row][j] != real_field[row][j])
        {
            playing_field[row][j] = real_field[row][j];
            save[ind].movement++;
        }
    }
    if(validity(i , j-1) && real_field[i][j-1] != 'B' && playing_field[i][j-1] != 'F' && playing_field[i][j-1] != real_field[i][j-1])
    {
        col = j - 1;
        while(validity(i , col) && real_field[i][col] == '.')
        {
            playing_field[i][col] = real_field[i][col];
            save[ind].movement++;
            col--;
            uncover(i , col);
        }
        if(validity(i , col) && real_field[i][col] != 'B' && playing_field[i][col] != 'F' && playing_field[i][col] != real_field[i][col])
        {
            playing_field[i][col] = real_field[i][col];
            save[ind].movement++;
        }
    }
    if(validity(i , j+1) && real_field[i][j+1] != 'B' && playing_field[i][j+1] != 'F' && playing_field[i][j+1] != real_field[i][j+1])
    {
        col = j + 1;
        while(validity(i , col) && real_field[i][col] == '.')
        {
            playing_field[i][col] = real_field[i][col];
            save[ind].movement++;
            col++;
            uncover(i , col);
        }
        if(validity(i , col) && real_field[i][col] != 'B' && playing_field[i][col] != 'F' && playing_field[i][col] != real_field[i][col])
        {
            playing_field[i][col] = real_field[i][col];
            save[ind].movement++;
        }
    }
    if(validity(i-1 , j-1) && real_field[i-1][j-1] != 'B' && playing_field[i-1][j-1] != 'F' && playing_field[i-1][j-1] != real_field[i-1][j-1])
    {
        row = i - 1;
        col = j - 1;
        while(validity(row , col) && real_field[row][col] == '.')
        {
            playing_field[row][col] = real_field[row][col];
            save[ind].movement++;
            row--;
            col--;
            uncover(row , col);
        } 
        if(validity(row , col) && real_field[row][col] != 'B' && playing_field[row][col] != 'F' && playing_field[row][col] != real_field[row][col])
        {
            playing_field[row][col] = real_field[row][col];
            save[ind].movement++; 
        } 
    }
    if(validity(i+1 , j+1) && real_field[i+1][j+1] != 'B' && playing_field[i+1][j+1] != 'F' && playing_field[i+1][j+1] != real_field[i+1][j+1])
    {
        row = i + 1;
        col = j + 1;
        while(validity(row , col) && real_field[row][col] == '.')
        {
            playing_field[row][col] = real_field[row][col];
            save[ind].movement++;
            row++;
            col++;
            uncover(row , col);
        }
        if(validity(row , col) && real_field[row][col] != 'B' && playing_field[row][col] != 'F' && playing_field[row][col] != real_field[row][col])
        {
            playing_field[row][col] = real_field[row][col];
            save[ind].movement++;
        }
    }
    if(validity(i-1 , j+1) && real_field[i-1][j+1] != 'B' && playing_field[i-1][j+1] != 'F' && playing_field[i-1][j+1] != real_field[i-1][j+1])
    {
        row = i - 1;
        col = j + 1;
        while(validity(row , col) && real_field[row][col] == '.')
        {
            playing_field[row][col] = real_field[row][col];
            save[ind].movement++;
            row--;
            col++;
            uncover(row , col);
        }
        if(validity(row , col) && real_field[row][col] != 'B' && playing_field[row][col] != 'F' && playing_field[row][col] != real_field[row][col])
        {
            playing_field[row][col] = real_field[row][col];
            save[ind].movement++;
        }
    }
    if(validity(i+1 , j-1) && real_field[i+1][j-1] != 'B' && playing_field[i+1][j-1] != 'F' && playing_field[i+1][j-1] != real_field[i+1][j-1])
    {
        row = i + 1;
        col = j - 1;
        while(validity(row , col) && real_field[row][col] == '.')
        {
            playing_field[row][col] = real_field[row][col];
            save[ind].movement++;
            row++;
            col--;
            uncover(row , col);
        }
        if(validity(row , col) && real_field[row][col] != 'B' && playing_field[row][col] != 'F' && playing_field[row][col] != real_field[row][col])
        {
            playing_field[row][col] = real_field[row][col];
            save[ind].movement++;
        }
    }
}
void flag(char i , char j , int& count , int& full_board)
{
    //1. removing the flag  
    if(playing_field[i][j] == 'F')
    {  
        playing_field[i][j] = ' ';
        full_board--;
        count--;
    }
    //2. putting the flag
    else if(count <= MINES)
    {
        playing_field[i][j] = 'F';
        full_board++;
        count++;    
    }
}
void print_field(char field[][max])
{
    for(int i=0 ; i < SIDES ; i++)
    {
        for(int j=0 ; j < SIDES ; j++)
        {
            if(field[i][j] == 0)
                cout << "|   ";
            else
                std::cout << "| " <<  field[i][j] << " ";
        }
        std::cout << "|\n\n";
    }
}
void save_scores(player& save)
{
    switch(SIDES)
    {
        case simple:    
            save.score++;
            break;
        case intermediate:  
            save.score += 3;
            break;
        case advanced: 
            save.score += 5;
            break;
    }
    if(SIDES > simple && SIDES < intermediate)
        save.score += 2;
    else if(SIDES > intermediate && SIDES < advanced)
        save.score += 4;
    else if(SIDES > advanced)
        save.score += 6; 
}
void win_or_lose(player& save , int row , int col)
{
    if(save.movement == TOTAL && playing_field[row][col] != 'B')
    {
        std::cout << "YOU WON!\n:)))))))" << endl;
        print_field(playing_field);
        save_scores(save);
    }
    else
    {
        //flags were mines or not ...
        //shows the bomb cells when i lose ...
        for(int i=0 ; i < SIDES ; i++)
        {
            for(int j=0 ; j < SIDES ; j++)
            {
                if(playing_field[i][j] == 'F' && real_field[i][j] != 'B')
                    playing_field[i][j] = 'X';
                if(playing_field[i][j] == 0 && real_field[i][j] == 'B')
                    playing_field[i][j] = 'B';
            }     
        }
        print_field(playing_field);
        play_beep();
        std::cout << "GAME OVER!\n))))))))):" << endl;
    }
    save.won_or_lost = true;
    delay(4000); 
}
int convert_x(int x)
{
    return (x+1)/4 - 1;
}
int convert_y(int y)
{
    return(y+1)/2 - 1;
}
void new_game()
{
    save[ind].won_or_lost = false;
    for(int i=0 ; i < max ; i++)
        for(int j=0 ; j < max ; j++)
            real_field[i][j] = 0;
    for(int i=0 ; i < max ; i++)
        for(int j=0 ; j < max ; j++)
            playing_field[i][j] = 0;
    char name[50];
    choose_difficulty();
    //FIRST SELECTION
    int c_row = 1 , c_column = 3 , row , column;
    print_field(playing_field);
    cursor_to_pos(1 , 3);
    int key = getch();
    while(key != ' ' && key != 'f' && key != 'o' && key != 'q')
    {
        key = getch();
        c_row = get_cursor_x();
        c_column = get_cursor_y();
        press(key , c_row , c_column);
    }
    column = convert_x(c_column);
    row = convert_y(c_row);
    switch(key)
    {
        case 'f':
            //First choice can't be marked as flag
            play_beep();
            break;
        case 'o':
            save_everything();
            save_scores(save[ind]);
            play(); 
            break;
        case 'q':
            play();
            break;
        case ' ':
            save_cursor();
            theboard(row , column);
            //saves the real board
            playing_field[row][column] = real_field[row][column];
            save[ind].movement++;
            uncover(row , column);
            clear_screen();
            print_field(playing_field);
            restore_cursor();
            break;
    }
}
void load_game(char name[])
{
    for(int i=0 ; i <= last_i ; i++)
    {
        if(strcmp(save[i].name , name) == 0)
        {
            ind = i;
            SIDES = save[ind].sides;
            TOTAL = SIDES*SIDES;
            if(save[ind].won_or_lost)
            {
                save[ind].flags = 0;
                save[ind].movement = 0;
                new_game();
                return;
            }
            else
            {
                MINES = save[ind].mines;
                board_initialize(real_field , save[ind].real_board);
                board_initialize(playing_field , save[ind].board);
                return;
            }
        }
    }
    play_beep();
    menu();
}
void leader_board()
{
    player temp;
    //bubble sort
    for(int i=0 ; i < last_i ; i++)
    {
        for(int j=0 ; j < last_i-i ; j++)   
        {
            if(save[j].score < save[j+1].score)
            {
                temp = save[j];
                save[j] = save[j+1];
                save[j+1] = temp;
            }
        }
    }
    for(int k=0 ; k < 5 ; k++)
        printf("%d. %s : %d\n" , k+1 , save[k].name , save[k].score);
    delay(5000);
}
void change_user()
{
    char name[50];
    cout << "Enter the name you want to continue playing with:" << endl;
    cin >> name;
    for(int i=0 ; i <= last_i ; i++)
    {
        if(strcmp(save[i].name , name) == 0)
        {
            ind = i;
            SIDES = save[ind].sides;
            TOTAL = SIDES*SIDES;
            if(save[ind].won_or_lost)
            {
                save[ind].flags = 0;
                save[ind].movement = 0;
                new_game();
                return;
            }
            else
            {
                MINES = save[ind].mines;
                board_initialize(real_field , save[ind].real_board);
                board_initialize(playing_field , save[ind].board);
                return;
            }
        }
    }
    ind = ++last_i;
    strcpy(save[ind].name , name);
    new_game();
}
void menu()
{
    init_clui();
    char name[50];
    char new_g[9] = "New Game";
    char load_g[10] = "Load Game";
    char change_name[12] = "Change User";
    char leader_b[13] = "Leader Board";
    char exit[5] = "Quit";
    clear_screen();
    save_cursor();
    cursor_to_pos(2 , 1);
    change_color_rgb(255 , 0 , 0);
    std::cout << "> ";
    reset_color();
    std::cout << load_g << endl;
    change_color_rgb(255 , 0 , 0);
    std::cout << "> ";
    reset_color(); 
    std::cout << change_name << endl; 
    change_color_rgb(255 , 0 , 0);
    std::cout << "> ";
    reset_color();
    std::cout << leader_b << endl; 
    change_color_rgb(255 , 0 , 0);
    std::cout << "> ";
    reset_color();
    std::cout << exit << endl;
    restore_cursor(); 
    change_color_rgb(255 , 0 , 0);
    std::cout << "> ";
    reset_color();
    std::cout << new_g;
    cursor_to_pos(1 , 15);
    int key = 0 , cursor_x = get_cursor_x() , cursor_y = get_cursor_y();
    while(key != ' ')
    {
        key = getch();
        cursor_x = get_cursor_x();
        cursor_y = get_cursor_y();
        menu_press(key , cursor_x , cursor_y);
    }
    switch(cursor_x)
    {
    case 1: //new game
        clear_screen();
        ind = ++last_i;
        std::cout << "Enter your name please:" << endl;
        cin >> name;
        strcpy(save[ind].name , name);
        new_game();
        break;
    case 2: //load game
        clear_screen();
        cout << "Enter the name you want to continue playing with:" << endl;
        cin >> name;
        load_game(name);
        break;
    case 3: //change user
        clear_screen();
        change_user();
        break;
    case 4: //leader board
        clear_screen();
        leader_board();
        menu();
        break;
    case 5:
        quit();
    }
    clear_screen();
}
void play()
{
    init_clui();
    menu();
    int c_row = get_cursor_x() , c_column = get_cursor_y() , row , column;
    column = convert_x(c_column);
    row = convert_y(c_row);
    //AFTER FIRST SELECTION
    print_field(playing_field);
    cursor_to_pos(1 , 3);
    int key;
    while(is_mine(row , column) && save[ind].movement < TOTAL)
    {
        key = 0;
        while(key != ' ' && key != 'f' && key != 'o' && key != 'q')
        {
            key = getch(); 
            c_row = get_cursor_x();
            c_column = get_cursor_y();
            press(key , c_row , c_column);
        }
        column = convert_x(c_column);
        row = convert_y(c_row);
        switch(key)
        {
            case ' ':
            {
                if(playing_field[row][column] == real_field[row][column] && real_field[row][column] != 0 || playing_field[row][column] == 'F')
                {
                    save_cursor();
                    play_beep();
                    restore_cursor();
                    continue;
                }
                playing_field[row][column] = real_field[row][column];
                uncover(row , column);
                save[ind].movement++;
                save_cursor();
                clear_screen();
                print_field(playing_field);
                restore_cursor();
                break;
            }
            case 'f':
            {
                if(playing_field[row][column] == real_field[row][column] && real_field[row][column] != 0)
                {
                    save_cursor();
                    play_beep();
                    restore_cursor();
                    continue;
                }
                if(save[ind].flags == MINES && playing_field[row][column] != 'F')
                {
                    play_beep();
                    break;
                }
                save_cursor();
                flag(row , column , save[ind].flags , save[ind].movement);
                clear_screen();
                print_field(playing_field);
                restore_cursor();
                break;
            }
            case 'o':
                save_everything();
                play();
                break;
            case 'q':
                play();
                break;
        }
    }
    clear_screen();
    win_or_lose(save[ind] , row , column);
    play();
}
int main()
{
    init_clui();
    play();
    return 0;
}
