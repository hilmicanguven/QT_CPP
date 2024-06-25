# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\LibraryInventoryTracker_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\LibraryInventoryTracker_autogen.dir\\ParseCache.txt"
  "LibraryInventoryTracker_autogen"
  )
endif()
