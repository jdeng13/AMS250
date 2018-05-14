 #include <stdio.h>
 #include <mpi.h>
 
 int main (int argc, char *argv[]) {
   double starttime,endtime;
   int namelen;
   char processor_name[MPI_MAX_PROCESSOR_NAME];
 
   MPI_Init(&argc,&argv);
   MPI_Get_processor_name(processor_name,&namelen);
   printf ("Process %s\n", processor_name);
 
   starttime = MPI_Wtime();
   //Here some computation or communication
   endtime = MPI_Wtime();
   printf ("Time: %lf\n",endtime-starttime);
 
   MPI_Finalize ();
   return 0;
 }
