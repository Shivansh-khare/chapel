// chplcgfns.h
//
// Declarations for variables and prototypes for functions which are
// generated by the chapel compiler.
// This header makes those symbols available to client code in the runtime.
//
// TODO: Arguably, since it contains both function and variable declarations,
//  it should be renamed as chplcgdecl.h (or so).
//
#ifndef _CHPL_GEN_INTERFACE_H_
#define _CHPL_GEN_INTERFACE_H_

#include <stdlib.h>
#include "chpltypes.h"

/* This header file is for routines that are in the generated code */

/* defined in chpl__header.h: */

#if 0
// TODO: Factor runtime includes so that we can compile with this declaration enabled.
// It is a verbatim copy of the declaration produced by the compiler, but since
// the runtime library is compiled first and depends on chpl_localeID_t, we need
// an early definition.
// As long as chplcgfns.h is not included by any compiler-generated code, we can
// remove the #if 0 and it will work.  Then, the duplicate declaration in chpltypes.c
// can be removed (q.v.).
typedef struct __chpl_localeID_t {
  c_nodeid_t node;
  c_subloc_t subloc;
} chpl_localeID_t;
#endif

extern const char* chpl_compileCommand;
extern const char* chpl_compileVersion;
extern const char* CHPL_HOST_PLATFORM;
extern const char* CHPL_TARGET_PLATFORM;
extern const char* CHPL_HOST_COMPILER;
extern const char* CHPL_TARGET_COMPILER;
extern const char* CHPL_THREADS;
extern const char* CHPL_COMM;

/* defined in main.c */
extern char* chpl_executionCommand;

/* generated */
extern chpl_fn_p chpl_ftable[];

void chpl__init_preInit(int64_t _ln, chpl_string _fn);
void chpl__init_ChapelThreads(int64_t _ln, chpl_string _fn);
void chpl__init_ChapelStandard(int64_t _ln, chpl_string _fn);

/* used for entry point: */
extern int64_t chpl_gen_main(chpl_main_argument* const _arg);

/* used for config vars: */
extern void CreateConfigVarTable(void);

/* used by copy collection: */

//extern size_t cid2size(chpl__class_id cid);
//extern size_t* cid2offsets(chpl__class_id cid);

/* These are defined in _type_structure.c if
   --gen-communicated-structures is true and are used by a
   communication layer to query types of communicated buffers */
extern chplType chpl_getFieldType(int typeNum, int fieldNum);
extern size_t chpl_getFieldOffset(int typeNum, int fieldNum);
extern size_t chpl_getFieldSize(int typeNum);
extern const int chpl_max_fields_per_type;

#endif
