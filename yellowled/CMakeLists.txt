add_library(yellowled STATIC
	yellowled.c
)

target_include_directories(yellowled PUBLIC
    .
    "../freertos/FreeRTOS-Kernel/include/"
    "../freertos/"
    "../freertos/FreeRTOS-Kernel/portable/GCC/ARM_CM0/"

)

target_link_libraries(yellowled LINK_PUBLIC
		      pico_stdlib
		      )
