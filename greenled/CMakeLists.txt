add_library(greenled STATIC
	greenled.c
)

target_include_directories(greenled PUBLIC
    .
    "../common/"
    "../msgqueue"
    "../freertos/FreeRTOS-Kernel/include/"
    "../freertos/"
    "../freertos/FreeRTOS-Kernel/portable/GCC/ARM_CM0/"

)

target_link_libraries(greenled LINK_PUBLIC
		      pico_stdlib
		      )
