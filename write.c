/**==================================================================================================**
 * File: write.c
 * Author: [A.Goktug]
 * Date: [25/02/10]
 * Description: This file provides functionalities for editing files in a hex or text format. 
 *              It supports basic text editing features such as scrolling, backspace, and adding new lines. 
 *              The editor can highlight keywords and display text in different colors depending on configuration.
 *
 * Functions:
 *      - is_keyword: Checks if a given word is a keyword.
 *      - load_file: Loads a file into memory for editing.
 *      - save_file: Saves the content to a file.
 *      - forgewritecolored: Edits the file with keyword coloring enabled.
 *      - forgewritewhite: Edits the file without keyword coloring (plain text).
 *      - forgewrite: A wrapper that chooses the appropriate editor based on the `coloring` configuration.
 *
 * Dependencies:
 *      - ncurses.h (for terminal-based UI)
 *      - textforge.h (custom header for editing functions)
 *      - keywords.h (contains list of keywords for syntax highlighting)
 *      - configs.h (for reading configuration settings such as coloring)
 *
 * Note:
 *      - The keywords for syntax highlighting are loaded from `keywords.h` and configured in `configs.h`.
 *      - The configuration file `config.ini` controls whether syntax highlighting is enabled or not.
 *==================================================================================================***/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "textforge.h"
#include "keywords.h"
#include "configs.h"

#define MAX_LINES 100
#define MAX_COLS 256
#define NUM_KEYWORDS 32

int is_keyword(const char *word) 
{
    for (int i = 0; i < NUM_KEYWORDS; i++) 
	{
        if (strcmp(word, keywords[i]) == 0) 
		{
		
		//
		//	Return index number when found
		//
            return i;
        }
    }
    return -1;
}

void load_file(const char *filename, char content[MAX_LINES][MAX_COLS], int *line_count)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("File Error");
        return;
    }

    *line_count = 0;
    while (fgets(content[*line_count], MAX_COLS, file) != NULL) {
        content[*line_count][strcspn(content[*line_count], "\n")] = 0;
        (*line_count)++;
        if (*line_count >= MAX_LINES) {
            break;
        }
    }

    fclose(file);
}

void save_file(const char *filename, char content[MAX_LINES][MAX_COLS], int line_count)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("File Save Error");
        return;
    }

    for (int i = 0; i < line_count; i++) {
        fprintf(file, "%s", content[i]);
        if (content[i][strlen(content[i]) - 1] != '\n') {
            fprintf(file, "\n");
        }
    }

    fclose(file);
}

void forgewritecolored(const char *filename) 
{
    char content[MAX_LINES][MAX_COLS] = {0};
    int line_count = 0;
    int x = 0, y = 0;
    
    load_file(filename, content, &line_count);

    initscr();
    start_color();
    for (int i = 0; i < NUM_KEYWORDS; i++) 
    {
        init_pair(i + 1, i + 1, COLOR_BLACK);
    }

    raw();
    keypad(stdscr, TRUE);
    noecho();

    int ch;
    while (1) 
    {
        clear();

        for (int i = 0; i < line_count; i++)
        {
            int j = 0;
            while (content[i][j] != '\0')
            {
                char word[MAX_COLS] = {0};
                int k = 0;

                while (content[i][j] != ' ' && content[i][j] != '\0' && content[i][j] != '\n')
                {
                    word[k++] = content[i][j++];
                }
                word[k] = '\0';

                int keyword_index = is_keyword(word);
                if (keyword_index != -1) {
                    attron(COLOR_PAIR(keyword_index + 1)); 
                    printw("%s", word);
                    attroff(COLOR_PAIR(keyword_index + 1));
                } else {
                    printw("%s", word);
                }

                while (content[i][j] == ' ')
                {
                    printw(" ");
                    j++;
                }
            }
            printw("\n");
        }

        move(y, x);
        refresh();

        ch = getch();

        if (ch == KEY_UP && y > 0)
        {
            y--;
            if (x > strlen(content[y])) x = strlen(content[y]);
        } 
        else if (ch == KEY_DOWN && y < line_count - 1) 
        {
            y++;
            if (x > strlen(content[y])) x = strlen(content[y]);
        } 
        else if (ch == KEY_LEFT && x > 0) 
        {
            x--;
        } 
        else if (ch == KEY_RIGHT && x < strlen(content[y])) 
        {
            x++;
        } 
        else if (ch == 10) 
        {
            if (line_count < MAX_LINES - 1) 
            {
                memmove(&content[y + 1], &content[y], (line_count - y) * MAX_COLS);
                line_count++;

                strcpy(content[y + 1], &content[y][x]);
                content[y][x] = '\0'; 

                y++;
                x = 0;
            }
        } 
        else if (ch == 127 || ch == KEY_BACKSPACE) 
        {
            if (x > 0) 
            { 
                memmove(&content[y][x - 1], &content[y][x], strlen(content[y]) - x + 1);
                x--;
            } else if (y > 0) 
            { 
                x = strlen(content[y - 1]);
                strcat(content[y - 1], content[y]);
                memmove(&content[y], &content[y + 1], (line_count - y) * MAX_COLS);
                line_count--;
                y--;
            }
        } 
        else if (ch == 27) 
        {
            save_file(filename, content, line_count);
            break;
        } 
        else if (ch >= 32 && ch <= 126) 
        {
            memmove(&content[y][x + 1], &content[y][x], strlen(content[y]) - x + 1);
            content[y][x] = ch;
            x++;
        }
    }

    endwin();
}

void forgewritewhite(const char *filename) 
{
    char content[MAX_LINES][MAX_COLS] = {0};
    int line_count = 0;
    int x = 0, y = 0;
    
    load_file(filename, content, &line_count);

    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    
    raw();
    keypad(stdscr, TRUE);
    noecho();

    int ch;
    while (1) 
	{
        clear();

        for (int i = 0; i < line_count; i++) 
		{
            int j = 0;
            while (content[i][j] != '\0') {
                char word[MAX_COLS] = {0};
                int k = 0;

                while (content[i][j] != ' ' && content[i][j] != '\0' && content[i][j] != '\n') 
				{
                    word[k++] = content[i][j++];
                }
                word[k] = '\0';

                attron(COLOR_PAIR(1));
                printw("%s", word);
                attroff(COLOR_PAIR(1));

                while (content[i][j] == ' ') 
				{
                    printw(" ");
                    j++;
                }
            }
            printw("\n");
        }

        move(y, x);
        refresh();

        ch = getch();

        if (ch == KEY_UP && y > 0)
		{
            y--;
            if (x > strlen(content[y])) x = strlen(content[y]);
        } 
		else if (ch == KEY_DOWN && y < line_count - 1) 
		{
            y++;
            if (x > strlen(content[y])) x = strlen(content[y]);
        } 
		else if (ch == KEY_LEFT && x > 0)
		{
            x--;
        } 
		else if (ch == KEY_RIGHT && x < strlen(content[y]))
		{
            x++;
        } 
		else if (ch == 10) {
            if (line_count < MAX_LINES - 1) 
			{
                memmove(&content[y + 1], &content[y], (line_count - y) * MAX_COLS);
                line_count++;

                strcpy(content[y + 1], &content[y][x]);
                content[y][x] = '\0'; 

                y++;
                x = 0;
            }
        }
		else if (ch == 127 || ch == KEY_BACKSPACE) 
		{
            if (x > 0) { 
                memmove(&content[y][x - 1], &content[y][x], strlen(content[y]) - x + 1);
                x--;
            } 
			else if (y > 0)
			{ 
                x = strlen(content[y - 1]);
                strcat(content[y - 1], content[y]);
                memmove(&content[y], &content[y + 1], (line_count - y) * MAX_COLS);
                line_count--;
                y--;
            }
        } 
		else if (ch == 27) 
		{
            save_file(filename, content, line_count);
            break;
        } 
		else if (ch >= 32 && ch <= 126) 
		{
            memmove(&content[y][x + 1], &content[y][x], strlen(content[y]) - x + 1);
            content[y][x] = ch;
            x++;
        }
    }

    endwin();
}

void forgewrite(const char *destfilename)
{
    if (coloring)
        forgewritecolored(destfilename);
    else
        forgewritewhite(destfilename);
}
