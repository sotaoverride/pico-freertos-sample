add_executable(product
	product.c
)

target_include_directories(product PUBLIC
    .
    "../common/"

)
target_link_libraries(product pico_stdlib freertos common greenled yellowled redled msgqueue)
pico_add_extra_outputs(product)
