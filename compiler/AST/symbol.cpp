#include <typeinfo>
#include "misc.h"
#include "symbol.h"
#include "symtab.h"


Symbol::Symbol(char* init_name, Type* init_type) :
  name(init_name),
  type(init_type),
  level(Symboltable::getLevel())
{}


void Symbol::print(FILE* outfile) {
  fprintf(outfile, "%s", name);
}

void Symbol::codegen(FILE* outfile) {
  fprintf(outfile, "%s", name);
}


void Symbol::printDef(FILE* outfile) {
  print(outfile);
}


void Symbol::printDefList(FILE* outfile, char* separator) {
  Symbol* ptr;

  printDef(outfile);
  ptr = nextLink(Symbol, this);
  while (ptr != NULL) {
    fprintf(outfile, "%s", separator);
    ptr->printDef(outfile);
    ptr = nextLink(Symbol, ptr);
  }
}


void Symbol::codegenDef(FILE* outfile) {
  type->codegen(outfile);
  fprintf(outfile, " ");
  this->codegen(outfile);
}  


void Symbol::codegenDefList(FILE* outfile, char* separator) {
  Symbol* ptr;

  codegenDef(outfile);
  ptr = nextLink(Symbol, this);
  while (ptr != NULL) {
    fprintf(outfile, "%s", separator);
    ptr->codegenDef(outfile);
    ptr = nextLink(Symbol, ptr);
  }
}


NullSymbol::NullSymbol(void) :
  Symbol("NullSymbol")
{}


bool NullSymbol::isNull(void) {
  return true;
}


UseBeforeDefSymbol::UseBeforeDefSymbol(char* init_name) :
  Symbol(init_name)
{}


VarSymbol::VarSymbol(char* init_name, varType init_varClass, bool init_isConst,
		     Type* init_type) :
  Symbol(init_name, init_type),
  varClass(init_varClass),
  isConst(init_isConst)
{}


void VarSymbol::printWithType(FILE* outfile) {
  print(outfile);
  if (type != NULL) {
    fprintf(outfile, ": ");
    type->print(outfile);
  }
}

NullVarSymbol::NullVarSymbol() :
  VarSymbol("NullVarSymbol")
{}


bool NullVarSymbol::isNull(void) {
  return true;
}


static char* paramTypeNames[NUM_PARAM_TYPES] = {
  "in",
  "inout",
  "out",
  "const"
};


ParamSymbol::ParamSymbol(paramType init_usage, char* init_name, 
			 Type* init_type) :
  Symbol(init_name, init_type),
  usage(init_usage)
{}


void ParamSymbol::printDef(FILE* outfile) {
  fprintf(outfile, "%s ", paramTypeNames[usage]);
  Symbol::print(outfile);
  fprintf(outfile, ": ");
  type->print(outfile);
}


TypeSymbol::TypeSymbol(char* init_name, Type* init_definition) :
  Symbol(init_name, init_definition)
{}


ClassSymbol::ClassSymbol(char* init_name, ClassType* init_class) :
  TypeSymbol(init_name, init_class)
{}


NullClassSymbol::NullClassSymbol(void) :
  ClassSymbol("NullClass", NULL)
{}


bool NullClassSymbol::isNull(void) {
  return true;
}


ClassType* ClassSymbol::getType(void) {
  if (typeid(*type) != typeid(ClassType)) {
    INT_FATAL(this, "ClassSymbol has non-ClassType");
  }
  return (ClassType*)type;
}


ReduceSymbol::ReduceSymbol(char* init_name, ClassType* init_class) :
  ClassSymbol(init_name, init_class)
{}



FnSymbol::FnSymbol(char* init_name, Symbol* init_formals, Type* init_retType,
		   Stmt* init_body, bool init_exportMe) :
  Symbol(init_name, init_retType),
  exportMe(init_exportMe),
  formals(init_formals),
  body(init_body)
{}


void FnSymbol::codegenDef(FILE* outfile) {
  if (!exportMe) {
    fprintf(outfile, "static ");
  }
  if (type->isNull()) {
    fprintf(outfile, "void");
  } else {
    type->codegen(outfile);
  }
  fprintf(outfile, " ");
  this->codegen(outfile);
  fprintf(outfile, "(");
  if (formals->isNull()) {
    fprintf(outfile, "void");
  } else {
    formals->codegenDefList(outfile, ", ");
  }
  fprintf(outfile, ")");
}


EnumSymbol::EnumSymbol(char* init_name, int init_val) :
  Symbol(init_name),
  val(init_val)
{}
