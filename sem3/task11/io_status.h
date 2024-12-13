# ifndef IO_STATUS_H
# define IO_STATUS_H

enum class io_status {
        success,
        eof,
        format,
        memory,
        open,
		create, // костыльный статус для task11
};

const char* get_error_message (io_status);

# endif //IO_STATUS_H
