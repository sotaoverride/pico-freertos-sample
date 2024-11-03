add_library(circbuffer STATIC
	circbuffer.c
)

target_include_directories(circbuffer PUBLIC
    .

)

target_link_libraries(circbuffer LINK_PUBLIC
		      pico_stdlib
		      )
