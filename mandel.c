#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)
{
    int maxIter = 255;
    int nx = 3000;
    int ny = 2000;

    double r_start = -2;
    double r_end = 1;
    double i_start = -1;
    double i_end = 1;

    int *mat=(int*)malloc(nx*ny*sizeof(int));
    int numOutside = 0;

    #pragma omp parallel
    {

    int tid = omp_get_thread_num();
    double starttime = omp_get_wtime();

    #pragma omp for reduction(+:numOutside) nowait
    for(int i = 0; i < nx; i++)
    {
        //Can compute r_c here, no need to do it every time in the j loop
        double r_c = r_start + ((double)i/nx) * (r_end-r_start);
        for(int j = 0; j < ny; j++)
        {
            int iter = 0;
            double i_c = i_start + ((double)j/ny) * (i_end - i_start);

            double r_z = r_c;
            double i_z = i_c;

            while(iter < maxIter)
            {
                double r_z_temp = r_z;
                r_z= (r_z*r_z) - (i_z*i_z) + r_c;
                i_z= 2.0 * r_z_temp * i_z + i_c;
                iter++;

                if(r_z*r_z+i_z*i_z > 4.0)
                {
                    numOutside++;
                    break;
                }
            }
            mat[i+j*nx] = iter;

        }//End j loop
    }//End i loop
    
    double endtime = omp_get_wtime();
    printf("Thread: %d Time %f\n", tid, endtime-starttime);

    }//End of parallel region

    double area = (r_end-r_start)*(i_end-i_start)*((double)nx*ny-numOutside)/(nx*ny);
    printf("Area: %f\n", area);
    //printf("Time %f\n", endtime-starttime);
    
}





