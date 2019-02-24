//function_trace.c
#include <stdio.h>
#define __USE_GNU
#include <dlfcn.h>
static FILE *fp_trace=NULL;
static int nDepth = 0;
void  __cyg_profile_func_enter(void *func, void *caller) __attribute__((no_instrument_function));
void  __cyg_profile_func_exit(void *func, void *caller) __attribute__((no_instrument_function));
 
void __attribute__((constructor)) traceBegin(void) {
  fp_trace = fopen("func_trace.out", "w");
}
 
void __attribute__((destructor)) traceEnd(void) {
  if (fp_trace != NULL) {
    fclose(fp_trace);
    fp_trace = NULL;
  }
}
 
 
void __cyg_profile_func_enter(void *func, void *caller) 
{
    nDepth ++;
    for(int i = 0 ; i < nDepth ; i++)
    {
        if(fp_trace)
        {
            fprintf(fp_trace,"\t");
        }
        printf("\t");
    }
    Dl_info info;
    if (dladdr(func, &info) != 0) 
    {
        if(fp_trace)
        {
            fprintf(fp_trace,"Enter:[%s,%s] \n",info.dli_fname,info.dli_sname);
        }
        printf("Enter:[%s,%s] \n",info.dli_fname,info.dli_sname);
    }
}
 
void __cyg_profile_func_exit(void *func, void *caller) {
 
    for(int i = 0 ; i < nDepth ; i++)
    {
        if(fp_trace)
        {
            fprintf(fp_trace,"\t");
        }
        printf("\t");
    }
    nDepth --;
 
    Dl_info info;
    if (dladdr(func, &info) != 0) 
    {        
        if(fp_trace)
        {
            fprintf(fp_trace,"Enter:[%s,%s] \n",info.dli_fname,info.dli_sname);
        }
        printf("Leave:[%s,%s] \n",info.dli_fname,info.dli_sname);
    }
}
