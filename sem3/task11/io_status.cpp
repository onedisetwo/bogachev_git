# include "io_status.h"

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

