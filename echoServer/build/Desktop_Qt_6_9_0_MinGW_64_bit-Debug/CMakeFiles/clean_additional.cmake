# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\echoServer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\echoServer_autogen.dir\\ParseCache.txt"
  "echoServer_autogen"
  )
endif()
