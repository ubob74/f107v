#include <stdlib.h>
#include <ringbuf.h>

#define RB_SZ 1024

static int tail;
static int head;
static int count;
static unsigned char rb_data[RB_SZ];

static int rb_is_empty(void)
{
	return ((head == tail) && count == 0);
}

static int rb_is_full(void)
{
	return ((head == tail) && count == sizeof(rb_data));
}

void rb_init(void)
{
	tail = 0;
	head = 0;
	count = 0;
	memset(rb_data, 0, sizeof(rb_data));
}

void rb_flush(void)
{
	rb_init();
}

int rb_push(const unsigned char *data, int size)
{
	int i;

	if (!data || !size)
		return 0;

	rb_lock();

	for (i = 0; i < size; i++) {
		if (rb_is_full())
			break;

		rb_data[tail++] = data[i];
		count++;
		if (tail == sizeof(rb_data))
			tail = 0;
	}

	rb_unlock();

	return i;
}

int rb_pull(unsigned char *data, int size)
{
	int i;

	if (!data || !size)
		return 0;

	rb_lock();

	for (i = 0; i < size; i++) {
		if (rb_is_empty())
			break;

		data[i] = rb_data[head];
		rb_data[head] = 0;
		count--;

		head = (head + 1) % sizeof(rb_data);

		/* if (head == sizeof(rb_data))
			head = 0; */
	}

	rb_unlock();

	return i;
}

void rb_dump(void)
{
	int i;
	unsigned char t, h;

	rb_lock();

	for (i = 0; i < sizeof(rb_data); i++) {
		t = (i == tail) ? 't' : ' ';
		printf("%-4c", t);
	}
	printf("\n");

	for (i = 0; i < sizeof(rb_data); i++)
		printf("%-4d", i);
	printf("\n");
	for (i = 0; i < sizeof(rb_data); i++)
		printf("%-4x", rb_data[i]);
	printf("\n");

	/* Show head */
	for (i = 0; i < sizeof(rb_data); i++) {
		h = (i == head) ? 'h' : ' ';
		printf("%-4c", h);
	}
	printf("\n");

	rb_unlock();
}

