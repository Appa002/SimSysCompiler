#include <builtinTypes.h>
#include "ExitTokenGenerator.h"

ACC::Structure* ACC::ExitTokenGenerator::generate(ACC::Code &code) {
  /*  auto& fn = code.getFnSymbol();
    auto expr = node->children[0]->asExpr()->generate(code);

    if(expr.typeId != BuiltIns::numType)
        throw std::runtime_error("Exit needs to be called with a number as argument.");

    fn.writeLine(expr.copyToRegister("rdi", code));
    fn.writeLine("mov rax, 60");
    fn.writeLine("syscall");
*/
    return {};
}
