INCLUDE (ScreamUtils)

# Required libraries
SET (rrtmgpLib rrtmgp)
SET (NEED_LIBS ${rrtmgpLib} scream_control scream_share)

# Copy yaml input file to run directory
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/input.yaml COPYONLY)

# Test atmosphere processes
CreateUnitTest(rrtmgp_stand_alone "rrtmgp_stand_alone.cpp" "${NEED_LIBS}" LABELS "rrtmgp;physics")

# Copy RRTMGP absorption coefficient lookup tables to local data directory
FILE (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)
CONFIGURE_FILE(${SCREAM_BASE_DIR}/../eam/src/physics/rrtmgp/external/rrtmgp/data/rrtmgp-data-sw-g224-2018-12-04.nc
               ${CMAKE_CURRENT_BINARY_DIR}/data COPYONLY)
CONFIGURE_FILE(${SCREAM_BASE_DIR}/../eam/src/physics/rrtmgp/external/rrtmgp/data/rrtmgp-data-lw-g256-2018-12-04.nc
               ${CMAKE_CURRENT_BINARY_DIR}/data COPYONLY)
