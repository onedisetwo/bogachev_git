#include "student.h"

const char* get_error_message(io_status err){
        switch(err){
                case io_status::open:
                        return "Failed to open file";
                case io_status::format:
                        return "Wrong input format in file";
                case io_status::eof:
			return "Not enough data in file";
                case io_status::memory:
                        return "Failed to allocate memory";
                case io_status::success:
                        return "";
                default:
                        return "Unknown error";
        }
}

io_status read_array (student* student_m, int n, char* filename){
        FILE *fp;
        int i;
        io_status tmp;
        if(!(fp = fopen(filename, "r"))){
                return io_status::open;
        }
        for(i = 0; i < n; i++){
                if((tmp = student_m[i].read(fp)) != io_status::success){
                        fclose(fp);
                        return tmp;
                }
        }
        fclose(fp);
        return io_status::success;
}

// print to the screen
void print_array (student* student_m, int n, int p){
        int i;
        for(i = 0; i < ((n > p) ? p : n); i++)
                (student_m[i]).print();
}

int f (int s, int n, int i){
        switch(s){
                case 1: return i;
                case 2: return n - i;
                case 3: return i/2;
                case 4: return n - i/2;
                default: return 0; // can't happen
        }
}

io_status init_array (student* student_m, int n, int s){
        int i;
	io_status tmp;
        for(i = 1; i <= n; i++){
                if((tmp = student_m[i-1].init("Student", f(s, n, i))) != io_status::success)
			return tmp;
        }
	return io_status::success;
}
