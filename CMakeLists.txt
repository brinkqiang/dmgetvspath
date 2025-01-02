cmake_minimum_required(VERSION 3.21)

PROJECT(dmgetvspath)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

ModuleInclude("dmformat" "thirdparty/dmformat")
ModuleImport("dmflags" "thirdparty/dmflags")
LibImport("execute_module" "src/execute_module")
ExeImport("tools" "execute_module;dmflags")
