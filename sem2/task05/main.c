#include <stdio.h>
#include "main.h"
#include "errors.h"

int get_k_name(int *k, char **name, int *arg, int argc, char *argv[]){
        if(sscanf(argv[*arg], "%d", k) != 1 || *arg >= argc)
                return ERROR_INPUT;
        (*arg)++;
        if(*k != 0)
                return SUCCESS;
        if(*arg >= argc)
                return ERROR_INPUT;
        else
                *name = argv[(*arg)++];
        return SUCCESS;
}
