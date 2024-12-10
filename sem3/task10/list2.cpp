#include "list2.h"

io_status list2::read(FILE *fp){
    int count = 0;
    list2_node buf;
    io_status status;
    list2_node *curr, *tail;
    list2 read;

    if (m == 0){
        delete_list();
        return io_status::eof;
    }

    status = buf.read(fp);
    if (status != io_status::success){
        if (feof(fp)){
            delete_list();
            return io_status::eof;
        }
        return status;
    }

    read.head = new list2_node;
    if (!read.head){
        return io_status::memory;
    }

    *(read.head) = (list2_node&&)(buf);
    count = 1;
    curr = read.head;

    for (; count < m && buf.read(fp) == io_status::success; count++){
        tail = new list2_node;
        if (tail == nullptr){
            return io_status::memory;
        }
        *tail = (list2_node&&)buf;
        curr->next = tail;
        tail->prev = curr;
        curr = tail;
    }

    if (count < m && !feof(fp)){
        return io_status::format;
    }

    delete_list();
    *this = (list2&&)(read);
    return io_status::success;
}
