add_library(uartTransportlayer STATIC
	uarttransportlayer.c
)
target_sources(uartTransportlayer PRIVATE ../product/product.c)

target_include_directories(uartTransportlayer PUBLIC
    .
    "../common/"
    "../msgqueue/"
    "../freertos/FreeRTOS-Kernel/include/"
    "../freertos/"
    "../freertos/FreeRTOS-Kernel/portable/GCC/ARM_CM0/"
    "../utils/"
    "../product/"

)

target_link_libraries(uartTransportlayer LINK_PUBLIC
		      pico_stdlib hardware_uart circbuffer
		      )
