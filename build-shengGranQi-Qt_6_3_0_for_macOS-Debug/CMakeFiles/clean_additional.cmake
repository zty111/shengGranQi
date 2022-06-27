# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/ShengGranQi_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ShengGranQi_autogen.dir/ParseCache.txt"
  "ShengGranQi_autogen"
  )
endif()
