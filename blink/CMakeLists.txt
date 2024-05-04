add_library(blink STATIC
	blink.c
)

target_include_directories(blink PUBLIC
    .
    "../freertos/FreeRTOS-Kernel/include/"
    "../freertos/"
    "../freertos/FreeRTOS-Kernel/portable/GCC/ARM_CM0/"

)

target_link_libraries(blink LINK_PUBLIC
		      pico_stdlib
		      )
