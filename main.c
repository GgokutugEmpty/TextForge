/**==================================================================================================**
 * File: main.c
 * Author: [A.Goktug]
 * Date: [25/02/10]
 * Description: A program that allows editing files with optional hex editor mode.
 * Usage: 
 *      - To open a file for editing: ./TextForge <filename>
 *      - To open a file in hex editor mode: ./TextForge <filename> -h
 * 
 * Dependencies:
 *      - textforge.h
 *      - configs.h
 * 
 * Note:
 *      - This program provides a basic text editor - code editor with additional features like hex editing.
 *==================================================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "textforge.h"
#include "configs.h"

int main(int argc, char *argv[]) 
{
    FILE *file;

    if (argc < 2)
	{
        fprintf(stderr, "Usage: %s <filename> [-h for hex editor]\n", argv[0]);
        return 1;
    }
    if (argc == 3 && strcmp(argv[2], "-h") == 0) {
        forgehexedit(argv[1]);
        return 0;
    }
    file = fopen(argv[1], "r");
    if (file == NULL)
	{
        return 0; 
    } else 
	{
        load_config();
        forgewrite(argv[1]); 
    }

    fclose(file);
    return 0;
}