#ifndef TEXTFORGE_H
#define TEXTFORGE_H

void forgewrite(const char *destfilename);
int load_config();
void load_file(const char *filename, char content[100][256], int *line_count);
void forgehexedit(const char *filename);
#endif
