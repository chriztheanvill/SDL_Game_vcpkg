message(STATUS "\n++++++++++ CONAN v2 ++++++++++")

# ###############################################################
# # Conan v1, VS Code, sin plugin y Clion OK
# # Include Conan-generated file
# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

# # Introduce Conan-generated targets
# conan_basic_setup(NO_OUTPUT_DIRS) # # No organizara

# ###############################################################
# # Conan v2
# ## Config
# # https://docs.conan.io/2/tutorial/consuming_packages/build_simple_cmake_project.html
# #
# # NOTA: Solo la primera vez que se va a ejecutar conan2
# # $ conan profile detect --force
# #
# # Construir con conan2
# # $ conan install . --output-folder=build/Debug --build=missing
# # $ conan install . --output-folder=build/Release --build=missing
# #
# #
# # $ cd build/Debug
# # $ cd build/Release
# #
# # $ cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug ../..
# # $ cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release ../..
# #
# # $ cmake --build . --config Debug
# # $ cmake --build . --config Release
# #
# # $ cd ../.. && rm -rf build
# #
# # $ conan install . --output-folder=build/Debug --build=missing --settings=build_type=Debug && cd build/Debug && cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug ../.. && cmake --build . --config Debug
# #
# #

# # Libs
# https://approvaltestscpp.readthedocs.io/en/latest/generated_docs/ConanIntegration.html

# find_package(catch2)
find_package(Catch2 REQUIRED)
find_package(docopt REQUIRED)

# find_package(fmt)
find_package(fmt REQUIRED)

# include_directories(${fmt_INCLUDE_DIR})
# link_libraries(${fmt_LIBRARIES})
find_package(spdlog REQUIRED)
find_package(glew REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(sol2 REQUIRED)
find_package(range-v3 REQUIRED)

# find_package(glad REQUIRED) ## No Conan2
#
message(STATUS "\n++++++++++ ~CONAN v2 ++++++++++\n")