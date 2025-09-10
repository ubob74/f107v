#ifndef _RB_H_
#define _RB_H_

static inline void rb_lock(void) {}
static inline void rb_unlock(void) {}

void rb_init(void);
void rb_flush(void);
int rb_push(const unsigned char *data, int size);
int rb_pull(unsigned char *data, int size);

#endif

