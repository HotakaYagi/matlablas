#include "mex.h"
#include "blas.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
#if MX_HAS_INTERLEAVED_COMPLEX
    mxDouble *A, *B, *C; /* pointers to input & output matrices*/
#else
    double *A, *B, *C; /* pointers to input & output matrices*/
#endif
    ptrdiff_t m,n,p;      /* matrix dimensions */
    char *chn = "N";
    double one = 1.0, zero = 0.0;
    
#if MX_HAS_INTERLEAVED_COMPLEX
    A = mxGetDoubles(prhs[0]); /* first input matrix */
    B = mxGetDoubles(prhs[1]); /* second input matrix */
#else
    A = mxGetPr(prhs[0]); /* first input matrix */
    B = mxGetPr(prhs[1]); /* second input matrix */
#endif
    /* dimensions of input matrices */
    m = mxGetM(prhs[0]);  
    p = mxGetN(prhs[0]);
    n = mxGetN(prhs[1]);

    /* check to make sure the first input argument is a real matrix */
    if( !mxIsDouble(prhs[0]) || mxIsComplex(prhs[0])) {
      mexErrMsgIdAndTxt( "MATLAB:matrixMultiply:fieldNotRealMatrix",
              "First input argument must be a real matrix.");
    }

    /* check to make sure the second input argument is a real matrix */
    if( !mxIsDouble(prhs[1]) || mxIsComplex(prhs[1])) {
      mexErrMsgIdAndTxt( "MATLAB:matrixMultiply:fieldNotRealMatrix",
              "Second input argument must be a real matrix.");
    }

    /* create output matrix C */
    plhs[0] = mxCreateDoubleMatrix(m, n, mxREAL);
#if MX_HAS_INTERLEAVED_COMPLEX
    C = mxGetDoubles(plhs[0]);
#else
    C = mxGetPr(plhs[0]);
#endif

    /* Pass arguments to Fortran by reference */
    dgemv(chn, &m, &p, &one, A, &m, B, &n, &zero, C, &n);
}
