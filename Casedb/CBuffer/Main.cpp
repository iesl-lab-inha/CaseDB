#include "CLevel.h"

void testWrite(int argc, const char * argv[]){
    std::ofstream f_out;
    clock_t c_start, c_end;
    double duration, speed;
    unsigned long totalSize = 0;

    c_start = clock();
    if(argc == 2){
	CLevel clevel;
	totalSize = clevel.Put(argv[1]);
    }
    c_end = clock();
    duration = (c_end - c_start) / (double) CLOCKS_PER_SEC;
    speed = totalSize / duration / 1048576;
    f_out.open("result.txt", std::ios_base::app);
    f_out << totalSize << ", " << speed << std::endl;
    
}

void testRead(){
    std::ofstream f_out;
    clock_t c_start, c_end;

    c_start = clock();
    CLevel clevel;
    clevel.Get("c_key_15");
    c_end = clock();
   // duration = (c_end - c_start) / (double) CLOCKS_PER_SEC;
    //speed = totalSize / duration / 1048576;
    f_out.open("result_read.txt", std::ios_base::app);
    f_out << (c_end - c_start) << std::endl;
}

int main(int argc, const char * argv[])
{
   // system("rm -rf /home/nemo/Desktop/db/leveldb/testdb");

    //testWrite(argc, argv);
    testRead();
    //std::cout<<"Hello"<<std::endl;
    return 0;
}
