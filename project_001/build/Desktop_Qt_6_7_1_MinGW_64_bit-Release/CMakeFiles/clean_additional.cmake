# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\project_001_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\project_001_autogen.dir\\ParseCache.txt"
  "project_001_autogen"
  )
endif()
