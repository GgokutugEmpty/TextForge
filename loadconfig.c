/**==================================================================================================**
 * File: loadconfig.c
 * Author: [A.Goktug]
 * Date: [25/02/10]
 * Description: This file contains functions for loading configuration from a file (config.ini).
 *              Specifically, it manages the setting for whether coloring is enabled or not.
 * Usage: 
 *      - This file is used to load configuration from a file named "config.ini".
 * 
 * Dependencies:
 *      - None
 * 
 * Note:
 *      - The configuration file should contain a line with "coloring=true" or "coloring=false".
 *==================================================================================================*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIG_FILE "config.ini"

int coloring = 0;
	
int load_config()
{
    FILE *file = fopen(CONFIG_FILE, "r");
    if (file == NULL) 
	{
        perror("config.ini opening error");
        return -1;
    }

    char line[256];

    while (fgets(line, sizeof(line), file))
	{
        line[strcspn(line, "\r\n")] = 0;
        if (strstr(line, "coloring"))
		{
            if (strstr(line, "true")) 
			{
                coloring = 1;
            } else if (strstr(line, "false")) 
			{
                coloring = 0;
            }
        }
    }

    fclose(file);
     return 1;
}
