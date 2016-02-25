#!/bin/sh
###Note: No commands may be executed until after the #PBS lines
### Job name (comment out the next line to get the name of the script used as the job name)
###PBS -N bl18_open_te
### Output files (comment out the next 2 lines to get the job name used instead)
###PBS -e test.err
###PBS -o test.log
### Send mail when job is aborted or terminates normally
#PBS -m abe
### Queue name (small <25 min, medium <2 h 15 min, long <13 h, verylong <50 h)
#PBS -q small 
### Number of nodes
###PBS -l nodes=2:ppn=4:opteron4
###PBS -l nodes=2:ppn=8:xeon8
#PBS -l nodes=2:ppn=16:xeon16
### Requesting time - 12 hours - overwrites **long** queue setting
####PBS -l walltime=00:25:00

# Go tho the directory from where the job was submitted (initial directory is $HOME)
echo Working directory is $PBS_O_WORKDIR
cd $PBS_O_WORKDIR

### Here follows the user commands:
# Define number of processors
NPROCS=`wc -l < $PBS_NODEFILE`
echo This job has allocated $NPROCS nodes

INSTRUMENT=BL18_pxtal_MCP.instr
#INSTRUMENT=BL18_pxtal_FF.instr
#INSTRUMENT=BL18_pxtal_BOTH.instr
OUTFILE=${INSTRUMENT%%.instr}.out

OUTDIR=${INSTRUMENT%%.instr}_${PBS_JOBID%%.*}
echo $INSTRUMENT $OUTFILE $OUTDIR

#MCSTAS_TOOLS=/home/niflheim1/erkn/mcstas/2.2a/tools/Perl/ $HOME/bin/mcrun --mpi=$NPROCS BL18_pxtal_1sided.instr L_min=0.4 L_max=4 NX=3 NY=3 NZ=3 XW=0.01 YH=0.01 ZD=0.01 map_fn=default.map_3x3 orts_fn=default.orts lau_fn=Fe.lau AX=2.886 AY=0 AZ=0 BX=0 BY=2.886 BZ=0 CX=0 CY=0 CZ=2.886 samplename=C0127 runnumber=0 side=7
mpirun -np $NPROCS ./${OUTFILE} --dir $OUTDIR -n5e7 L_min=0.4 L_max=4 NX=1 NY=1 NZ=1 XW=0.01 YH=0.01 ZD=0.01 map_fn=openbeam_sample.map orts_fn=default.orts lau_fn=Fe.lau AX=2.886 AY=0 AZ=0 BX=0 BY=2.886 BZ=0 CX=0 CY=0 CZ=2.886 samplename=C0127 runnumber=0 side=7
