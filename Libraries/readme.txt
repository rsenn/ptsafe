MATLAB Compiler

1. Prerequisites for Deployment 

. Verify the MATLAB Compiler Runtime (MCR) is installed and ensure you    
  have installed version 7.15.   

. If the MCR is not installed, run MCRInstaller, located in:

  <matlabroot>*/toolbox/compiler/deploy/maci64/MCRInstaller.dmg

For more information on the MCR Installer, see the MATLAB Compiler 
documentation.    


NOTE: You will need administrator right to run MCRInstaller. 


2. Files to Deploy and Package

Files to package for Shared Libraries
=====================================
-foolib.ctf (component technology file) 
-foolib.dylib
-foolib.h
-MCRInstaller.dmg 
   - include when building component by clicking "Add MCR" link
     in deploytool
-This readme file

3. Definitions

For a complete list of product terminology, go to 
http://www.mathworks.com/help and select MATLAB Compiler.



* NOTE: <matlabroot> is the directory where MATLAB is installed on the target machine.


4. Appendix 

A. On the target machine, add the MCR directory to the environment variable DYLD_LIBRARY_PATH.

        NOTE: <mcr_root> is the directory where MCR is installed
              on the target machine.         


        . Add the MCR directory to the environment variable by issuing 
          the following commands:

            setenv DYLD_LIBRARY_PATH
                <mcr_root>/v715/runtime/maci64:
                <mcr_root>/v715/sys/os/maci64:
                <mcr_root>/v715/bin/maci64:
                /System/Library/Frameworks/JavaVM.framework/JavaVM:
                /System/Library/Frameworks/JavaVM.framework/Libraries
            setenv XAPPLRESDIR <mcr_root>/v715/X11/app-defaults


        NOTE: To make these changes persistent after logout on Linux 
              or Mac machines, modify the .cshrc file to include this  
              setenv command.
        NOTE: The environment variable syntax utilizes forward 
              slashes (/), delimited by colons (:).  
