/*
 * Author: rainoftime
 * File Description: CNF
 * Creation Date:  2017.
 * Modification History:
*/

#ifndef _CNF
#define _CNF

struct cnf {
    unsigned m_vc;       // var count
    unsigned m_cc;       // clause count
    int **   m_clauses;  // 2-dim. array with entries same as in cnf file
    unsigned m_lc;       // literal count
    unsigned *m_cl;      // clause length
    cnf(char *fname);

    ~cnf();
};

#endif
