/*
 * MATLAB Compiler: 4.15 (R2011a)
 * Date: Tue Sep  6 07:50:25 2011
 * Arguments: "-B" "macro_default" "-W" "lib:foolib" "-T" "link:lib" "-d"
 * "/Users/cuz/Desktop/OygoSVN/Projects/ptsafe/Libraries" "-C" "-w"
 * "enable:specified_file_mismatch" "-w" "enable:repeated_file" "-w"
 * "enable:switch_ignored" "-w" "enable:missing_lib_sentinel" "-w"
 * "enable:demo_license" "-v"
 * "/Users/cuz/Desktop/OygoSVN/Projects/ptsafe/Libraries/foo.m" 
 */

#include <stdio.h>
#define EXPORTING_foolib 1
#include "foolib.h"

static HMCRINSTANCE _mcr_inst = NULL;


#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultPrintHandler(const char *s)
{
  return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultErrorHandler(const char *s)
{
  int written = 0;
  size_t len = 0;
  len = strlen(s);
  written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
  if (len > 0 && s[ len-1 ] != '\n')
    written += mclWrite(2 /* stderr */, "\n", sizeof(char));
  return written;
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_foolib_C_API
#define LIB_foolib_C_API /* No special import/export declaration */
#endif

LIB_foolib_C_API 
bool MW_CALL_CONV foolibInitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler)
{
    int bResult = 0;
  if (_mcr_inst != NULL)
    return true;
  if (!mclmcrInitialize())
    return false;
    bResult = mclInitializeComponentInstanceNonEmbeddedStandalone(  &_mcr_inst,
                                                                    NULL,
                                                                    "foolib",
                                                                    LibTarget,
                                                                    error_handler, 
                                                                    print_handler);
    if (!bResult)
    return false;
  return true;
}

LIB_foolib_C_API 
bool MW_CALL_CONV foolibInitialize(void)
{
  return foolibInitializeWithHandlers(mclDefaultErrorHandler, mclDefaultPrintHandler);
}

LIB_foolib_C_API 
void MW_CALL_CONV foolibTerminate(void)
{
  if (_mcr_inst != NULL)
    mclTerminateInstance(&_mcr_inst);
}

LIB_foolib_C_API 
long MW_CALL_CONV foolibGetMcrID() 
{
  return mclGetID(_mcr_inst);
}

LIB_foolib_C_API 
void MW_CALL_CONV foolibPrintStackTrace(void) 
{
  char** stackTrace;
  int stackDepth = mclGetStackTrace(&stackTrace);
  int i;
  for(i=0; i<stackDepth; i++)
  {
    mclWrite(2 /* stderr */, stackTrace[i], sizeof(char)*strlen(stackTrace[i]));
    mclWrite(2 /* stderr */, "\n", sizeof(char)*strlen("\n"));
  }
  mclFreeStackTrace(&stackTrace, stackDepth);
}


LIB_foolib_C_API 
bool MW_CALL_CONV mlxFoo(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "foo", nlhs, plhs, nrhs, prhs);
}

LIB_foolib_C_API 
bool MW_CALL_CONV mlfFoo(int nargout, mxArray** y, mxArray** state_ret, mxArray* x, 
                         mxArray* u, mxArray* state, mxArray* id)
{
  return mclMlfFeval(_mcr_inst, "foo", nargout, 2, 4, y, state_ret, x, u, state, id);
}
