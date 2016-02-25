#!/bin/bash
#
# ess queue script

#SBATCH --job-name=bl18_sxtal_verylong
#SBATCH --error=bl18_sxtal_verylong.e%j
#SBATCH --output=bl18_sxtal_verylong.o%j
#SBATCH --nodes 20-39
#SBATCH --partition long
#SBATCH --time=10:00:00
#SBATCH --mail-type=END
#SBATCH --mail-user=erkn@fysik.dtu.dk
# the --exclusive is needed when running OpenMPI
# it will allocate 1x12 core per node
#SBATCH --exclusive 
NUMCORES=`echo "$SLURM_NNODES 12 * p "| dc`
module load mcstas/2.2a

#INSTRUMENT=BL18_pxtal_MCP.instr
INSTRUMENT=BL18_pxtal_FF.instr
#INSTRUMENT=BL18_pxtal_BOTH.instr
OUTFILE=${INSTRUMENT%%.instr}.out

OUTDIR=${INSTRUMENT%%.instr}_${SLURM_JOB_ID}
echo $INSTRUMENT $OUTFILE $OUTDIR

### Set up mcrun line
mpirun ./$OUTFILE --dir $OUTDIR -n1e10 L_min=0.4 L_max=4 NX=1 NY=1 NZ=1 XW=0.01 YH=0.01 ZD=0.01 map_fn=1x1x3.map orts_fn=default.orts lau_fn=CoNiGa_bcc.xtal AX=2.86 AY=0 AZ=0 BX=0 BY=2.86 BZ=0 CX=0 CY=0 CZ=2.86 samplename=C0127 omega=0 runnumber=0 side=7
### END of McSub script
### Set up email status reports 

### END of McSub script
