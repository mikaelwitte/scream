I'm going to put my thoughts about what is needed to put a new process in here.

Every process requires the following files:

atmosphere_XXX.cpp
atmosphere_XXX.hpp
scream_YYY_interface.F90
scream_YYY_interface.hpp

Where XXX is the generic process name (i.e. microphysics) and YYY is the specific process name (i.e. P3)

File Descriptions:
-----------------

atmosphere_XXX.cpp:
   Creates the atmospheric object from the atmospheric process class.
   Defines the initialization steps for the process.
   Defines the registration of fields to the field manager (FM) for the process.
   Defines the run sequence for the process.
   Defines the finalization steps for the process.

atmosphere_XXX.hpp:
   Defines the AtmosphericProcess object specific to this process.
   
scream_YYY_interface.F90:
   Contains all of the fortran code that will be called by the init, run and finalize steps in
     the atmospheric process object.  These must be bounded by C.

scream_YYY_interface.hpp:
   C wrappers for the fortran code in the SCREAM_YYY_interface.F90 file.


