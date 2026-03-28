# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Clocks_workwithQPainter_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Clocks_workwithQPainter_autogen.dir\\ParseCache.txt"
  "Clocks_workwithQPainter_autogen"
  )
endif()
