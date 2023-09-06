/*--------------------------------------------------------------*/
/* 																*/
/*					output_canopy_stratum						*/
/*																*/
/*	output_canopy_stratum - creates output files objects.		*/
/*																*/
/*	NAME														*/
/*	output_canopy_stratum - outputs current contents of a canopy_stratum.			*/
/*																*/
/*	SYNOPSIS													*/
/*	void	output_canopy_stratum(										*/
/*					struct	canopy_stratum_object	*canopy_stratum,				*/
/*					struct	date	date,  						*/
/*					FILE 	*outfile)							*/
/*																*/
/*	OPTIONS														*/
/*																*/
/*	DESCRIPTION													*/
/*																*/
/*	outputs spatial structure according to commandline			*/
/*	specifications to specific files							*/
/*																*/
/*	PROGRAMMER NOTES											*/
/*																*/
/*	We only permit one fileset per spatial modelling level.     */
/*	Each fileset has one file for each timestep.  				*/
/*																*/
/*--------------------------------------------------------------*/
#include <stdio.h>
#include "rhessys.h"

void	output_canopy_stratum( int basinID, int hillID, int zoneID, int patchID,
							  struct	canopy_strata_object	*stratum,
							  struct    patch_object  *patch,
							  struct    zone_object   *zone,
							  struct	date	current_date,
							  FILE *outfile)
{
	/*------------------------------------------------------*/
	/*	Local Function Declarations.						*/
	/*------------------------------------------------------*/
	
	/*------------------------------------------------------*/
	/*	Local Variable Definition. 							*/
	/*------------------------------------------------------*/
	// * if(patchID==226201 || patchID==207743 || patchID==239202) 
	fprintf(outfile,
		"%d %d %d %d %d %d %d %d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %d %lf %lf %lf %lf %lf %lf\n",
		current_date.day,
		current_date.month,
		current_date.year,
		basinID,
		hillID,
		zoneID,
		patchID,
		stratum[0].ID,
		zone[0].rain,
		patch[0].rain_throughfall,
		patch[0].rain_throughfall_final,
		stratum[0].rain_receive,
		stratum[0].epv.proj_lai,
		stratum[0].evaporation*1000,
		stratum[0].Kstar_direct,
		stratum[0].Kstar_diffuse,
		stratum[0].sublimation*1000,
		stratum[0].transpiration_unsat_zone *1000.0 + stratum[0].transpiration_sat_zone *1000.0,
		stratum[0].ga*1000.0,
		stratum[0].gsurf*1000.0,
		stratum[0].gs*1000.0,
		stratum[0].epv.psi,
		stratum[0].cdf.leaf_day_mr*1000.0,
		stratum[0].cdf.psn_to_cpool*1000.0,
		stratum[0].rain_stored*1000.0,
		stratum[0].snow_stored*1000.0,
		0.0,//stratum[0].rootzone.SatPct,
		stratum[0].mult_conductance.APAR,
		stratum[0].mult_conductance.tavg,
		stratum[0].mult_conductance.LWP,
		stratum[0].mult_conductance.CO2,
		stratum[0].mult_conductance.tmin,
		stratum[0].mult_conductance.vpd,
		stratum[0].dC13,
			stratum[0].Lstar,
			stratum[0].surface_heat_flux,
			stratum[0].epv.height,
			stratum[0].cover_fraction,
			stratum[0].defaults[0][0].ID,
            stratum[0].APAR_direct,
            stratum[0].APAR_diffuse,
            stratum[0].PET*1000.0,
            stratum[0].cdf.potential_psn_to_cpool*1000.0,
            stratum[0].ppfd_sunlit,
            stratum[0].ppfd_shade);
	return;
} /*end output_canopy_stratum*/
