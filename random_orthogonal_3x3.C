#include <stdlib.h>

/* \brief fill the matrix U with a random column vectors such that it is orthogonal
 * \param U [out] an orthoogonal matrix
 */


/*functions returning the maximal value of a vector*/
/** \brief Get the value of the maximal component of a vector
 *
 * Returns the maximal component (including sign) of the vector 
 * \param c vector dimension
 * \param *v adress of the vector
 * \return the maximal vector component
 * \sa vmaxi
 * \return maximum component value
*/
double vmaxd(int c, double *v){
  register int jj;
  register double vmax=DBL_MIN;
  for (jj=0;jj<c;jj++) vmax=(v[jj]>vmax)?v[jj]:vmax;
  return(vmax);
}

/** \brief Get the mean value of the components of a vector
 *
 * \param c vector dimension
 * \param *v adress of the vector
 * \return mean of vector components
 */
double vmeand(int c, double *v) {
  register int jj;
  register double vmean=0;
  for (jj=0;jj<c;jj++) vmean+=v[jj];
  return(vmean/(double)c);
}

/**\brief Get the value of the maximal component of an integer valued vector
 *
 * \param c vector dimension
 * \param *v adress of the vector
 * \return the maximal vector component
 * \sa vmaxd
 * \return maximum component value
*/
int vmaxi(int c, const int *v){
  register int jj;
  register int vmax=INT_MIN;
  for (jj=0;jj<c;jj++) vmax=(v[jj]>vmax)?v[jj]:vmax;
  return(vmax);
}

/** \brief Sum of components of an integer valued vector
 *
 * \param c vector dimension
 * \param *v pointer to the vector
 * \return sum of the components
 */
int vsumi(int c, const int *v){
  register int jj;
  register int sumi=0;
  for (jj=0;jj<c;jj++) sumi+=v[jj];
  return(sumi);
}
 
/** \brief Sum of components of a double valued vector
 *
 * \param c vector dimension
 * \param *v pointer to the vector
 * \return sum of the components
 */
double vsumd(int c, const double *v){
  register int jj;
  register double sumd=0;
  for (jj=0;jj<c;jj++) sumd+=v[jj];
  return(sumd);
}

/** \brief Multiply a vector by a 3x3 matrix 
 *
 * Matrices are stored in memory as 9 consecutive elements in row order.
 * \param *M pointer to the 3x3 matrix. (stored in memory as 9 consectuive values)
 * \param *v pointer the input vector
 * \param *vr pointer to the resulting vector. (assumed to be allocated elsewhere)
 * \return pointer to the resulting vector to allow nesting
 */
double *matvectmul3(double *M, double *v, double *vr){
  *vr= M[0]*v[0] + M[1]* v[1] + M[2]* v[2];
  *(vr+1)=M[3]*v[0] + M[4]* v[1] + M[5]* v[2];
  *(vr+2)=M[6]*v[0] + M[7]* v[1] + M[8]* v[2];
  return vr;
}


/** \brief Multiply an integer valued vector by a 3x3 matrix 
 *
 * Matrices are stored in memory as 9 consecutive elements in row order.
 * \param *v pointer the input vector
 * \param *vr pointer to the resulting vector. (assumed to be allocated elsewhere)
 * \return pointer to the resulting vector to allow nesting
 */
double *matvectmul3di(double *M, int *v, double *vr) {
  *vr= M[0]*v[0] + M[1]* v[1] + M[2]* v[2];
  *(vr+1)=M[3]*v[0] + M[4]* v[1] + M[5]* v[2];
  *(vr+2)=M[6]*v[0] + M[7]* v[1] + M[8]* v[2];
  return vr;
}

/** \brief Multiply two 3x3 matrices 
 *
 * Matrices are stored in memory as 9 consecutive elements in row order.
 * 
 * \param *M1 pointer to the 1st 3x3 matrix. 
 * \param *M2 pointer to the 2nd 3x3 matrix. 
 * \param *Mo pointer to the resulting 3x3 matrix. 
 */
double *matmatmul3(double *M1, double *M2, double *Mo){
  Mo[0]=M1[0]*M2[0] + M1[1]*M2[3] + M1[2]*M2[6];
  Mo[1]=M1[0]*M2[1] + M1[1]*M2[4] + M1[2]*M2[7];
  Mo[2]=M1[0]*M2[2] + M1[1]*M2[5] + M1[2]*M2[8];

  Mo[3]=M1[3]*M2[0] + M1[4]*M2[3] + M1[5]*M2[6];
  Mo[4]=M1[3]*M2[1] + M1[4]*M2[4] + M1[5]*M2[7];
  Mo[5]=M1[3]*M2[2] + M1[4]*M2[5] + M1[5]*M2[8];

  Mo[6]=M1[6]*M2[0] + M1[7]*M2[3] + M1[8]*M2[6];
  Mo[7]=M1[6]*M2[1] + M1[7]*M2[4] + M1[8]*M2[7];
  Mo[8]=M1[6]*M2[2] + M1[7]*M2[5] + M1[8]*M2[8];
  return Mo;
}
/**\brief add two 3-element vectors and store the result in the 2nd
 * \param x 1st vector term
 * \param y 2nd vector term 
 * \return pointer to the 2nd vector
 */
double *vectadd3d(double *x, double *y){
 y[0]=x[0]+y[0];
 y[1]=x[0]+y[0];
 y[2]=x[0]+y[0];
 return y;
}

/**\brief Calculate 2-norm of a vector in \f$\mathbf{R}^3\f$
 * \param v pointer to the vector
 * \return euklidean norm of the vector
 */
double norm2(double *v){
  double n,v0,v1,v2;
  v0=v[0];v1=v[1];v2=v[2];
  n=(v0*v0+ v1*v1+ v2*v2 );
  n=sqrt(n);
  return n;
}

/**\brief Calculate the vector crossproduct of tho vectors in \f$\mathbf{R}^3\f$
 * \param v pointer to the 1st vector
 * \param u[inout] pointer to the 2nd vector - On exit contains the crossproduct of the two
 * \return pointer to the second vector which contains \f$\vec{v} \times \vec{u}\f$*/
double *crossproduct(double *v, double *u){
  double r0=v[1]*u[2]-v[2]*u[1];
  double r1=u[0]*v[2]-u[2]*v[0];
  double r2=v[0]*u[1]-v[1]*u[0];
  u[0]=r0;
  u[1]=r1;
  u[2]=r2;
  return u;
}

/**\brief Calculate the vector scalar (inner) product of two vectors in \f$\mathbf{R}^3\f$
 * \param v pointer to the 1st vector
 * \param u pointer to the 2nd vector
 * \return \f$\vec{v} \cdot \vec{u}\f$
 */
double scalarproduct(double *v, double *u){
  double g;
  g=v[0]*u[0]+v[1]*u[1]+v[2]*u[2];
  return(g);
}


void random_orthogonal_3x3(){

    FILE *ofp = fopen("output.orts","wb");

    const int N=250;


    double v[3],u[3];
    double vnorm,unorm;
    double U[9];

    TRandom3 *tr = new TRandom3();

    for (int ii=0;ii<N; ii++){
        /*generate a first normalised vector*/
        v[0]= (double) tr->Rndm();
        v[1]= (double) tr->Rndm();
        v[2]= (double) tr->Rndm();
        vnorm=norm2(v);
        v[0]= v[0]/vnorm;v[1]=v[1]/vnorm;v[2]=v[2]/vnorm;
        U[0]=v[0];U[3]=v[1];U[6]=v[2];
        /*generate a first normalised vector*/
        u[0]= (double) tr->Rndm();
        u[1]= (double) tr->Rndm();
        u[2]= (double) tr->Rndm();
        unorm=norm2(u);
        u[0]= u[0]/unorm;u[1]=u[1]/unorm;u[2]=u[2]/unorm;
        /*generate the third as the crossproduct of the two first ones*/
        crossproduct(v,u);
        unorm=norm2(u);
        u[0]= u[0]/unorm;u[1]=u[1]/unorm;u[2]=u[2]/unorm;
        U[2]=u[0];U[5]=u[1];U[8]=u[2];
        /*now do the second one as the crossproduct of the 3rd and the first*/
        crossproduct(u,v);
        vnorm=norm2(v);
        v[0]= v[0]/vnorm;v[1]=v[1]/vnorm;v[2]=v[2]/vnorm;
        U[1]=v[0];U[4]=v[1];U[7]=v[2];
        /*U now contains an orthonormal matrix (stored in row order)*/
        for (int jj=0;jj<9;jj++){
            fprintf(ofp," %.8g",U[jj]);
        }
        fprintf(ofp,"\n");
    }
    fclose(ofp);
}
