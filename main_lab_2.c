//
// Created by itmo on 9/22/23.
//
#include <sys/stat.h>
#include <string.h>
#include "main_lab_2.h"
#include "graph.h"

extern FilesNodes filesNodes[maxNodesInList];
extern int fileNum;

const char *name = "result";

int main(int argc, char *argv[]) {
    if (argc < maxNodesInList) {
        if (argc > 1) {
            for (int i = 1; i < argc; i++) {
                FILE *input_file = fopen(argv[i], "r");
                if (input_file) {
                    filesNodes[fileNum] = initFileNodes();
                    yyin = input_file;
                    yyparse();
                    fclose(input_file);
                    fileNum++;
                } else {
                    printf("Не удалось открыть файл: %s\n", argv[1]);
                }
            }
            FilesNodes procedures = findProcedures();
            GraphConfig **cfgs = malloc(procedures.cnt * sizeof(GraphConfig *));
            for (int i = 0; i < procedures.cnt; ++i) {
                Fun fun = prepareFun(procedures.nodes[i]);
                GraphConfig *cfg = initGraphConfig(fun, 0, i);
                cfgs[i] = cfg;
            }
            mkdir(name, S_IRWXU);
            for (int i = 0; i < procedures.cnt; ++i) {
                char *filename = malloc(strlen(cfgs[i]->procedureName) + 5);
                sprintf(filename, "%s/%s.txt", name, cfgs[i]->procedureName);
                FILE *f = fopen(filename, "w+");
                fprintf(f, "digraph G {");
                graphConfigPrint(f, cfgs[i], i, cfgs, procedures.cnt);
                fprintf(f, "start [shape=Mdiamond]; end [shape=Msquare];\n}\n");
                fclose(f);
            }
            destroy();
        } else {
            printf("Использование: %s <input_file>\n", argv[0]);
        }
    } else {
        printf("Max input files: 1024");
        return 1;
    }
    return 0;
}