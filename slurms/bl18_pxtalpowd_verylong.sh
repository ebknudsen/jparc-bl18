#!/bin/bash
#
# ess queue script

#SBATCH --job-name=bl18_pxtal_verylong
#SBATCH --error=bl18_pxtal_verylong.e%j
#SBATCH --output=bl18_pxtal_verylong.o%j
###SBATCH --nodes 20-39
###SBATCH --partition long
#SBATCH --nodes 1
#SBATCH --partition express
###SBATCH --time=10:00:00
#SBATCH --mail-type=END
#SBATCH --mail-user=erkn@fysik.dtu.dk
# the --exclusive is needed when running OpenMPI
# it will allocate 1x12 core per node
#SBATCH --exclusive 
NUMCORES=`echo "$SLURM_NNODES 12 * p "| dc`
module load mcstas/2.2a

INSTRUMENT=BL18_pxtalpowd_MCP.instr
#INSTRUMENT=BL18_pxtal_FF.instr
#INSTRUMENT=BL18_pxtal_BOTH.instr
OUTFILE=${INSTRUMENT%%.instr}.out

OUTDIR=${INSTRUMENT%%.instr}_${SLURM_JOB_ID}
echo $INSTRUMENT $OUTFILE $OUTDIR

### Set up mcrun line
mpirun ./$OUTFILE --dir $OUTDIR -n1e7 L_min=0.4 L_max=4 NX=200 NY=500 NZ=200 XW=0.01 YH=0.025 ZD=0.01 map_fn=data/fe_allgrains.map orts_fn=data/default.orts pow_fn=data/Fe.powder lau_fn=data/Fe.lau AX=2.8665 AY=0 AZ=0 BX=0 BY=2.8665 BZ=0 CX=0 CY=0 CZ=2.8665 samplename=C0127 omega=__omega__ runnumber=0 side=7
