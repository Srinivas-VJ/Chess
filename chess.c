/*
 *  CHESS
 *  Created by Srinivas V on 15/02/20.
 *  Copyright © 2020 Srinivas V. All rights reserved.
 */
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include <stdlib.h>
int board[8][8] = {-1,-2,-3,-4,-5,-3,-2,-1,
                    0,-6,-6,-6,-6,-6,-6,-6,
                    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                    -6 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                    0, 6, 6, 6, 6, 6 ,6, 6,
                    1 ,2, 3, 4, 5, 3 ,2, 1};
int tempboard[8][8] = {-1,-2,-3,-4,-5,-3,-2,-1,
    -6,-6,-6,-6,-6,-6,-6,-6,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
    6, 6, 6, 6, 6, 6 ,6, 6,
    1 ,2, 3, 4, 5, 3 ,2, 1};
int player = 1;
int inactive_moves;
int checkmate = 0;
int stalemate = 0;
int number_of_pawns = 0;
int number_of_pawns_temp = 0;
int black_rook1_moved;
int black_rook2_moved;
int white_rook1_moved;
int white_rook2_moved;
int white_king_moved;
int black_king_moved;
int isValidMove(int [][8],int ,int ,int ,int);
int makeMove(int [][8],int ,int ,int ,int);
int whiteSoldierMove(int [][8],int ,int ,int ,int);
int blackSoldierMove(int [][8],int ,int ,int ,int);
int horseMove(int [][8],int ,int ,int ,int);
int elephantMove(int [][8],int ,int ,int ,int );
int camelMove(int [][8],int ,int ,int ,int );
int kingMove(int [][8],int ,int ,int ,int );
int isCastle(int [][8],int ,int ,int ,int );
int isKingSafe(int [][8]);
int playerHasValidMove(void);
void castle(int ,int ,int ,int );
void pawn_promotion(int ,int );
void printBoard(void);
void printInvalidMove(void);
void printCheckmate(void);
void printStalemate(void);
void printThanks(void);
void print50(void);
void printDraw(void);
void printCheck(void);
int main()
{
    printf("\e[1;1H\e[2J\n\n");//clrscr
    black_rook1_moved = 0;
    black_rook2_moved = 0;
    white_rook1_moved = 0;
    white_rook2_moved = 0;
    white_king_moved = 0;
    black_king_moved = 0;
    player = 1;
    number_of_pawns_temp = 32;
    char move[4];
    printf("   ██████╗██╗  ██╗███████╗███████╗███████╗\n");
    printf("  ██╔════╝██║  ██║██╔════╝██╔════╝██╔════╝\n");
    printf("  ██║     ███████║█████╗  ███████╗███████╗\n");
    printf("  ██║     ██╔══██║██╔══╝  ╚════██║╚════██║\n");
    printf("  ╚██████╗██║  ██║███████╗███████║███████║\n");
    printf("   ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
    printf("\nPress enter key to continue.... ");
    getchar();
    while (playerHasValidMove())
    {
        if (number_of_pawns_temp == number_of_pawns)
            inactive_moves++;
        else
            inactive_moves = 1;
        number_of_pawns_temp = number_of_pawns;
        if (inactive_moves>50)
            break;
        printBoard();
        if (!isKingSafe(board))
            printCheck();
        printf("%s's turn\nEnter your move - ",player?"White":"Black");
        scanf("%s",move);
        printf("\e[1;1H\e[2J");
        int len,start[2],end[2];
        len = (int)strlen(move);
        if ((len == 4) && isalpha(move[0]) && isalpha(move[2]) && isdigit(move[1]) && isdigit(move[3]) )
        {
            switch(move [0])
            {
                case 'a':
                    start[1]=0;
                    break;
                case 'b':
                    start[1]=1;
                    break;
                case 'c':
                    start[1]=2;
                    break;
                case 'd':
                    start[1]=3;
                    break;
                case 'e':
                    start[1]=4;
                    break;
                case 'f':
                    start[1]=5;
                    break;
                case 'g':
                    start[1]=6;
                    break;
                case 'h':
                    start[1]=7;
                    break;
                default:
                    printInvalidMove();
                    continue;
            }
            start[0] = ('9' - move[1]) - 1;
            end[0]= ('9' - move[3]) - 1;
            if (start[0]>8 || end[0]>8)
            {
                printInvalidMove();
                continue;
            }
            switch(move [2])
            {
                case 'a':
                    end[1]=0;
                    break;
                case 'b':
                    end[1]=1;
                    break;
                case 'c':
                    end[1]=2;
                    break;
                case 'd':
                    end[1]=3;
                    break;
                case 'e':
                    end[1]=4;
                    break;
                case 'f':
                    end[1]=5;
                    break;
                case 'g':
                    end[1]=6;
                    break;
                case 'h':
                    end[1]=7;
                    break;
                default:
                    printInvalidMove();
                    continue;
            }
            if (isValidMove(board,start[0],start[1],end[0],end[1]))
            {
                if ((board[start[0]][start[1]] == 6 && start[0] == 1) || (board[start[0]][start[1]] == -6 && start[0] == 6))
                    pawn_promotion(start[0], start[1]);
                if(makeMove(board,start[0],start[1],end[0],end[1]))
                {
                    switch(board[end[0]][end[1]])
                    {
                        case 5:
                        case -5:
                            if (!player)
                                white_king_moved = 1;
                            else
                                black_king_moved = 1;
                            break;
                        case 1:
                        case -1:
                            if (start[0] == 0 && start[1] == 0)
                                black_rook1_moved = 1;
                            else if (start[0] == 0 && start[1] == 7)
                                black_rook2_moved = 1;
                            else if (start[0] == 7 && start[1] == 0)
                                white_rook1_moved = 1;
                            else if (start[0] == 7 && start[1] == 7)
                                white_rook2_moved = 1;
                            break;
                        default:
                            continue;
                    }
                    continue;
                }
                else
                    printInvalidMove();
                printf("\n %s king gets into check !\n",player?"White":"Black");        }

            else
                printInvalidMove();
        }
        else
            printInvalidMove();
    }
    printBoard();
    if (checkmate)
        printCheckmate();
    else if (stalemate)
    {
        printStalemate();
        printDraw();
    }
    else if (inactive_moves>50)
    {
        print50();
        printDraw();
    }
    printThanks();

}
void printCheck(void)
{
    printf("\x1b[31m");
    if (player)
    {
        printf("┬ ┬┬ ┬┬┌┬┐┌─┐  ┬┌─┬┌┐┌┌─┐  ┬┌┐┌  ┌─┐┬ ┬┌─┐┌─┐┬┌─ ┬\n");
        printf("│││├─┤│ │ ├┤   ├┴┐│││││ ┬  ││││  │  ├─┤├┤ │  ├┴┐ │\n");
        printf("└┴┘┴ ┴┴ ┴ └─┘  ┴ ┴┴┘└┘└─┘  ┴┘└┘  └─┘┴ ┴└─┘└─┘┴ ┴ o\n");
    }
    else
    {
        printf("┌┐ ┬  ┌─┐┌─┐┬┌─  ┬┌─┬┌┐┌┌─┐  ┬┌┐┌  ┌─┐┬ ┬┌─┐┌─┐┬┌─ ┬\n");
        printf("├┴┐│  ├─┤│  ├┴┐  ├┴┐│││││ ┬  ││││  │  ├─┤├┤ │  ├┴┐ │\n");
        printf("└─┘┴─┘┴ ┴└─┘┴ ┴  ┴ ┴┴┘└┘└─┘  ┴┘└┘  └─┘┴ ┴└─┘└─┘┴ ┴ o\n");
    }
    printf("\x1b[0m");
}
void printInvalidMove()
{
    inactive_moves--;
    printf("\x1b[31m");
    printf("╦┌┐┌┬  ┬┌─┐┬  ┬┌┬┐  ┌┬┐┌─┐┬  ┬┌─┐ ┬\n");
    printf("║│││└┐┌┘├─┤│  │ ││  ││││ │└┐┌┘├┤  │\n");
    printf("╩┘└┘ └┘ ┴ ┴┴─┘┴─┴┘  ┴ ┴└─┘ └┘ └─┘ o\n");
    printf("\x1b[0m");
}
void printCheckmate()
{
    printf("\x1b[32m");
    if (player)
    {
        printf("╔═╗┬ ┬┌─┐┌─┐┬┌─┌┬┐┌─┐┌┬┐┌─┐  ┬   ╦ ╦┬ ┬┬┌┬┐┌─┐  ┬ ┬┬┌┐┌┌─┐\n");
        printf("║  ├─┤├┤ │  ├┴┐│││├─┤ │ ├┤   │   ║║║├─┤│ │ ├┤   │││││││└─┐\n");
        printf("╚═╝┴ ┴└─┘└─┘┴ ┴┴ ┴┴ ┴ ┴ └─┘  o   ╚╩╝┴ ┴┴ ┴ └─┘  └┴┘┴┘└┘└─┘o\n");
    }
    else
    {
        printf("╔═╗┬ ┬┌─┐┌─┐┬┌─┌┬┐┌─┐┌┬┐┌─┐  ┬   ╔╗ ┬  ┌─┐┌─┐┬┌─  ┬ ┬┬┌┐┌┌─┐\n");
        printf("║  ├─┤├┤ │  ├┴┐│││├─┤ │ ├┤   │   ╠╩╗│  ├─┤│  ├┴┐  │││││││└─┐\n");
        printf("╚═╝┴ ┴└─┘└─┘┴ ┴┴ ┴┴ ┴ ┴ └─┘  o   ╚═╝┴─┘┴ ┴└─┘┴ ┴  └┴┘┴┘└┘└─┘o\n");
    }
    printf("\x1b[0m");

}
void printStalemate(){
    printf("\x1b[36m");
    printf("┌─┐┌┬┐┌─┐┬  ┌─┐┌┬┐┌─┐┌┬┐┌─┐  ┬\n");
    printf("└─┐ │ ├─┤│  ├┤ │││├─┤ │ ├┤   │\n");
    printf("└─┘ ┴ ┴ ┴┴─┘└─┘┴ ┴┴ ┴ ┴ └─┘  o\n");
    printf("\x1b[0m");

}
void printThanks(){
    printf("\x1b[32m");
    printf("╔╦╗┬ ┬┌─┐┌┐┌┬┌─┌─┐  ┌─┐┌─┐┬─┐  ┌─┐┬  ┌─┐┬ ┬┬┌┐┌┌─┐  ┬\n");
    printf(" ║ ├─┤├─┤│││├┴┐└─┐  ├┤ │ │├┬┘  ├─┘│  ├─┤└┬┘│││││ ┬  │\n");
    printf(" ╩ ┴ ┴┴ ┴┘└┘┴ ┴└─┘  └  └─┘┴└─  ┴  ┴─┘┴ ┴ ┴ ┴┘└┘└─┘  o\n");
    printf("\x1b[0m");

}
void print50(){
    printf("\x1b[36m");
    printf("╔═╗┬┌─┐┌┬┐┬ ┬  ┬┌┐┌┌─┐┌─┐┌┬┐┬┬  ┬┌─┐  ┌┬┐┌─┐┬  ┬┌─┐┌─┐  ┬\n");
    printf("╠╣ │├┤  │ └┬┘  ││││├─┤│   │ │└┐┌┘├┤   ││││ │└┐┌┘├┤ └─┐  │\n");
    printf("╚  ┴└   ┴  ┴   ┴┘└┘┴ ┴└─┘ ┴ ┴ └┘ └─┘  ┴ ┴└─┘ └┘ └─┘└─┘  o\n");
    printf("\x1b[0m");

}
void printDraw(){
    printf("\x1b[36m");
    printf("╔╦╗┌─┐┌┬┐┌─┐┬ ┬  ┌┬┐┬─┐┌─┐┬ ┬┌┐┌  ┬\n");
    printf("║║║├─┤ │ │  ├─┤   ││├┬┘├─┤││││││  │\n");
    printf("╩ ╩┴ ┴ ┴ └─┘┴ ┴  ─┴┘┴└─┴ ┴└┴┘┘└┘  o\n");
    printf("\x1b[0m");

}
void printBoard()
{
    char col_name[8] = {'a','b','c','d','e','f','g','h'};
     printf(" \t");
        for (int i=0; i<8;i++)
            printf(" %c ",col_name[i]);
        printf("\n\n");
        for (int row = 0,p=8;row<8;row++,p--)
        {
            printf(" %d\t",p);
            for (int col = 0;col<8;col++)
            {
                switch (board[row][col])
                {

                    case 0:
                        printf(" . ");
                        break;
                    case -1:
                        printf(" r ");
                        break;
                    case -2:
                        printf(" h ");
                        break;
                    case -3:
                        printf(" b ");
                        break;
                    case -4:
                        printf(" q ");
                        break;
                    case -5:
                        printf(" k ");
                        break;
                    case -6:
                        printf(" s ");
                        break;
                    case 1:
                        printf(" R ");
                        break;
                    case 2:
                        printf(" H ");
                        break;
                    case 3:
                        printf(" B ");
                        break;
                    case 4:
                        printf(" Q ");
                        break;
                    case 5:
                        printf(" K ");
                        break;
                    case 6:
                        printf(" S ");
                        break;
                    default:
                        break;
                }
            }
            printf("\n");
        }
}
int isValidMove(int Board[][8],int r1,int c1,int r2,int c2)
{
    int pawn = Board[r1][c1];
    if ((player && pawn>0) || ((player == 0 )&& pawn<0))
    {
        switch (pawn)
        {
            case 6:
                if (whiteSoldierMove(Board,r1,c1,r2,c2)) return 1;
                return 0;
                break;
            case -6:
                if (blackSoldierMove(Board,r1,c1,r2,c2)) return 1;
                return 0;
                break;
            case 5:
            case -5:
                if (kingMove(Board,r1,c1,r2,c2)) return 1;
                return 0;
                break;
            case 3:
            case -3:
                if (camelMove(Board,r1,c1,r2,c2))return 1;
                return 0;
                break;
            case 2:
            case -2:
                if (horseMove(Board,r1,c1,r2,c2)) return 1;
                return 0;
                break;
            case 1:
            case -1:
                if (elephantMove(Board,r1,c1,r2,c2)) return 1;
                return 0;
                break;
            case 4:
            case -4:
                if (elephantMove(Board,r1,c1,r2,c2) || camelMove(Board,r1,c1,r2,c2))
                    return 1;
                return 0;
                break;
        }
        return 1;
    }
    return 0;
}
int makeMove(int Board[][8],int r1,int c1,int r2,int c2)
{
    int temp,res;
    temp = Board[r2][c2];
    Board[r2][c2] = Board[r1][c1];
    Board[r1][c1] = 0;
    if (!isKingSafe(Board))
    {
        Board[r1][c1] = Board[r2][c2];
        Board[r2][c2] = temp;
        res = 0; ;
    }
    else
    {
        res = 1;
        player = player?0:1;
    }
    return res;
}
int whiteSoldierMove(int Board[][8],int r1,int c1,int r2,int c2)
{
    int res;
    if (c1 == c2 )
    {
        if ((r1 == 6) && (Board[r2][c2] == 0) && (Board[r1 - 1][c2] == 0) &&  (r2==4 || r2==5))
            res = 1;
        else if ((r2+1) == r1 && (Board[r2][c2] == 0))
            res = 1;
        else
            res = 0;
    }
    else if ((Board[r2][c2]<0) && (r2 == (r1 - 1)) && (c2 == (c1 - 1) ||  c2 == (c1+1)))
        res = 1;
    else
        res = 0;
    return res;
}
int blackSoldierMove(int Board[][8],int r1,int c1,int r2,int c2)
{
    int res;
    if (c1 == c2 )
    {
        if ((r1 == 1) && (board[r2][c2] == 0) && (Board[r1 + 1][c2] == 0) &&  (r2==3 || r2==2))
            res = 1;
        else if ((r2-1) == r1 && (Board[r2][c2] == 0))
            res = 1;
        else
            res = 0;
    }
    else if ((Board[r2][c2]>0) && (r2 == (r1 + 1)) && (c2 == (c1 - 1) ||  c2 == (c1+1)))
        res = 1;
    else
        res = 0;
    return res;
}
int horseMove(int Board[][8],int r1,int c1,int r2,int c2)
{
    int res;
    if (player && Board[r2][c2]>0) return 0;
    else if (Board[r2][c2]<0) return 0;
    if (((r2 == (r1+2)) || (r2 == (r1-2))) && ((c2 == (c1+1)) || (c2 == (c1-1))))
        res = 1;
    else if (((c2 == (c1+2)) || (c2 == (c1-2))) && ((r2 == (r1+1)) || (r2 == (r1-1))))
        res = 1;
    else
        res = 0;
    return res;
}
int elephantMove(int Board[][8],int r1,int c1,int r2,int c2)
{
    int res = 1;
    if (player && Board[r2][c2]>0) return 0;
    else if (!player && Board[r2][c2]<0) return 0;
    if (r1 == r2)
    {
        if (c1>c2)
        {
            for(int i = (c1-1);i>c2;i--)
            {
                if (Board[r2][i] == 0) continue;
                res = 0;
                break;
            }
        }
        else if (c2>c1)
        {
            for(int i = (c1+1);i<c2;i++)
            {
                if (Board[r2][i] == 0) continue;
                res = 0;
                break;
            }
        }
        else
            return 0;
    }
    else if(c1 == c2)
    {
        if (r1>r2)
        {
            for(int i = (r1-1);i>r2;i--)
            {
                if (Board[i][c2] == 0)
                    continue;
                else{
                res = 0;
                break;
                }
            }
        }
        else if (r2>r1)
        {
            for(int i = (r1+1);i<r2;i++)
            {
                if (Board[i][c2] == 0) continue;
                res = 0;
                break;
            }
        }
        else
            return 0;
    }
    else
        return 0;
    return res;
}
int camelMove(int Board[][8],int r1,int c1,int r2,int c2)
{
    int res = 1;
    if (player)
    {
        if (Board[r2][c2]>0)
            return 0;
    }
    else
        if (Board[r2][c2]<0)
            return 0;
    if (r2>r1 && c2>c1)
    {
        if ((r2 - r1) == (c2 -c1))
        {
            for(int i = r1+1,j = c1+1;i<r2;i++,j++)
            {
                if (Board[i][j] == 0)
                    continue;
                res = 0;
                break;
            }
        }
        else
            res = 0;
    }
    else if(r2>r1 && c2<c1)
    {
        if ((r2 - r1) == (c1 - c2))
        {
            for(int i = r1+1,j = c1-1;i<r2;i++,j--)
            {
                if (Board[i][j] == 0)
                    continue;
                res = 0;
                break;
            }
        }
        else
            res = 0;
    }
    else if(r1>r2 && c2>c1)
    {
        if ((r1 - r2) == (c2 - c1))
        {
            for(int i = r1-1,j = c1+1;j<c2;i--,j++)
            {
                if (Board[i][j] == 0)
                    continue;
                res = 0;
                break;
            }
        }
        else
            res = 0;
    }
    else if(r2<r1 && c2<c1)
    {
        if ((r1 - r2) == (c1 - c2))
        {
            for(int i = r1-1,j = c1-1;i<r2;i--,j--)
            {
                if (Board[i][j] == 0)
                    continue;
                res = 0;
                break;
            }
        }
        else
            res = 0;
    }
    else
        res = 0;
    return res;
}
int kingMove(int Board[][8],int r1,int c1,int r2,int c2)
{
    int res = 0;
    if (r2 == r1 && !(c2 == c1 + 1 || c2 == c1 - 1))
        if (isCastle(Board,r1,c1,r2,c2))
        {
            castle(r1,c1,r2,c2);
            return 1;
        }
    if (player)
    {
        if (Board[r2][c2]>0)
            return 0;
    }
    else
        if (Board[r2][c2]<0)
            return 0;
    if ((r2 == r1 + 1 || r2 == r1 -1) &&  (c2 == c1 + 1 || c2 == c1 -1))
        res =  1;
    else if ((r2 == r1) && (c2 == c1 + 1 || c2 == c1 - 1) )
        res = 1;
    else if ((c2 == c1) && (r2 == r1 + 1 || r2 == r1 - 1) )
        res = 1;
    else
        res = 0;
    return res;
}
int isCastle(int Board[][8],int r1,int c1,int r2,int c2)
{
    if (!isKingSafe(Board))
        return 0;
    int res = 0;
    if (r1 == 0 && c1 == 4)
    {
        if (black_king_moved)
            return 0;
        if (c2 == 6 && !black_rook2_moved && (Board[0][7] == -1))
        {
            for (int i = c1+1;i<=6;i++)
            {
                if (Board[r1][i] == 0)
                {
                    res = 1;
                    continue;
                }
                return 0;
            }
        }
        else if (c2 == 2 && !black_rook1_moved && (Board[0][0] == -1))
        {
            for (int i = c1-1;i>=1;i--)
            {
                if (Board[r1][i] == 0)
                {
                    res = 1;
                    continue;
                }
                return 0;
            }
        }
    }
    else if (r1 == 7 && c1 == 4)
    {
        if (white_king_moved)
            return 0;
        if (c2 == 6 && !white_rook2_moved && (board[7][7] == 1))
        {
            for (int i = c1+1;i<=6;i++)
            {
                if (Board[r1][i] == 0)
                {
                    res = 1;
                    continue;
                }
                return 0;
            }
        }
        else if (c2 == 2 && !white_rook1_moved  && (board[7][0] == 1))
        {
            for (int i = c1-1;i>=1;i--)
            {
                if (Board[r1][i] == 0)
                {
                    res = 1;
                    continue;
                }
                return 0;
            }
        }
    }
    return res;
}
void castle(int r1,int c1,int r2,int c2)
{
    if (r1 == 0)
    {
        if (c2 == 6)
        {
            board[0][7] = 0;
            board[0][5] = -1;
        }
        if (c2 == 2)
        {
            board[0][0] = 0;
            board[0][3] = -1;
        }
    }
    else
    {
        if (c2 == 6)
        {
            board[7][7] = 0;
            board[7][5] = 1;
        }
        if (c2 == 2)
        {
            board[7][0] = 0;
            board[7][3] = 1;
        }
    }
}
void pawn_promotion(int r1, int c1)
{
    char ch;
    printf("Which pawn do you want to promote?\n ");
    if (player)
    {
        printf("Enter Q for Queen\n\tH for Horse\n\tR for Rook\n\tB for Bishop\n");
        fflush(stdin);
        scanf(" %c",&ch);
        switch (ch)
        {
            case 'Q':
                board[r1][c1] = 4;
                break;
            case 'H':
                board[r1][c1] = 2;
                break;
            case 'R':
                board[r1][c1] = 1;
                break;
            case 'B':
                board[r1][c1] = 3;
                break;
            default:
                printf("Invalid input!\nPlease enter a valid input\n");
                pawn_promotion(r1,c1);
        }
    }
    else
    {
        printf("Enter q for Queen\n\th for Horse\n\tr for Rook\n\tb for Bishop\n");
        fflush(stdin);
        scanf(" %c",&ch);
        switch (ch)
        {
            case 'q':
                board[r1][c1] = -4;
                break;
            case 'h':
                board[r1][c1] = -2;
                break;
            case 'r':
                board[r1][c1] = -1;
                break;
            case 'b':
                board[r1][c1] = -3;
                break;
            default:
                printf("Invalid input!\nPlease enter a valid input\n");
                pawn_promotion(r1,c1);
        }
    }
}
int isKingSafe(int Board[][8])
{
    int r = -1,c = -1;
    for(int i = 0;i<8;i++)
    {
        for(int j = 0;j<8;j++)
        {
            if (((Board[i][j] == 5) && player) || ((Board[i][j] == -5) & !player) )
            {
                r = i;
                c = j;
                i = 8;
                break;
            }
        }
    }
    if (player)
    {
        player = 0;
        for(int i = 0;i<8;i++)
        {
            for(int j = 0;j<8;j++)
            {
                if (Board[i][j]>=0)
                    continue;
                else if (isValidMove(Board,i,j,r,c))
                {
                    player = 1;
                    return 0;
                }
            }
        }
        player = 1;
    }
    else
    {
        player = 1;
        for(int i = 0;i<8;i++)
        {
            for(int j = 0;j<8;j++)
            {
                if (Board[i][j]<=0)
                    continue;
                else if (isValidMove(Board,i,j,r,c))
                {
                    player = 0;
                    return 0;
                }
            }
        }
        player = 0;
    }
    return 1;
}
int playerHasValidMove()
{
    number_of_pawns = 0;
    int i,j;
    for (i = 0;i<8;i++)
        for(j = 0;j<8;j++)
        {
            tempboard[i][j] = board[i][j];
            if (board[i][j] != 0)
                number_of_pawns++;
        }
    int r = -1,c = -1;
    for (r = 0;r<8;r++)
    {
        for(c = 0;c<8;c++)
        {
            if ((board[r][c] == 0) || (player && board[r][c]<0) || (!player && board[r][c]>0))
                continue;
            for (i = 0;i<8;i++)
                for(j = 0;j<8;j++)
                    if(isValidMove(board,r, c, i, j))
                    {
                        tempboard[i][j] = tempboard[r][c];
                        tempboard[r][c] = 0;
                        if(isKingSafe(tempboard))
                        {
                            tempboard[i][j] = board[i][j];
                            tempboard[r][c] = board[r][c];
                            return 1;
                        }
                        tempboard[i][j] = board[i][j];
                        tempboard[r][c] = board[r][c];
                    }
        }
    }
    if (!isKingSafe(board))
        checkmate = 1;
    else
        stalemate = 1;
    player = player?0:1;
    return 0;
}

