/*
 * lqi.c
 *
 *  Created on: 1 mars 2020
 *      Author: Daniel Mårtensson
 */

#include "../../Headers/Configurations.h"
#include "../../Headers/Functions.h"

static void integral(float* xi, float* r, float* y);

/*
 * This computes the Linear Quadratic Integral inputs
 * Input: Vector y, Vector u, Scalar qi, Vector r, Matrix L, Matrix Li, Vector x, Vecor xi
 */
void lqi(float* y, float* u, float qi, float* r, float* L, float* Li, float* x, float* xi) {

	// First compute the control law: L_vec = L*x
	float L_vec[RDIM*1];
	memset(L_vec, 0, RDIM*sizeof(float));
	mul(L, x, L_vec, RDIM, ADIM, 1);

	// Then compute the integral law: Li_vec = Li*xi
	float Li_vec[RDIM];
	memset(Li_vec, 0, RDIM*sizeof(float));
	integral(xi, r, y);
	mul(Li, xi, Li_vec, RDIM, YDIM, 1);

	// Now combine these two laws: u = Li/(1-qi)*r - (L*x - Li*xi)
	for(int i = 0; i < RDIM; i++){
		*(u + i) = *(Li + i*RDIM)/(1-qi) * *(r + i) - (*(L_vec + i) - *(Li_vec + i));
	}
}

/*
 * This computes the integral by sum state vector xi with reference - measurement
 * xi = xi + r - y;
 */
static void integral(float* xi, float* r, float* y) {
	for(int i = 0; i < RDIM; i++){
		/*
		 * Anti-windup
		 */
		if(ANTI_WINDUP == 0){
			*(xi + i) = *(xi + i) + *(r + i) - *(y + i); // Always integrate
		}else if(ANTI_WINDUP == 1){
			if(*(r + i) > *(y + i)){
				*(xi + i) = *(xi + i) + *(r + i) - *(y + i); // Only integrate when r > y, else delete
			}else{
				*(xi + i) = 0; // Delete just that xi
			}
		}else if(ANTI_WINDUP == 2){
			if(*(r + i) > *(y + i)){
				*(xi + i) = *(xi + i) + *(r + i) - *(y + i); // Only integrate r > y, else stop
			}
		}else{
			*(xi + i) = *(xi + i) + *(r + i) - *(y + i); // Always integrate if nothing else selected
		}
	}
}


