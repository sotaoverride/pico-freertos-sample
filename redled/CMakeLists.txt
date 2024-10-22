add_library(redled STATIC
	redled.c
)
target_sources(redled PRIVATE ../common/led_task.c)

target_include_directories(redled PUBLIC
    .
    "../common/"
    "../msgqueue/"
    "../freertos/FreeRTOS-Kernel/include/"
    "../freertos/"
    "../freertos/FreeRTOS-Kernel/portable/GCC/ARM_CM0/"

)

target_link_libraries(redled LINK_PUBLIC
		      pico_stdlib
		      )
