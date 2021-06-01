#include <stdio.h>
#include <stdlib.h>
#include "../source/avm/avm.h"

void decoder(char *filename);

int main()
{
    decoder("bin.abc");
}

void decoder(char *filename)
{
    size_t len;
    char *currStr;

    unsigned magicNumber;

    unsigned totalNumberConsts;
    double *numConsts = NULL;

    unsigned totalStrConsts;
    char **strConsts = NULL;

    unsigned totalLibFuncs;
    char **libFuncs = NULL;

    unsigned totalUserFuncs;
    userfunc *userFuncs = NULL;

    unsigned totalInstructions;
    instruction *instructions = NULL;

    int i;

    FILE *stream;

    stream = fopen(filename, "rb"); // r for read, b for binary
    //read magic number
    fread(&magicNumber, sizeof(magicNumber), 1, stream);
    printf("Magic number :%u\n", magicNumber);

    //read numbers
    fread(&totalNumberConsts, sizeof(totalNumberConsts), 1, stream);
    printf("Total Number Consts :%u\n", totalNumberConsts);
    numConsts = (double *)malloc(totalNumberConsts * sizeof(double));
    for (i = 0; i < totalNumberConsts; i++)
    {
        fread(&numConsts[i], sizeof(numConsts[i]), 1, stream); //sizeof(double better?)
        printf("numConst[%d] = %f\n", i, numConsts[i]);
    }

    //read strings
    fread(&totalStrConsts, sizeof(totalStrConsts), 1, stream);
    printf("Total String Consts :%u\n", totalStrConsts);
    strConsts = (char **)malloc(totalStrConsts * sizeof(char *));
    for (i = 0; i < totalStrConsts; i++)
    {
        fread(&len, sizeof(len), 1, stream); //sizeof(double better?)
        printf("LEN %lu\n", len);
        currStr = (char *)malloc(sizeof(char) * (len + 1));

        fread(currStr, len, 1, stream);
        currStr[len] = '\0';
        //printf("strConst[%d] = %s\n", i, currStr);

        strConsts[i] = currStr; //mipws strdup(currStr); ?
        printf("strConst[%d] = %s\n", i, strConsts[i]);
    }

    //read lib funcs
    fread(&totalLibFuncs, sizeof(totalLibFuncs), 1, stream);
    printf("Total Lib Funcs :%u\n", totalLibFuncs);

    libFuncs = (char **)malloc(sizeof(totalLibFuncs * sizeof(char *)));
    for (i = 0; i < totalLibFuncs; i++)
    {
        fread(&len, sizeof(len), 1, stream); //sizeof(double better?)
        currStr = (char *)malloc(sizeof(char) * (len + 1));

        fread(currStr, len, 1, stream);
        currStr[len] = '\0';

        libFuncs[i] = currStr;

        printf("LibFuncs[%d] = %s\n", i, libFuncs[i]);
    }

    //read user funcs
    fread(&totalUserFuncs, sizeof(totalUserFuncs), 1, stream);
    printf("Total User Funcs :%u\n", totalUserFuncs);
    userFuncs = (userfunc *)malloc(sizeof(userfunc) * totalUserFuncs);
    for (i = 0; i < totalUserFuncs; i++)
    {
        unsigned address;
        unsigned locals;

        fread(&address, sizeof(address), 1, stream);
        fread(&locals, sizeof(locals), 1, stream);

        fread(&len, sizeof(len), 1, stream);
        currStr = (char *)malloc(sizeof(char) * (len + 1));

        fread(currStr, len, 1, stream);
        currStr[len] = '\0';

        userFuncs[i].address = address;
        userFuncs[i].localSize = locals;
        userFuncs[i].id = currStr;

        printf("UserFuncs[%d] = (%u %u %s)\n", i, userFuncs[i].address, userFuncs[i].localSize, userFuncs[i].id);
    }

    //read instructions
    fread(&totalInstructions, sizeof(totalInstructions), 1, stream);
    printf("Total Instructions :%u\n", totalInstructions);
    instructions = (instruction *)malloc(sizeof(instruction) * totalInstructions);
    for (i = 0; i < totalInstructions; i++)
    {
        unsigned opcode;
        unsigned result_type, arg1_type, arg2_type;
        unsigned result_val, arg1_val, arg2_val;
        fread(&opcode, sizeof(opcode), 1, stream);
        fread(&result_type, sizeof(result_type), 1, stream);
        fread(&result_val, sizeof(result_val), 1, stream);
        fread(&arg1_type, sizeof(arg1_type), 1, stream);
        fread(&arg1_val, sizeof(arg1_val), 1, stream);
        fread(&arg2_type, sizeof(arg2_type), 1, stream);
        fread(&arg2_val, sizeof(arg2_val), 1, stream);

        instructions[i].opcode = opcode; //
        instructions[i].result.type = result_type;
        instructions[i].result.val = result_val;
        instructions[i].arg1.type = arg1_type;
        instructions[i].arg1.val = arg1_val;
        instructions[i].arg2.type = arg2_type;
        instructions[i].arg2.val = arg2_val;

        printf("Opcode: %u\n", instructions[i].opcode);
        printf("Result type:  %u\n", instructions[i].result.type);
        printf("Result val:  %u\n", instructions[i].result.val);
        printf("Argument 1 type:  %u\n", instructions[i].arg1.type);
        printf("Argument 1 val:  %u\n", instructions[i].arg1.val);
        printf("Argument 2 type:  %u\n", instructions[i].arg2.type);
        printf("Argument 2 val:  %u\n", instructions[i].arg2.val);
    }

    fclose(stream);
}
