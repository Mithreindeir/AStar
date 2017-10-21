#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "astar.h"
#define IDXCOORD(x, y, w) ((y)*(w)+(x))

struct map {
	struct node ** nodes;
	int num_nodes;
	int width, height;
};

struct node_stack* get_neighbors(struct map * m, struct node * current)
{
	struct node_stack * n = ns_init();
	
	int x = 0, y = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (current == m->nodes[IDXCOORD(j, i, m->width)]) {
				x = j;
				y = i;
			}
		}
	}
	if ((x-1) >= 0) {
		ns_add(n, m->nodes[IDXCOORD(x-1, y, m->width)]);
	}
	if ((y+1) < m->height) {
		ns_add(n, m->nodes[IDXCOORD(x, y+1, m->width)]);
	}
	if (y-1 >= 0) {
		ns_add(n, m->nodes[IDXCOORD(x, y-1, m->width)]);
	}
	if ((x+1) < m->width) {
		ns_add(n, m->nodes[IDXCOORD(x+1, y, m->width)]);
	}

	for (int i = 0; i < n->num_nodes; i++ ) {
		//printf("node x: %d y: %d \n", n->nodes[i]->x, n->nodes[i]->y);
	}
	return n;
}

int main(int argc, char ** argv)
{
	struct map * m = malloc(sizeof(struct map));
	m->width = 10;
	m->height = 10;
	m->nodes = malloc(sizeof(struct node *) * (m->width * m->height));
	m->num_nodes = m->width * m->height;

	for (int i = 0; i < m->height; i++) {
		for (int j = 0; j < m->width; j++) {
			int w = 0;
			if ((j > 1 && j < 9) && (i == 8)) w = 1;
			if (j == 8 && (i > 1 && i < 8)) w = 1;

			m->nodes[j+(i*m->width)] = node_init(j, i, w);
		}
	}
	//
	a_star(m->nodes[0], m->nodes[99], m, get_neighbors);

	struct node_stack * ns = ns_init();
	struct node * next = m->nodes[99];
	while (1) {
		ns_add(ns, next);
		if (next == m->nodes[0])
			break;
		next = next->parent;
	}
	for (int i = 0; i < m->height; i++) {
		for (int j = 0; j < m->width; j++) {
			struct node * n = m->nodes[IDXCOORD(j, i, m->width)];
			if (!ns_find(ns, n)) {
				if (n->wall) {
					printf("# "); 
				} else {
					printf(". ");
				}
			} else {
				printf("M ");
			}
		}
		printf("\n");
	}
	ns_destroy(ns);
	//
	for (int i = 0; i < m->num_nodes; i++ ) {
		free(m->nodes[i]);
	}
	free(m->nodes);
	free(m);

	return 0;
}

/*

	
*/