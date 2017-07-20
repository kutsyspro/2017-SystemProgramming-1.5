#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
	FILE    *fp_sour;    // 파일 원본을 위한 파일 스트림 포인터
	FILE    *fp_dest;    // 복사 대상을 위한 파일 스트림 포인터
	char     buff[1024]; // 파일 내요을 읽기/쓰기를 위한 버퍼
	size_t   n_size;     // 읽거나 쓰기를 위한 데이터의 개수

	if(argc==1)
	{                                       
		fp_sour  = fopen( "HighCopy.c"  , "r");
		fp_dest  = fopen( "HighCopy1.c", "w");

		while( 0 < (n_size = fread( buff, 1, 1024, fp_sour)))
		{
			fwrite( buff, 1, n_size, fp_dest);
		}                            

		fclose( fp_sour);
		fclose( fp_dest);
		return 0;
	}
	else if(argc==2)
	{
		fp_sour  = fopen( argv[1]  , "r");
		fp_dest  = fopen( "HighCopy1.c", "w");

		while( 0 < (n_size = fread( buff, 1, 1024, fp_sour)))
		{
			fwrite( buff, 1, n_size, fp_dest);
		} 

		fclose( fp_sour);
		fclose( fp_dest);
		return 0;

	}
	else if(argc==3)
	{
		fp_sour  = fopen( argv[1]  , "r");
		fp_dest  = fopen( argv[2], "w");

		while( 0 < (n_size = fread( buff, 1, 1024, fp_sour)))
		{
			fwrite( buff, 1, n_size, fp_dest);
		} 

		fclose( fp_sour);
		fclose( fp_dest);
		return 0;

	}
}
