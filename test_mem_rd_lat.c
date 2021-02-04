



char *init_mem(size_t size, size_t stride)
{
	char *mem = malloc(size + 2*4096);
	for (size_t i = stride; i < size; i += stride) {
		*(char **)&mem[i - stride] = (char*)&mem[i];
	}
	*(char **)&mem[i - stride] = (char*)&mem[0];
	return mem;
}

#define	ONE	p = (char **)*p;
#define	FIVE	ONE ONE ONE ONE ONE
#define	TEN	FIVE FIVE
#define	FIFTY	TEN TEN TEN TEN TEN
#define	HUNDRED	FIFTY FIFTY


void
benchmark_loads(iter_t iterations, void *cookie)
{
	struct mem_state* state = (struct mem_state*)cookie;
	register char **p = (char**)state->p[0];
	register size_t i;
	register size_t count = state->len / (state->line * 100) + 1;

	while (iterations-- > 0) {
		for (i = 0; i < count; ++i) {
			HUNDRED;
		}
	}

	use_pointer((void *)p);
	state->p[0] = (char*)p;
}
