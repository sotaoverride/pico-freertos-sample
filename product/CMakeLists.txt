add_executable(product
	product.c
)

target_link_libraries(product pico_stdlib freertos blink msgqueue)
pico_add_extra_outputs(product)
