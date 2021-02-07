# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <iostream>

using namespace std;

# define L 100

int main(int argc, char *argv[]){

    int spin[L][L];
    int i, j, k;
    int ip1, im1, jp1, jm1;
    int mcs;
    int spinValue, spinNeighbourSum;
    int mag;
    int mcsmax;
    int seed;

    double r;
    double K;
    double energyChange;
    double rm;
    double averageMag;
    double TTC;

    /***** Set the parameters *****/
    mcsmax  = 1000;
    TTC     = 1.2;
    K       = 0.2216544 / TTC;
    seed    = 4711;

    srand(seed);

    /***** Initialize the Lattice *****/
    for (i=0; i<L; i++){
        for(j=0; j<L; j++){
            spin[i][j] = -1;
        }
    }

    mag         = - L*L*L;
    averageMag  = 0.0;

    /***** Monte Carlo Loop *****/
    for (mcs=0; mcs<mcsmax; mcs++){

        /***** Loop over all lattice sites *****/
        for(i=0; i<L; i++){
            for(j=0; j<L; j++){

                /***** Periodic boundary conditions *****/
                ip1 = i+1 >= L ?  i+1-L : i+1;
                im1 = i-1 <  0 ?  i-1+L : i-1;
                jp1 = j+1 >= L ?  j+1-L : j+1;
                jm1 = j-1 <  0 ?  j-1+L : j-1;

                /***** Change in energy *****/
                spinValue = spin[i][j];
                spinNeighbourSum =  spin[im1][j] + spin[ip1][j] +
                                    spin[i][jm1] + spin[i][jp1];

                energyChange = 2.0 * K * spinValue * spinNeighbourSum;

                /***** Generate random number ******/
                r = (float)rand() / (float)RAND_MAX;

                /***** Accept/reject the change *****/
                if (energyChange == 0 || r<exp(-(double) energyChange)){
                    spin[i][j]  = -spinValue;
                    mag         -= 2 * spinValue;
                }
            }
        }

        rm = (double) mag / (float) (L*L);
        averageMag += fabs(rm);

    }

    averageMag /= (float) mcsmax;
    printf("%f\n", averageMag);

    return 0;
}