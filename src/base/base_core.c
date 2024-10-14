/* Slice Usage Macros */

#define slice_of(_ptr) {                  \
    .ptr = _ptr,                          \
    .len = sizeof(_ptr) / sizeof(_ptr[0]) \
}

#define slice_from(_ptr, idx) {                    \
    .ptr = _ptr + idx,                             \
    .len = sizeof(_ptr) / ( idx + sizeof(_ptr[0])) \
}

#define slice_range(_ptr, start, end) { \
    .ptr = _ptr+start,                  \
    .len = end - start                  \
}

#define slice_get(slice, idx) slice.ptr[idx]

#define slice_set(slice, idx, elem) {                       \
    static_assert(idx > 0, "Cant Index Below 0, Dumbass");  \
    assert(idx < list.len, "Out Of Bounds Access");         \
    slice.ptr[idx] = elem;                                  \
}


/* Growable List Usage Macros */

#define list_append(list, elem) {                                                \
    static_assert(sizeof(list.ptr[0]) == sizeof(elem), "Elem must fit in list"); \
    if (list.len < list.cap) {                                                   \
        list.ptr[list.len] = elem;                                               \
        list.len += 1;                                                           \
    } else {                                                                     \
        list.ptr = realloc(list.ptr, sizeof(list.ptr[0]) * (list.cap * 2));      \
        list.cap = list.cap * 2;                                                 \
        list.ptr[list.len] = elem;                                               \
        list.len += 1;                                                           \
    }                                                                            \
}

#define list_get(list, idx) list.ptr[idx]

#define list_set(list, idx, elem) {                        \
    static_assert(idx > 0, "Cant Index Below 0, Dumbass"); \
    assert(idx < list.len, "Out Of Bounds Access");        \
    list.ptr[idx] = elem;                                  \
}

#define list_remove(list, idx) {                           \
    static_assert(idx > 0, "Cant Index Below 0, Dumbass"); \
    assert(idx < list.len, "Out Of Bounds Access");        \
    list.ptr[idx] = list.ptr[list.len - 1];                \
    list.len -= 1;                                         \
}

/* Linked List Functions */

#define SLL_Stack_push(list, item)
