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

void *malloct(unsigned nbytes) {
	Header *p, *prevp;
	unsigned nunits;

	if(nbytes == 0) {
		printf("malloc block size must be positive\n");
		return NULL;
	}
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
	int isnewmem = 0;
	Header *bp, *p;

	bp = (Header *)ap - 1;
	if(bp->s.size == 0) {
		printf("malloc block size must be positive\n");
		return;
	}
	for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if(p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
			if((p + p->s.size <= bp) || (bp < p->s.ptr))
				isnewmem = 1;
			break;
		}

	if(bp + bp->s.size == p->s.ptr) {
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else if ((isnewmem == 0) && ((bp + bp->s.size) > p->s.ptr)){
		printf("malloc block size not match in free list\n");
		return;
	} else
		bp->s.ptr = p->s.ptr;
	if(p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else {
		p->s.ptr = bp;
		if((isnewmem == 0) && ((p + p->s.size) > bp)) {
			printf("malloc block size not match in free list\n");
			return;
		}
	}
	freep = p;
}

int main() {
	char *str, *origin;
	Header *temp;
	int defaultsize;
	
	str = (char *)malloct(0);
	origin  = (char *)malloct(sizeof(char) * 1000);
	freet(origin);
	str = (char *)malloct(sizeof(char) * 6);

	temp = (Header *)str - 1;
	defaultsize = temp->s.size;
	temp->s.size = 0;
	freet(str);
	temp->s.size = 300;
	freet(str);
	temp->s.size = defaultsize;
	freet(str);

	return 0;
}
