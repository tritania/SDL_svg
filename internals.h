#ifndef INTERNALS_H
#define INTERNALS_H

#define SVG_VERSION 108

#ifdef VERBOSE
#define dprintf(format, arg...) printf(format, ##arg)
#else
#define dprintf(format, arg...)
#endif

// Point. This is in coordinates appropriate to the SDL_Surface
typedef struct _IPoint {
	float x,y;
} IPoint;

typedef struct svg_matrix {
	float matrix[6];
} svg_matrix_t;


#define MATRIXSTACKDEPTH 16 // must be power of 2

#define MINPATH 256 // when we allocate a path, start with this number of points
#define MINPATHSTOPS 64

#define NUM_GRADIENT_COLORS 256 // must be power of 2
struct SDL_svg_context {
	SDL_Surface *surface;
	int numpoints; // number of ipoints of path that is building up
	int pathmax; // number of ipoints that will fit in the allocated path
	IPoint *path; // path that is building up
	int numpathstops; // number of pathstops at *pathstops
	int maxpathstops; // maximum space at *pathstops
	int *pathstops; // the pathstops, each are which IPoint at path to stop
	IPoint at;
	double FillOpacity;
// svg_paint_t
	void *paint; // Big question who deallocates this
	IPoint gradient_p1; // for radial, the center point
	IPoint gradient_p2; // for radial, the focus point
	float gradient_r;
	int gradient_policy;
	int tmatrixsp;
	svg_matrix_t tmatrixstack[MATRIXSTACKDEPTH];
	unsigned long gradient_colors[NUM_GRADIENT_COLORS];
	unsigned long solidcolor;
// svg_fill_rule_t
	int fill_rule;

	float w,h;
	double OffsetX,OffsetY;
	double ScaleX,ScaleY;
//svg_t *
	void *SVG;
	int TargetOffsetX;
	int TargetOffsetY;


};

IPoint FixCoords(SDL_svg_context *c, IPoint p);
IPoint FixSizes(SDL_svg_context *c, IPoint p);

void svg_matrix_init(svg_matrix_t *dst, float va, float vb, float vc,
			float vd, float ve, float vf);
IPoint svg_apply_matrix(svg_matrix_t *m, IPoint p);
IPoint svg_apply_matrix_without_translation(svg_matrix_t *m, IPoint p);

void svg_matrix_multiply(svg_matrix_t *dest, svg_matrix_t *left, svg_matrix_t *right);

#endif