#define StandardBufSize 4096
typedef struct DataBuf DataBuf;
struct DataBuf {
    DataBuf* next;
    u8* ptr;
    u64 len;
    u64 pos;
};

typedef struct Arena Arena;
struct Arena {
    DataBuf* first;
    DataBuf* last;
    u64 pos;
    u64 len;
};

global Arena Arena_init(u64 size);
global void* Arena_push(Arena arena , u64 size);

#define Arena_create(arena, type) (type*) Arena_push(arena, sizeof(type))
#define push_arena(arena, type, count) (type*) Arena_push(arena, sizeof(type) * count)
