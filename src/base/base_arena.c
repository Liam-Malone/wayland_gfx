global Arena Arena_init(u64 size) {
    DataBuf* first_buf = malloc(sizeof(DataBuf));
    *first_buf = (DataBuf) {
        .next = nullptr,
        .ptr = nullptr,
        .len = 0,
        .pos = 0,
    };

    if (size > StandardBufSize) {
        first_buf->ptr = (u8*) malloc(size);
        first_buf->len = size;
    } else {
        first_buf->ptr = (u8*) malloc(StandardBufSize);
        first_buf->len = StandardBufSize;
    }

    return (Arena) {
        .first = first_buf,
        .last = first_buf,
        .pos = 0,
        .len = 1,
    };
}

global void* Arena_push(Arena arena , u64 size) {
    DataBuf* current = arena.first;
    u64 cur_pos = 0;
    void* ret_ptr = nullptr;

    /* move pointer to correct buffer */
    while (cur_pos < arena.pos) {
        current = current->next;
        cur_pos++;
    }
    if (current->pos + size > current->len) {
        /* Grow arena */
    } else {
        ret_ptr = (void*) current + current->pos;
        current->pos += size;
    }

    return ret_ptr;
}

