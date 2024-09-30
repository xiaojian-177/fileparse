#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void pbyte(FILE* stream, int num) {
	for(int i = 0; i < num; i++) {
		fputc(0x00, stream) ;  
		
		
	}
}

int main(int argc, char** argv) {
	if (argc != 3 && argc != 4) {
		printf("Usage: %s filein fileout\nfilein format:& is 1MB, $ is 1KB, . is 10Bytes", argv[0]);
		exit(1);
		
	}
	FILE* outfile;
	FILE* infile;
	bool ignore = false;
	
	if(argc == 4 && strcmp(argv[3] ,"--ignore-all") == 0){
		ignore = true;
		printf("Warning:ignore all format string.\n");
		
	}
	
	outfile = fopen(argv[2], "wb");
	infile = fopen(argv[1], "rb");
	unsigned char buff;
	int byte = 0;
	int write = 0;
	
	while (fread(&buff, 1, 1, infile)){
		switch (buff) {
            case 0x2e :
            	if (ignore){
					break;
				}
				for(int i = 0; i < 10; i++) {
					fputc(0x00, outfile) ; 
					write++; 
				}
				break;
			case 0x24 :
				if (ignore){
					break;
				}
				for(int i = 0; i < 1024; i++) {
					fputc(0x00, outfile) ; 
					write++;
					
					 
				}
				break;
			case 0x26 :
				if (ignore){
					break;
				}
				pbyte(outfile, 1048576);
				write += 1048576;
				
				break;
            default : fputc(buff, outfile); write++; break;
            
            
			
			
			
		}
		byte++;
		
	}
	printf("%d bytes readed\n%d bytes writed", byte, write);
	fclose(outfile);
	fclose(infile);
	
}
