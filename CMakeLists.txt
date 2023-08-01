# CMakeList.txt : CMake project for dot-matrix, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("dot-matrix")


# Add source to this project's executable.
add_executable (dot-matrix "src/main.cpp" "src/gb.cpp" "src/gb.h" "src/cart.cpp" "src/cart.h" "src/consts.h" "src/cpu.h" "src/cpu.cpp" "src/mmu.h" "src/mmu.cpp" "src/ppu.h" "src/ppu.cpp" )

find_package(fmt CONFIG REQUIRED)
target_link_libraries(dot-matrix PRIVATE fmt::fmt)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(dot-matrix
	PRIVATE
	$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
	$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET dot-matrix PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
