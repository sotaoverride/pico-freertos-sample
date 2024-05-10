add_library(common STATIC
	led_task.c
)

target_include_directories(common PUBLIC
    .
    "../msgqueue/"
    "../freertos/FreeRTOS-Kernel/include/"
    "../freertos/"
    "../freertos/FreeRTOS-Kernel/portable/GCC/ARM_CM0/"

)

target_link_libraries(common LINK_PUBLIC
		      pico_stdlib
		      )
