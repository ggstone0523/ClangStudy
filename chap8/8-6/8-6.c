#include <stddef.h>
#include <stdio.h>
#define NALLOC 1024

typedef long Align;

union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

void *malloct(unsigned nbytes);
static Header *morecoret(unsigned);
void freet(void *ap);
void *calloct(unsigned n, unsigned size);

void *malloct(unsigned nbytes) {
	Header *p, *prevp;
	unsigned nunits;

	nunits = (nbytes+sizeof(Header)-1/sizeof(Header)+1);
	if((prevp = freep) == NULL) {
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for(p = prevp->s.ptr; ;prevp = p, p = p->s.ptr) {
		if(p->s.size >= nunits) {
			if(p->s.size == nunits)
				prevp->s.ptr = p->s.ptr;
			else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p+1);
		}
		if(p == freep)
			if((p = morecoret(nunits)) == NULL)
				return NULL;
	}
}

static Header *morecoret(unsigned nu) {
	char *cp, *sbrk(int);
	Header *up;

	if(nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if(cp == (char *)-1)
		return NULL;
	up = (Header *)cp;
	up->s.size = nu;
	freet((void *)(up+1));
	return freep;
}

void freet(void *ap) {
	Header *bp, *p;

	bp = (Header *)ap - 1;
	for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;

	if(bp + bp->s.size == p->s.ptr) {
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;
	if(p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	freep = p;
}

void *calloct(unsigned n, unsigned size) {
	char *p, *temp;;
	int i = 0;
	int nsize = n * size;

	p = (char *)malloct(nsize);
	temp = p;
	while(i < nsize) {
		*(temp+i) = 0;
		i++;
	}
	return (void *)p;
}

int main() {
	char *str;
	str = calloct(6, sizeof(char));
	*str = 'h';
	*(str+1) = 'e';
	*(str+2) = 'l';
	*(str+3) = 'l';
	*(str+4) = 'o';
	*(str+5) = '\0';

	printf("%s\n", str);
	freet(str);
	return 0;
}
