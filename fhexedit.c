/**==================================================================================================**
 * File: fhexedit.c
 * Author: [A.Goktug]
 * Date: [25/02/10]
 * Description: A program that allows users to edit files in hexadecimal format.
 * 
 * Dependencies:
 *      - textforge.h
 *      - configs.h
 * 
 * Note:
 *      - This program provides a basic hex editor interface.
 *      - The 'Save' functionality has a known bug that corrupts the file (needs to be fixed).
 *==================================================================================================**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "textforge.h"
#include "configs.h"

#define MAX_LINES 100
#define MAX_COLS 256
#define HEX_COLS 16

void load_file_hex(const char *filename, unsigned char content[MAX_LINES][MAX_COLS], int *line_count)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL) 
	{
        perror("File Error");
        return;
    }

    *line_count = 0;
    while (!feof(file)) 
	{
        size_t bytes_read = fread(content[*line_count], 1, MAX_COLS, file);
        if (bytes_read == 0) break;

        (*line_count)++;
        if (*line_count >= MAX_LINES) 
		{
            break;
        }
    }

    fclose(file);
}

void save_file_hex(const char *filename, unsigned char content[MAX_LINES][MAX_COLS], int line_count)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL) 
	{
        perror("File Save Error");
        return;
    }

    for (int i = 0; i < line_count; i++) 
	{
        fwrite(content[i], 1, MAX_COLS, file);
    }

    fclose(file);
}

void display_hex_and_ascii(const unsigned char content[MAX_LINES][MAX_COLS], int line_count)
{
    for (int i = 0; i < line_count; i++) 
	{
        printw("%08X  ", i * HEX_COLS); 
        for (int j = 0; j < HEX_COLS; j++) 
		{
            if (j < MAX_COLS) 
			{
                printw("%02X ", content[i][j]);
            } else
			{
                printw("   ");
            }
        }
		
		//	
        // ASCII representation
        //
		printw(" |");
        for (int j = 0; j < HEX_COLS; j++) {
            if (j < MAX_COLS) {
                printw("%c", (content[i][j] >= 32 && content[i][j] <= 126) ? content[i][j] : '.');
            }
			else 
			{
			
			//
			//	Pad area
			//
                printw(" ");
            }
        }
        printw("|\n");
    }
}

void forgehexedit(const char *filename)
{
    unsigned char content[MAX_LINES][MAX_COLS] = {0};
    int line_count = 0;
    int x = 0, y = 0;

    load_file_hex(filename, content, &line_count);

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    int ch;
    while (1) 
	{
        clear();
        display_hex_and_ascii(content, line_count);
        move(y, (x * 3) + 10);
        refresh();

        ch = getch();

        if (ch == KEY_UP && y > 0) 
		{
            y--;
        } 
		else if (ch == KEY_DOWN && y < line_count - 1) 
		{
            y++;
        } 
		else if (ch == KEY_LEFT && x > 0) {
            x--;
        } 
		else if (ch == KEY_RIGHT && x < MAX_COLS - 1)
		{
            x++;
        } 
		else if (ch == 127 || ch == KEY_BACKSPACE) 
		{
            if (x > 0) 
			{
                content[y][x - 1] = 0;
                x--;
            } 
			else if (y > 0) 
			{
                x = MAX_COLS - 1;
                memmove(&content[y - 1], &content[y], (line_count - y) * MAX_COLS);
                line_count--;
                y--;
            }
        } 
		//
		//	Escape key for exiting
		//
		else if (ch == 27) 
		{
		//
			//  save_file_hex(filename, content, line_count);
				//	BUG! Fix it! Save is corrupting the file.
		//
			break;
        } else if (ch >= 32 && ch <= 126) 
		{ 
            if (x < MAX_COLS) 
			{
                content[y][x] = ch;
                x++;
            }
        }
    }

    endwin();
}
