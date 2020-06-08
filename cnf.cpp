/*
 * Author: rainoftime
 * File Description: CNF(Conjunction Normal Form)
 * Creation Date:  2017.
 * Modification History:
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "cnf.h"

cnf::cnf(char *fname) : m_vc(0), m_cc(0), m_clauses(NULL), m_lc(0) {
    FILE *ifp;
    if ((ifp = fopen(fname, "r")) == NULL) {
        fprintf(stderr, "Cannot open file: %s\n", fname);
        exit(0);
    }

    unsigned j, k, x, clause_index = 0, max_clause_len = 1024;
    int *literals = (int *) malloc(max_clause_len * sizeof(int));

    char line[100000];
    size_t len = 100000;
    char c;

    while ((c = getc(ifp)) != EOF) {
        if (isspace(c)) continue; else ungetc(c, ifp);
        fgets(line, len, ifp);
        if (c == 'p') {
            if (sscanf(line, "p cnf %d %d", &m_vc, &m_cc) == 2) {
                m_clauses = (int **) calloc(m_cc, sizeof(int *));
                m_cl = (unsigned *)  calloc(m_cc, sizeof(unsigned));
                break;
            } else {
                fprintf(stderr, "Invalid CNF file\n");
                exit(0);
            }
        }
    }

    while ((c = getc(ifp)) != EOF && clause_index < m_cc) {
        if (isspace(c)) continue; else ungetc(c, ifp);
        if ((c == '-') || isdigit(c)) {
            for (j = 0; fscanf(ifp, "%d", &(literals[j])), literals[j] != 0;) {
                if (++j == max_clause_len) {
                    max_clause_len *= 2;
                    literals = (int *) realloc(literals, max_clause_len * sizeof(int));
                }
            }
            m_clauses[clause_index] = (int *) calloc(j + 1, sizeof(int));
            bool skip_clause = false;
            for (k = 0; k <= j;) {
                bool duplicate_literal = false;
                for (x = 0; x < k; x++) {
                    if (literals[x] == literals[k]) {
                        duplicate_literal = true;
                        break;
                    } else if (literals[x] + literals[k] == 0) {
                        skip_clause = true;
                        break;
                    }
                }
                if (skip_clause) break;
                if (duplicate_literal) {
                    literals[k] = literals[--j];
                    literals[j] = 0;
                } else {
                    m_clauses[clause_index][k] = literals[k];
                    k++;
                }
            }
            if (skip_clause) free(m_clauses[clause_index]);
            else m_lc += (m_cl[clause_index++] = j);
        }
        fgets(line, len, ifp);
    }

    free(literals);
    fclose(ifp);
    if (m_cc > clause_index) {
        m_cc = clause_index;
        m_clauses = (int **) realloc(m_clauses, clause_index * sizeof(int *));
    }
}

cnf::~cnf() {
    if (m_clauses) {
        for (unsigned i = 0; i < m_cc; i++) free(m_clauses[i]);
        free(m_clauses);
    }
    free(m_cl);
}
