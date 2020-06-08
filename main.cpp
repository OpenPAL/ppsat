/*
 * Author: rainoftime
 * File Description: Main function
 * Creation Date:  2017.
 * Modification History:
*/

#define VERSION "0.1"
#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
#include <ctime>
double _get_cpu_time(){ 
  return (double) clock() / CLOCKS_PER_SEC;
}
#else

#include <sys/time.h>
//#include <sys/resource.h>
//#include <unistd.h>

/*
double _get_cpu_time() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return (usage.ru_utime.tv_usec + usage.ru_stime.tv_usec) *
           (1e-6) + (usage.ru_utime.tv_sec + usage.ru_stime.tv_sec);
}
*/

#endif

#include "sat_solver.h"

int main(int argc, char **argv) {
    //printf("c ppsat %s\n", VERSION);
    if (argc < 2) exit(0);
    //double _start_time = _get_cpu_time();

    cnf *m_cnf = new cnf(argv[1]);
    //printf("c solving %s\n", argv[1]);
    //printf("c %d variables, %d clauses\n", m_cnf->m_vc, m_cnf->m_cc);
    fflush(stdout);

    sat_solver solver(*m_cnf);
    delete m_cnf;

    bool result = solver.run();

    /* this code can be used for interfacing with SateELite
    if (argc > 2) {
        if(result) {
            FILE *ofp;
            if ((ofp = fopen(argv[2], "w")) != NULL) {
                fprintf(ofp, "SAT\n");
                solver.printSolution(ofp);
                fclose(ofp);
            }
        }
    } else {
    */
    if (result) {
        printf("s sat\n");
        //		printf("s SATISFIABLE\nv ");
        //		solver.printSolution(stdout);
    } else printf("s unsat\n");
    //}
    //solver.print_stats();
    //printf("c solved in %.2fs\n", _get_cpu_time() - _start_time);
    exit(result ? 10 : 20);
}

