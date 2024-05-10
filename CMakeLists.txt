cmake_minimum_required(VERSION 3.12)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

SET(BINARY_NAME "GoCows")

project(pico_freertos_samples)

SET(LIBRARY_VERSION_MAJOR 0)
SET(LIBRAR_VERSION_STRING 0.1)
# initialize the Pico SDK
pico_sdk_init()

# rest of your project
add_subdirectory(freertos)
add_subdirectory(redled)
add_subdirectory(yellowled)
add_subdirectory(greenled)
add_subdirectory(divcheck)
add_subdirectory(product)
add_subdirectory(msgqueue)

