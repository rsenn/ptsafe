/*
 * MATLAB Compiler: 4.11 (R2009b)
 * Date: Wed Jul 27 16:21:26 2011
 * Arguments: "-B" "macro_default" "-B" "csharedlib:foolib" "-W" "lib:foolib"
 * "-T" "link:lib" "foo.m" "-C" 
 */

#include <stdio.h>
#define EXPORTING_foolib 1
#include "foolib.h"
#ifdef __cplusplus
extern "C" {
#endif

extern mclComponentData __MCC_foolib_component_data;

#ifdef __cplusplus
}
#endif


static HMCRINSTANCE _mcr_inst = NULL;


#if defined( _MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__) || defined(__LCC__)
#ifdef __LCC__
#undef EXTERN_C
#endif
#include <windows.h>

static char path_to_dll[_MAX_PATH];

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, void *pv)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        if (GetModuleFileName(hInstance, path_to_dll, _MAX_PATH) == 0)
            return FALSE;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
    }
    return TRUE;
}
#endif
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
  if (_mcr_inst != NULL)
    return true;
  if (!mclmcrInitialize())
    return false;
  if (!GetModuleFileName(GetModuleHandle("foolib"), path_to_dll, _MAX_PATH))
    return false;
  if (!mclInitializeComponentInstance(&_mcr_inst, &__MCC_foolib_component_data, true, 
                                      NoObjectType, LibTarget, error_handler, 
                                      print_handler))
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
  int stackDepth = mclGetStackTrace(_mcr_inst, &stackTrace);
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
