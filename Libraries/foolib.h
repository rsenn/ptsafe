/*
 * MATLAB Compiler: 4.11 (R2009b)
 * Date: Wed Jul 27 16:21:26 2011
 * Arguments: "-B" "macro_default" "-B" "csharedlib:foolib" "-W" "lib:foolib"
 * "-T" "link:lib" "foo.m" "-C" 
 */

#ifndef __foolib_h
#define __foolib_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_foolib
#define PUBLIC_foolib_C_API __global
#else
#define PUBLIC_foolib_C_API /* No import statement needed. */
#endif

#define LIB_foolib_C_API PUBLIC_foolib_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_foolib
#define PUBLIC_foolib_C_API __declspec(dllexport)
#else
#define PUBLIC_foolib_C_API __declspec(dllimport)
#endif

#define LIB_foolib_C_API PUBLIC_foolib_C_API


#else

#define LIB_foolib_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_foolib_C_API 
#define LIB_foolib_C_API /* No special import/export declaration */
#endif

extern LIB_foolib_C_API 
bool MW_CALL_CONV foolibInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_foolib_C_API 
bool MW_CALL_CONV foolibInitialize(void);

extern LIB_foolib_C_API 
void MW_CALL_CONV foolibTerminate(void);



extern LIB_foolib_C_API 
void MW_CALL_CONV foolibPrintStackTrace(void);

extern LIB_foolib_C_API 
bool MW_CALL_CONV mlxFoo(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_foolib_C_API 
long MW_CALL_CONV foolibGetMcrID();



extern LIB_foolib_C_API bool MW_CALL_CONV mlfFoo(int nargout, mxArray** y, mxArray** state_ret, mxArray* x, mxArray* u, mxArray* state, mxArray* id);

#ifdef __cplusplus
}
#endif
#endif
