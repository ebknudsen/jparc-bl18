#!/bin/bash
#
# ess queue script

#SBATCH --job-name=bl18_pxtal_test
#SBATCH --error=bl18_pxtal_test.e%j
#SBATCH --output=bl18_pxtal_test.o%j
###SBATCH --nodes 1
#SBATCH --partition express
#SBATCH --time=2:00:00
# the --exclusive is needed when running OpenMPI
# it will allocate 1x12 core per node
#SBATCH --exclusive 

echo Working directory is $SLURM_SUBMIT_DIR
cd $SLURM_SUBMIT_DIR

NUMCORES=`echo "$SLURM_NNODES 12 * p "| dc`
module load mcstas/2.2a

INSTRUMENT=BL18_pxtal_MCP.instr
#INSTRUMENT=BL18_pxtal_FF.instr
#INSTRUMENT=BL18_pxtal_BOTH.instr
OUTFILE=${INSTRUMENT%%.instr}.out

OUTDIR=${INSTRUMENT%%.instr}_${PBS_JOBID%%.*}
echo $INSTRUMENT $OUTFILE $OUTDIR

### Set up mcrun line
mpirun ./$OUTFILE --dir $OUTDIR -n5e7 L_min=0.4 L_max=4 NX=101 NY=101 NZ=101 XW=0.01 YH=0.01 ZD=0.01 map_fn=default.map_101x101_rectified orts_fn=default.orts lau_fn=Fe.lau AX=2.886 AY=0 AZ=0 BX=0 BY=2.886 BZ=0 CX=0 CY=0 CZ=2.886 samplename=C0127 runnumber=0 side=7
### Set up email status reports 
#SBATCH --mail-type=END
#SBATCH --mail-user=erkn@fysik.dtu.dk

### END of McSub script
