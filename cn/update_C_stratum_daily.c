/*--------------------------------------------------------------*/
/* 								*/
/*		update_C_stratum_daily				*/
/*								*/
/*								*/
/*	NAME							*/
/*	update_C_stratum_daily -					*/
/*								*/
/*		updates daily C stores to			*/
/*		account for psn and respiration 		*/
/*	SYNOPSIS						*/
/*	double	update_C_stratum_daily(					*/
/*								*/
/*	returns:						*/
/*								*/
/*	OPTIONS							*/
/*								*/
/*	DESCRIPTION						*/
/*								*/
/*								*/
/*	PROGRAMMER NOTES					*/
/*								*/
/*								*/
/*--------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rhessys.h"
#include "phys_constants.h"

int update_C_stratum_daily(struct epconst_struct epc,
						   struct cstate_struct *cs,
                           struct cdayflux_struct *cdf,
                           struct soil_c_object *cs_soil,
                           struct canopy_strata_object *stratum)
{
	/*------------------------------------------------------*/
	/*	Local Function Declarations.						*/
	/*------------------------------------------------------*/
	
	/*------------------------------------------------------*/
	/*	Local Variable Definition. 							*/
	/*------------------------------------------------------*/
	int ok=1;
    if(cdf->psn_to_cpool<0){
        printf("updateC problem (%d,%e,%e,%e, %e,%e)\n",
               stratum[0].ID,
               cdf->psn_to_cpool,
               cdf->total_mr,
               cdf->total_gr,
               cs->availc,
               cs->cpool
               );
    }//debug
        
        
	/* Daily photosynthesis */
	cs->gpsn_src	+= cdf->psn_to_cpool;
	cs->cpool	+= cdf->psn_to_cpool;
	/* Daily maintenance respiration */
	cs->cpool	-= cdf->leaf_day_mr;
	cs->cpool	-= cdf->leaf_night_mr;
	cs->leaf_mr_snk += cdf->leaf_day_mr + cdf->leaf_night_mr;
	cs->cpool	-= cdf->froot_mr;
	cs->froot_mr_snk += cdf->froot_mr;
	if (epc.veg_type == TREE) {
		cs->cpool	-= cdf->livestem_mr;
		cs->cpool	-= cdf->livecroot_mr;
		cs->livestem_mr_snk += cdf->livestem_mr;
		cs->livecroot_mr_snk += cdf->livecroot_mr;
	}
	cs->net_psn = cdf->psn_to_cpool - cdf->total_mr - cdf->total_gr;
//    if(cs->net_psn < -0.02) printf("problem[%d] %e %e, %e[%e+%e+%e+%e+%e], %e[%e+%e+%e+%e+%e+%e+%e+%e+%e+%e+%e+%e], %e[(%e+%e+%e+%e+%e+%e)*%e], %e\n",
//        stratum[0].ID,
//        cs->net_psn,
//        cdf->psn_to_cpool,
//        //--------
//        cdf->total_mr,
//        cdf->leaf_day_mr, cdf->leaf_night_mr,//
//        cdf->livestem_mr,//
//        cdf->livecroot_mr,//
//        cdf->froot_mr,// 6
//        //--------
//        cdf->total_gr, // cost to turn into flesh (error?)
//        cdf->cpool_leaf_gr, cdf->transfer_leaf_gr,
//        cdf->cpool_livestem_gr, cdf->transfer_livestem_gr,
//        cdf->cpool_livecroot_gr, cdf->transfer_livecroot_gr,
//        cdf->cpool_deadcroot_gr, cdf->transfer_deadcroot_gr,
//        cdf->cpool_deadstem_gr, cdf->transfer_deadstem_gr,
//        cdf->cpool_froot_gr, cdf->transfer_froot_gr,//13
//        //--------
//        cdf->cpool_to_gresp_store, // cost to build storage (error?)
//        cdf->cpool_to_leafc_store,
//        cdf->cpool_to_frootc_store,
//        cdf->cpool_to_livestemc_store, cdf->cpool_to_deadstemc_store,
//        cdf->cpool_to_livecrootc_store, cdf->cpool_to_deadcrootc_store,
//        epc.gr_perc,//8
//        //---------
//        cs->availc);
      
    
    

	/* Daily allocation fluxes */
	/* daily leaf allocation fluxes */
	cs->leafc          += cdf->cpool_to_leafc;
	cs->cpool          -= cdf->cpool_to_leafc;
	cs->leafc_store  += cdf->cpool_to_leafc_store;
	cs->cpool          -= cdf->cpool_to_leafc_store;
	/* Daily fine root allocation fluxes */
	cs->frootc         += cdf->cpool_to_frootc;
	cs->cpool          -= cdf->cpool_to_frootc;
	cs->frootc_store += cdf->cpool_to_frootc_store;
	cs->cpool          -= cdf->cpool_to_frootc_store;
	if (epc.veg_type == TREE){
		/* Daily live stem wood allocation fluxes */
		cs->live_stemc          += cdf->cpool_to_livestemc;
		cs->cpool              -= cdf->cpool_to_livestemc;
		cs->livestemc_store  += cdf->cpool_to_livestemc_store;
		cs->cpool              -= cdf->cpool_to_livestemc_store;
		/* Daily dead stem wood allocation fluxes */
		cs->dead_stemc          += cdf->cpool_to_deadstemc;
		cs->cpool              -= cdf->cpool_to_deadstemc;
		cs->deadstemc_store  += cdf->cpool_to_deadstemc_store;
		cs->cpool              -= cdf->cpool_to_deadstemc_store;
		/* Daily live coarse root wood allocation fluxes */
		cs->live_crootc         += cdf->cpool_to_livecrootc;
		cs->cpool              -= cdf->cpool_to_livecrootc;
		cs->livecrootc_store += cdf->cpool_to_livecrootc_store;
		cs->cpool              -= cdf->cpool_to_livecrootc_store;
		/* Daily dead coarse root wood allocation fluxes */
		cs->dead_crootc         += cdf->cpool_to_deadcrootc;
		cs->cpool              -= cdf->cpool_to_deadcrootc;
		cs->deadcrootc_store += cdf->cpool_to_deadcrootc_store;
		cs->cpool              -= cdf->cpool_to_deadcrootc_store;
	}
	/* Daily allocation for transfer growth respiration */
    cs->gresp_store  = 0.0; //+= cdf->cpool_to_gresp_store;//<<----------------------------------------------
	cs->cpool          -= cdf->cpool_to_gresp_store;
	/* Daily growth respiration fluxes */
	/* Leaf growth respiration */
	cs->leaf_gr_snk     += cdf->cpool_leaf_gr;
	cs->cpool           -= cdf->cpool_leaf_gr;
	cs->leaf_gr_snk     += cdf->transfer_leaf_gr;
	cs->gresp_transfer  -= cdf->transfer_leaf_gr;
	/* Fine root growth respiration */
	cs->froot_gr_snk    += cdf->cpool_froot_gr;
	cs->cpool           -= cdf->cpool_froot_gr;
	cs->froot_gr_snk    += cdf->transfer_froot_gr;
	cs->gresp_transfer  -= cdf->transfer_froot_gr;
	if (epc.veg_type == TREE){
		/* Live stem growth respiration */
		cs->livestem_gr_snk  += cdf->cpool_livestem_gr;
		cs->cpool            -= cdf->cpool_livestem_gr;
		cs->livestem_gr_snk  += cdf->transfer_livestem_gr;
		cs->gresp_transfer   -= cdf->transfer_livestem_gr;
		/* Dead stem growth respiration */
		cs->deadstem_gr_snk  += cdf->cpool_deadstem_gr;
		cs->cpool            -= cdf->cpool_deadstem_gr;
		cs->deadstem_gr_snk  += cdf->transfer_deadstem_gr;
		cs->gresp_transfer   -= cdf->transfer_deadstem_gr;
		/* Live coarse root growth respiration */
		cs->livecroot_gr_snk += cdf->cpool_livecroot_gr;
		cs->cpool            -= cdf->cpool_livecroot_gr;
		cs->livecroot_gr_snk += cdf->transfer_livecroot_gr;
		cs->gresp_transfer   -= cdf->transfer_livecroot_gr;
		/* Dead coarse root growth respiration */
		cs->deadcroot_gr_snk += cdf->cpool_deadcroot_gr;
		cs->cpool            -= cdf->cpool_deadcroot_gr;
		cs->deadcroot_gr_snk += cdf->transfer_deadcroot_gr;
		cs->gresp_transfer   -= cdf->transfer_deadcroot_gr;
	}

    
    // catching negative "cs->gresp_transfer" bug:
    if(cs->gresp_transfer<0){
        cs->cpool += cs->gresp_transfer;
        cs->gresp_transfer = 0.0;
    }//debug
    
    
    if(stratum[0].phen.gwseasonday > epc.ndays_expand && cs->cpool>0)
        cs_soil->DOC += cs->cpool*0.05; cs->cpool*=0.95;
    // postive CPOOL --> DOC
    
    
	return (!ok);
}		

