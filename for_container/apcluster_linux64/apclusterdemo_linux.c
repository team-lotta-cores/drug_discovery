/*************************************************************************
/* Example of using the affinity propagation clustering modules.
/* See BJ Frey and D Dueck, Science 315, 972-976, Feb 16, 2007, for more details
/*
/* Copyright 2007, BJ Frey / D Dueck. This software may be freely */
/* used and distributed for non-commercial purposes.                      */
/**************************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dlfcn.h>
#include "apcluster.h"

/*callback function; returning non-zero will abort apcluster */
int callback(double *curr_a, double *curr_r, int N, int *curr_idx, int I, double curr_netsim, int iter) {
	if(curr_netsim==-HUGE_VAL) printf("%d\t%s\n", iter, "NaN"); /* cannot calculate netsim */
	else printf("%d\t%f\n", iter, curr_netsim);
	return(0); /* 0=continue apcluster */
}

int main(int argc, char** argv) {
	double sij[]={-15.561,-1.861,-4.066,-9.293,-3.581,-3.093,-27.967,-32.147,-44.921,-47.967,-17.665,-15.628,-6.430,-36.111,-21.062,-32.094,-46.606,-65.053,-64.292,-42.983,-22.071,-11.619,-35.921,-51.256,-19.754,	-1.861,-15.561,-1.839,-8.387,-8.612,-4.909,-15.438,-19.376,-28.647,-31.421,-9.245,-6.721,-1.980,-22.467,-10.440,-22.388,-38.132,-52.074,-49.382,-31.872,-16.521,-6.795,-24.393,-36.228,-10.369,-4.066,-1.839,-15.561,-2.561,-7.097,-2.363,-17.266,-25.109,-31.390,-27.590,-5.415,-8.475,-6.370,-17.876,-10.448,-13.314,-23.992,-36.746,-36.043,-20.618,-7.652,-1.947,-15.996,-27.065,-15.957,-9.293,-8.387,-2.561,-15.561,-6.642,-2.241,-28.773,-41.141,-45.675,-34.572,-8.612,-18.211,-17.008,-22.646,-19.008,-11.184,-15.561,-29.072,-31.518,-16.679,-3.816,-2.318,-15.480,-27.314,-30.247,-3.581,-8.612,-7.097,-6.642,-15.561,-1.458,-44.952,-53.686,-66.515,-62.544,-24.441,-29.052,-18.491,-47.060,-34.200,-34.301,-42.021,-63.480,-66.777,-44.127,-20.513,-13.814,-40.627,-58.475,-37.880,-3.093,-4.909,-2.363,-2.241,-1.458,-15.561,-32.239,-41.536,-50.820,-45.330,-14.087,-19.384,-13.103,-32.147,-22.741,-21.832,-29.598,-47.020,-49.076,-30.043,-11.593,-6.297,-26.753,-41.495,-28.560,-27.967,-15.438,-17.266,-28.773,-44.952,-32.239,-15.561,-2.126,-2.110,-5.972,-7.313,-1.788,-9.199,-5.633,-1.042,-18.227,-38.981,-40.223,-31.372,-24.265,-24.331,-15.561,-14.764,-16.689,-2.962,-32.147,-19.376,-25.109,-41.141,-53.686,-41.536,-2.126,-15.561,-2.609,-13.515,-16.243,-4.613,-9.944,-14.491,-5.458,-32.592,-59.021,-60.772,-49.446,-40.740,-39.186,-26.203,-28.088,-30.241,-1.572,-44.921,-28.647,-31.390,-45.675,-66.515,-50.820,-2.110,-2.609,-15.561,-5.895,-15.692,-7.693,-18.816,-8.843,-5.778,-27.112,-50.933,-47.903,-36.342,-32.455,-37.470,-28.040,-21.515,-20.068,-7.021,-47.967,-31.421,-27.590,-34.572,-62.544,-45.330,-5.972,-13.515,-5.895,-15.561,-8.956,-11.047,-26.444,-1.281,-6.170,-11.085,-25.670,-20.974,-13.189,-12.655,-21.379,-19.102,-6.893,-4.432,-17.315,-17.665,-9.245,-5.415,-8.612,-24.441,-14.087,-7.313,-16.243,-15.692,-8.956,-15.561,-4.386,-10.533,-3.674,-2.907,-3.817,-14.577,-19.552,-16.461,-8.008,-4.993,-1.995,-3.791,-8.877,-12.546,-15.628,-6.721,-8.475,-18.211,-29.052,-19.384,-1.788,-4.613,-7.693,-11.047,-4.386,-15.561,-3.332,-7.760,-0.737,-15.948,-34.891,-40.428,-33.715,-23.112,-17.983,-8.972,-14.360,-19.640,-2.097,-6.430,-1.980,-6.370,-17.008,-18.491,-13.103,-9.199,-9.944,-18.816,-26.444,-10.533,-3.332,-15.561,-20.313,-7.075,-26.722,-47.318,-58.700,-52.987,-36.801,-23.903,-11.639,-26.800,-36.526,-3.661,-36.111,-22.467,-17.876,-22.646,-47.060,-32.147,-5.633,-14.491,-8.843,-1.281,-3.674,-7.760,-20.313,-15.561,-3.767,-5.337,-17.474,-16.075,-10.422,-7.417,-12.333,-10.623,-2.812,-2.958,-15.514,-21.062,-10.440,-10.448,-19.008,-34.200,-22.741,-1.042,-5.458,-5.778,-6.170,-2.907,-0.737,-7.075,-3.767,-15.561,-11.658,-28.921,-32.061,-25.402,-17.291,-15.521,-8.556,-9.602,-13.088,-4.295,-32.094,-22.388,-13.314,-11.184,-34.301,-21.832,-18.227,-32.592,-27.112,-11.085,-3.817,-15.948,-26.722,-5.337,-11.658,-15.561,-3.898,-6.270,-5.573,-0.837,-2.326,-5.129,-0.547,-3.830,-29.393,-46.606,-38.132,-23.992,-15.561,-42.021,-29.598,-38.981,-59.021,-50.933,-25.670,-14.577,-34.891,-47.318,-17.474,-28.921,-3.898,-15.561,-2.802,-5.848,-2.293,-4.558,-12.745,-6.267,-10.108,-54.020,-65.053,-52.074,-36.746,-29.072,-63.480,-47.020,-40.223,-60.772,-47.903,-20.974,-19.552,-40.428,-58.700,-16.075,-32.061,-6.270,-2.802,-15.561,-1.153,-2.547,-11.918,-21.792,-6.608,-6.127,-59.772,-64.292,-49.382,-36.043,-31.518,-66.777,-49.076,-31.372,-49.446,-36.342,-13.189,-16.461,-33.715,-52.987,-10.422,-25.402,-5.573,-5.848,-1.153,-15.561,-2.341,-13.500,-21.388,-4.453,-2.409,-50.490,-42.983,-31.872,-20.618,-16.679,-44.127,-30.043,-24.265,-40.740,-32.455,-12.655,-8.008,-23.112,-36.801,-7.417,-17.291,-0.837,-2.293,-2.547,-2.341,-15.561,-4.618,-9.909,-1.176,-2.902,-38.551,-22.071,-16.521,-7.652,-3.816,-20.513,-11.593,-24.331,-39.186,-37.470,-21.379,-4.993,-17.983,-23.903,-12.333,-15.521,-2.326,-4.558,-11.918,-13.500,-4.618,-15.561,-2.213,-4.956,-12.123,-32.179,-11.619,-6.795,-1.947,-2.318,-13.814,-6.297,-15.561,-26.203,-28.040,-19.102,-1.995,-8.972,-11.639,-10.623,-8.556,-5.129,-12.745,-21.792,-21.388,-9.909,-2.213,-15.561,-7.185,-15.493,-19.053,-35.921,-24.393,-15.996,-15.480,-40.627,-26.753,-14.764,-28.088,-21.515,-6.893,-3.791,-14.360,-26.800,-2.812,-9.602,-0.547,-6.267,-6.608,-4.453,-1.176,-4.956,-7.185,-15.561,-1.669,-26.659,-51.256,-36.228,-27.065,-27.314,-58.475,-41.495,-16.689,-30.241,-20.068,-4.432,-8.877,-19.640,-36.526,-2.958,-13.088,-3.830,-10.108,-6.127,-2.409,-2.902,-12.123,-15.493,-1.669,-15.561,-31.941,-19.754,-10.369,-15.957,-30.247,-37.880,-28.560,-2.962,-1.572,-7.021,-17.315,-12.546,-2.097,-3.661,-15.514,-4.295,-29.393,-54.020,-59.772,-50.490,-38.551,-32.179,-19.053,-26.659,-31.941,-15.561};
	unsigned int i[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24};
	unsigned int j[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
	int m=25, N=625;	/* 25 data points, 625 similarites & preferences */
	int  (*apcluster32)(double*,unsigned int*, unsigned int*, unsigned int, int*, double*, APOPTIONS*); /* function pointer */
	APOPTIONS apoptions={0};
	void *dlh = NULL;
	char *error;
	int iter, k, *idx=0; /* memory for returning clusters of the data points */
	double netsim = 0.0; /* variable for returning the final net similarity */

	if (!(dlh=dlopen("./apclusterunix32.so", RTLD_LAZY))) {printf("%s\n",dlerror()); return(-1);}
	apcluster32 = (int (*)(double*,unsigned int*, unsigned int*, unsigned int, int*, double*, APOPTIONS*))dlsym(dlh, "apcluster32");
	if((error = dlerror())!=NULL) { printf("%s\n",error); return -2;}

	apoptions.cbSize = sizeof(APOPTIONS);
	apoptions.lambda = 0.9;
	apoptions.minimum_iterations = 1;
	apoptions.converge_iterations = 200;
	apoptions.maximum_iterations = 2000;
	apoptions.nonoise = 0;
	apoptions.progress=callback; apoptions.progressf=NULL;
	iter = (*apcluster32)(sij, i, j, N, idx=(int*)calloc(m,sizeof(*idx)), &netsim, &apoptions); /* actual function call */

	if(iter>0) for( k=0; k<m; k++) printf("%d\n", idx[k]+1); /* success: print out the indices */
	else printf("Error code: %d\n", iter); /* failed or canceled by user */

	dlclose(dlh); if(idx) free(idx); /* unload DLL and free memory */
	return 0;
}