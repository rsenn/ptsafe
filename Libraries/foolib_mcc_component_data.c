/*
 * MATLAB Compiler: 4.13 (R2010a)
 * Date: Mon Sep  5 15:54:07 2011
 * Arguments: "-B" "macro_default" "-W" "lib:foolib" "-T" "link:lib" "-d"
 * "/Users/cuz/Desktop/OygoSVN/Projects/ptsafe/Libraries" "-C" "-w"
 * "enable:specified_file_mismatch" "-w" "enable:repeated_file" "-w"
 * "enable:switch_ignored" "-w" "enable:missing_lib_sentinel" "-w"
 * "enable:demo_license" "-v"
 * "/Users/cuz/Desktop/OygoSVN/Projects/ptsafe/Libraries/foo.m" 
 */

#include "mclmcrrt.h"

#ifdef __cplusplus
extern "C" {
#endif
const unsigned char __MCC_foolib_session_key[] = {
    '0', 'E', '8', '9', '4', '5', '8', '3', 'B', '9', 'E', 'B', 'E', '9', '7',
    '3', '0', 'C', 'F', 'A', 'B', '9', 'E', '1', '7', '6', 'D', '1', '0', '5',
    '5', '0', 'D', '9', 'A', '1', '3', 'C', 'D', 'B', 'A', 'D', '5', 'B', '2',
    '6', 'E', '4', '9', 'D', 'A', '9', '3', '4', '8', '9', '5', 'F', 'B', '0',
    'F', '1', 'A', '0', '4', '4', '2', '0', '0', '2', 'C', 'D', 'D', '8', 'F',
    'E', '2', 'E', 'F', '7', '1', '0', 'B', 'B', '3', '4', '1', '9', '1', '7',
    'E', '9', 'A', 'D', '7', 'A', 'C', '3', 'D', '9', 'D', '5', 'C', '2', '4',
    'C', '7', 'C', '0', '6', '1', '3', 'B', '2', '1', '6', '2', '8', '2', 'E',
    '6', '5', '9', '5', 'F', '7', 'D', '8', 'D', 'D', '3', '2', '0', '9', '8',
    'A', '0', 'D', 'D', '1', '7', 'D', '8', '1', '7', 'F', 'E', 'E', '6', '4',
    '8', '7', 'B', '6', '6', '9', '7', '6', 'D', '3', '3', 'B', 'E', '3', 'B',
    '6', '6', '4', 'D', '1', '1', 'B', '3', 'F', '7', '0', 'F', '0', '4', 'E',
    '5', 'C', 'A', '9', 'F', '5', 'A', 'E', '3', '8', 'F', '5', '1', '0', '4',
    '0', '8', '5', '3', 'D', 'A', 'B', '0', '7', 'A', '9', '0', '0', '1', '8',
    '4', '6', 'A', '1', '9', 'F', '5', 'E', 'B', '4', '9', 'D', '2', '7', '0',
    'C', '1', 'F', 'F', '8', '4', 'D', 'F', 'D', '5', 'D', '7', 'C', '8', 'A',
    '7', '8', '1', 'F', '8', 'A', '3', '1', '9', 'B', '3', '7', 'E', 'D', 'E',
    '9', '\0'};

const unsigned char __MCC_foolib_public_key[] = {
    '3', '0', '8', '1', '9', 'D', '3', '0', '0', 'D', '0', '6', '0', '9', '2',
    'A', '8', '6', '4', '8', '8', '6', 'F', '7', '0', 'D', '0', '1', '0', '1',
    '0', '1', '0', '5', '0', '0', '0', '3', '8', '1', '8', 'B', '0', '0', '3',
    '0', '8', '1', '8', '7', '0', '2', '8', '1', '8', '1', '0', '0', 'C', '4',
    '9', 'C', 'A', 'C', '3', '4', 'E', 'D', '1', '3', 'A', '5', '2', '0', '6',
    '5', '8', 'F', '6', 'F', '8', 'E', '0', '1', '3', '8', 'C', '4', '3', '1',
    '5', 'B', '4', '3', '1', '5', '2', '7', '7', 'E', 'D', '3', 'F', '7', 'D',
    'A', 'E', '5', '3', '0', '9', '9', 'D', 'B', '0', '8', 'E', 'E', '5', '8',
    '9', 'F', '8', '0', '4', 'D', '4', 'B', '9', '8', '1', '3', '2', '6', 'A',
    '5', '2', 'C', 'C', 'E', '4', '3', '8', '2', 'E', '9', 'F', '2', 'B', '4',
    'D', '0', '8', '5', 'E', 'B', '9', '5', '0', 'C', '7', 'A', 'B', '1', '2',
    'E', 'D', 'E', '2', 'D', '4', '1', '2', '9', '7', '8', '2', '0', 'E', '6',
    '3', '7', '7', 'A', '5', 'F', 'E', 'B', '5', '6', '8', '9', 'D', '4', 'E',
    '6', '0', '3', '2', 'F', '6', '0', 'C', '4', '3', '0', '7', '4', 'A', '0',
    '4', 'C', '2', '6', 'A', 'B', '7', '2', 'F', '5', '4', 'B', '5', '1', 'B',
    'B', '4', '6', '0', '5', '7', '8', '7', '8', '5', 'B', '1', '9', '9', '0',
    '1', '4', '3', '1', '4', 'A', '6', '5', 'F', '0', '9', '0', 'B', '6', '1',
    'F', 'C', '2', '0', '1', '6', '9', '4', '5', '3', 'B', '5', '8', 'F', 'C',
    '8', 'B', 'A', '4', '3', 'E', '6', '7', '7', '6', 'E', 'B', '7', 'E', 'C',
    'D', '3', '1', '7', '8', 'B', '5', '6', 'A', 'B', '0', 'F', 'A', '0', '6',
    'D', 'D', '6', '4', '9', '6', '7', 'C', 'B', '1', '4', '9', 'E', '5', '0',
    '2', '0', '1', '1', '1', '\0'};

static const char * MCC_foolib_matlabpath_data[] = 
  { "foolib/", "$TOOLBOXDEPLOYDIR/", "$TOOLBOXMATLABDIR/general/",
    "$TOOLBOXMATLABDIR/ops/", "$TOOLBOXMATLABDIR/lang/",
    "$TOOLBOXMATLABDIR/elmat/", "$TOOLBOXMATLABDIR/randfun/",
    "$TOOLBOXMATLABDIR/elfun/", "$TOOLBOXMATLABDIR/specfun/",
    "$TOOLBOXMATLABDIR/matfun/", "$TOOLBOXMATLABDIR/datafun/",
    "$TOOLBOXMATLABDIR/polyfun/", "$TOOLBOXMATLABDIR/funfun/",
    "$TOOLBOXMATLABDIR/sparfun/", "$TOOLBOXMATLABDIR/scribe/",
    "$TOOLBOXMATLABDIR/graph2d/", "$TOOLBOXMATLABDIR/graph3d/",
    "$TOOLBOXMATLABDIR/specgraph/", "$TOOLBOXMATLABDIR/graphics/",
    "$TOOLBOXMATLABDIR/uitools/", "$TOOLBOXMATLABDIR/strfun/",
    "$TOOLBOXMATLABDIR/imagesci/", "$TOOLBOXMATLABDIR/iofun/",
    "$TOOLBOXMATLABDIR/audiovideo/", "$TOOLBOXMATLABDIR/timefun/",
    "$TOOLBOXMATLABDIR/datatypes/", "$TOOLBOXMATLABDIR/verctrl/",
    "$TOOLBOXMATLABDIR/codetools/", "$TOOLBOXMATLABDIR/helptools/",
    "$TOOLBOXMATLABDIR/demos/", "$TOOLBOXMATLABDIR/timeseries/",
    "$TOOLBOXMATLABDIR/hds/", "$TOOLBOXMATLABDIR/guide/",
    "$TOOLBOXMATLABDIR/plottools/", "toolbox/local/",
    "$TOOLBOXMATLABDIR/datamanager/", "toolbox/compiler/" };

static const char * MCC_foolib_classpath_data[] = 
  { "" };

static const char * MCC_foolib_libpath_data[] = 
  { "" };

static const char * MCC_foolib_app_opts_data[] = 
  { "" };

static const char * MCC_foolib_run_opts_data[] = 
  { "" };

static const char * MCC_foolib_warning_state_data[] = 
  { "off:MATLAB:dispatcher:nameConflict" };


mclComponentData __MCC_foolib_component_data = { 

  /* Public key data */
  __MCC_foolib_public_key,

  /* Component name */
  "foolib",

  /* Component Root */
  "",

  /* Application key data */
  __MCC_foolib_session_key,

  /* Component's MATLAB Path */
  MCC_foolib_matlabpath_data,

  /* Number of directories in the MATLAB Path */
  37,

  /* Component's Java class path */
  MCC_foolib_classpath_data,
  /* Number of directories in the Java class path */
  0,

  /* Component's load library path (for extra shared libraries) */
  MCC_foolib_libpath_data,
  /* Number of directories in the load library path */
  0,

  /* MCR instance-specific runtime options */
  MCC_foolib_app_opts_data,
  /* Number of MCR instance-specific runtime options */
  0,

  /* MCR global runtime options */
  MCC_foolib_run_opts_data,
  /* Number of MCR global runtime options */
  0,
  
  /* Component preferences directory */
  "foolib_6CE76F2AA0155FC3B45C3727D2BEFE16",

  /* MCR warning status data */
  MCC_foolib_warning_state_data,
  /* Number of MCR warning status modifiers */
  1,

  /* Path to component - evaluated at runtime */
  NULL

};

#ifdef __cplusplus
}
#endif


