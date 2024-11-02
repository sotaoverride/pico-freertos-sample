#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
size_t cobs_encode(const uint8_t * restrict input, size_t length, uint8_t * restrict output)
{
    size_t read_index = 0;
    size_t write_index = 1;
    size_t code_index = 0;
    uint8_t code = 1;

    while(read_index < length)
    {
        if(input[read_index] == 0)
        {
            output[code_index] = code;
            code = 1;
            code_index = write_index++;
            read_index++;
        }
        else
        {
            output[write_index++] = input[read_index++];
            code++;
            if(code == 0xFF)
            {
                output[code_index] = code;
                code = 1;
                code_index = write_index++;
            }
        }
    }

    output[code_index] = code;

    return write_index;
}
int main(){
	uint8_t input[4]={0x00, 0x01, 0x00, 0x0f};
	uint8_t output[6]={0xff,0xff,0xff,0xff,0xff,0xff};
	cobs_encode(input, 4, output);
	for(uint8_t i=0;i<6;i++) printf("%d\n", output[i]);


	return 1;
}

