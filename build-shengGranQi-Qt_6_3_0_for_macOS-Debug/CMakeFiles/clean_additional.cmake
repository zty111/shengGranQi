# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/shengGranQi_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/shengGranQi_autogen.dir/ParseCache.txt"
  "shengGranQi_autogen"
  )
endif()
